#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <stdio.h>  
#include <sys/mman.h>  
#include <errno.h>  
#include <unistd.h>  
#include <stdlib.h>  
  
  
char code[4096] __attribute__((aligned(4096)));  
  
int main(int argc, const char *argv[])  
{  
    int fd;  
    int ret;  
    void (*func)(void);  
  
    if (argc != 2) {  
        fprintf(stderr, "\n\tUsage: sctest <shellcode>\n\n");  
        return 1;  
    }  
  
    fd = open(argv[1], O_RDONLY);  
    if (!fd) {  
        fprintf(stderr, "Unable open file %s, err = %d(%m)\n", argv[1], errno);  
        return 2;  
    }  
  
    ret = read(fd, code, sizeof(code));  
    if (ret < 0) {  
        fprintf(stderr, "Unable read file %s, err = %d(%m)\n", argv[1], errno);  
        return 3;  
    }  
  
    ret = mprotect(code, sizeof(code), PROT_EXEC);  
    if (ret < 0) {  
        fprintf(stderr, "Unable mprotect, err = %d(%m)\n", errno);  
        return 4;  
    }  
  
    /* execute shell code */  
    func = (void (*)(void))code;  
    func();  
    abort();      
}
