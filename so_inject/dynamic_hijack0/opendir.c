#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main()
{
	DIR * d;
	d = opendir("/bin/");
	printf("opendir return %x\n", d);
	return 0;
}
