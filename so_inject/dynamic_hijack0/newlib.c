#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <dlfcn.h>

int nest = 0;

void functions()
{
	printf("my own function \n");
}

#define LIBC_PATH       "/lib/i386-linux-gnu/libc.so.6"

DIR     *opendir(const char *name)
{
	void  *handle;
	DIR  *(*sym0)(const char *name);

	void  *(*sym1)(const char *name);

	handle = dlopen(LIBC_PATH, RTLD_LAZY);

	sym0 = opendir;
	sym1 = (void *) dlsym(handle, "opendir");
	printf("OPENDIR HIJACKED -orig- = %08X -> %08X.::. -param- = [%s] %d\n", 
			sym1, sym0, name, nest++);
	return (sym1(name));
}
