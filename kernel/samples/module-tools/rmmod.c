/* rmmod.c: remove a module from the kernel.
    Copyright (C) 2001  Rusty Russell.
    Copyright (C) 2002  Rusty Russell, IBM Corporation.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <asm/unistd.h>
#include <stdarg.h>
#include <getopt.h>
#include <syslog.h>

#include "util.h"
#include "logging.h"

extern long delete_module(const char *, unsigned int);

static char *next_field(const char *line)
{
	const char *rest;

	rest = line + strcspn(line, " ");
	rest += strspn(rest, " ");
	return (char *)rest;
}

/* Report that the module is in use. */
static void mod_in_use(const char *modname, char *usedby)
{
	/* New /proc/modules uses a single "-" to mean "nothing".  Old
           one just puts nothing there. */
	if (usedby[0] == '-' || streq(usedby, "")) {
		error("Module %s is in use\n", modname);
		return;
	}

	/* New /proc/modules *always* prints commas (even if only one) */
	if (strchr(usedby, ','))
		/* Blatt over trailing comma for neatness */
		usedby[strcspn(usedby, " \n")-1] = '\0';
	else {
		/* Older /proc/modules just put them as
                   space-separated names.  Blatt over trailing \n */
		usedby[strlen(usedby)-1] = '\0';
	}

	error("Module %s is in use by %s\n", modname, usedby);
}

/* If we can check usage without entering kernel, do so. */
static int check_usage(const char *modname)
{
	FILE *module_list;
	char line[10240], name[64];
	unsigned long size, refs;
	int scanned;

	module_list = fopen("/proc/modules", "r");
	if (!module_list) {
		if (errno == ENOENT) /* /proc may not be mounted. */
			return 0;
		fatal("can't open /proc/modules: %s\n", strerror(errno));
	}
	while (fgets(line, sizeof(line)-1, module_list) != NULL) {
		if (strchr(line, '\n') == NULL) {
			fatal("V. v. long line broke rmmod.\n");
			exit(1);
		}

		scanned = sscanf(line, "%s %lu %lu", name, &size, &refs);
		if (strcmp(name, modname) != 0)
			continue;

		if (scanned < 2)
			fatal("Unknown format in /proc/modules: %s\n", line);

		if (scanned == 2)
			fatal("Kernel does not have unload support.\n");

		/* Hand it fields 3 onwards. */
		if (refs != 0)
			mod_in_use(modname,
				   next_field(next_field(next_field(line))));
		goto out;
	}
	error("Module %s does not exist in /proc/modules\n", modname);
	refs = 1;
 out:
	fclose(module_list);
	return (refs == 0) ? 0 : -EINVAL;
}

static int rmmod(const char *path, int flags)
{
	long ret;
	char name[strlen(path) + 1];

	filename2modname(name, path);

	if ((flags & O_NONBLOCK) && !(flags & O_TRUNC)) {
		if (check_usage(name) != 0)
			return 1;
	}

	info("rmmod %s, wait=%s%s\n", name,
	     (flags & O_NONBLOCK) ? "no" : "yes",
	     (flags & O_TRUNC) ? " force" : "");

	ret = delete_module(name, flags);
	if (ret != 0)
		error("Removing '%s': %s\n", name, strerror(errno));
	return ret;
}

static const struct option options[] = { { "all", 0, NULL, 'a' },
				   { "force", 0, NULL, 'f' },
				   { "help", 0, NULL, 'h' },
				   { "syslog", 0, NULL, 's' },
				   { "verbose", 0, NULL, 'v' },
				   { "version", 0, NULL, 'V' },
				   { "wait", 0, NULL, 'w' },
				   { NULL, 0, NULL, 0 } };

static void print_usage(const char *progname)
{
	fprintf(stderr,
		"Usage: %s [-fhswvV] modulename ...\n"
		// " -a (or --all) to remove all modules (no names needed)\n"
		" -f (or --force) forces a module unload, and may crash your\n"
		"    machine.  This requires the Forced Module Removal option\n"
		"    when the kernel was compiled.\n"
		" -h (or --help) prints this help text\n"
		" -s (or --syslog) says use syslog, not stderr\n"
		" -v (or --verbose) enables more messages\n"
		" -V (or --version) prints the version code\n"
		" -w (or --wait) begins a module removal even if it is used\n"
		"    and will stop new users from accessing the module (so it\n"
		"    should eventually fall to zero).\n"
		, progname);
	exit(1);
}

int main(int argc, char *argv[])
{
	/* O_EXCL so kernels can spot old rmmod versions */
	unsigned int flags = O_NONBLOCK|O_EXCL;
	int i, opt, all = 0;
	int ret, err;

	while ((opt = getopt_long(argc, argv,
			"afh?swvV", options, NULL)) != EOF) {
		switch (opt) {
		case 'a':	// --all
			all = 1;
			break;
		case 'f':	// --force
			flags |= O_TRUNC;
			break;
		case 's':	// --syslog
			openlog("rmmod", LOG_CONS, LOG_DAEMON);
			logging = 1;
			break;
		case 'w':	// --wait
			flags &= ~O_NONBLOCK;
			break;
		case 'v':	// --verbose
			verbose++;
			break;
		case 'V':	// --version
			//puts(PACKAGE " version " VERSION);
			return 0;

		default:
			print_usage(argv[0]);
		}
	}
	if (!argv[optind]) {
		fprintf(stderr, "no module names given\n");
		print_usage(argv[0]);
	}

	err = 0;
	/* remove each specified module */
	for (i = optind; i < argc; i++) {
		ret = rmmod(argv[i], flags);
		if (ret != 0)
			err = 1;
	}

	if (logging)
		closelog();
	exit(err);
}
