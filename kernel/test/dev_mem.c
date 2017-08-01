#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#define PAGE_SIZE (4 * 1024)

/* this test code cannot work :( */
int main()
{
    long long int addr = 0;
    int data;
    int fd;
	int *mbuf = NULL;

    if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
        perror("open");
        exit(-1);
    }
#if 0    
    int count;
    while(1) {
        count = read(fd, &data, sizeof(data));
        if (count == sizeof(data)) {
            addr += sizeof(data);
        } else if (count == 0) {
            printf("read finish. total: size %x\n", addr);
            break;
        } else {
            printf("read %x fail\n", addr);
            exit(-1);
        }

        if ((addr % PAGE_SIZE) == 0) {
            printf("0x%x\n", addr);
        }
    }
#endif

    while(1) {
        if ((mbuf = mmap((void *)addr, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
            perror("mmap");
            printf("map %p fail\n", (void *)addr);
            exit(-1);
        }

        printf("%p\n", (void *)addr);
        addr += PAGE_SIZE;
        munmap(mbuf, PAGE_SIZE);
    }

    close(fd);
    return 0;
}
