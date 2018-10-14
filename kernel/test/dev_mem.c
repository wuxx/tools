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
/*
	kernel config require CONFIG_STRICT_DEVMEM=n
	http://blog.sina.com.cn/s/blog_6f5b220601012xbc.html
*/

#define PAGE_SIZE (4 * 1024)

/* this test code cannot work :( */
int main()
{
    int i;
    long long int addr = 0;
    int data;
    int fd;
	int *mbuf = NULL;
    struct stat st;

    if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
        perror("open");
        exit(-1);
    }

#if 0
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        exit(-1);
    }

    printf("size: 0x%lx\n", st.st_size);
    while(1);
#endif
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
        if ((mbuf = mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, addr)) == MAP_FAILED) {
            perror("mmap");
            printf("map %p fail\n", (void *)addr);
            exit(-1);
        }

        printf("%p %x\n", (int *)addr, mbuf[0]);
#if 0
        if (addr == 0x13e8a000) {
            for(i = 0; i < PAGE_SIZE / 4; i++) {
                printf("[%x]: %x\n", addr + i * 4, mbuf[i]);
            }
	    while(1);
        }
#endif

        addr += PAGE_SIZE;
        munmap(mbuf, PAGE_SIZE);
    }

    close(fd);
    return 0;
}
