
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <endian.h>

#include <limits.h>
#include <elf.h>

int main(int argc, char **argv)
{
    int i;
    int ifd;
    char *mbuf;
    unsigned int *wbuf;
    unsigned int checksum = 0;
    int word_num;
    struct stat st;

    if (argc != 2) {
        printf("usage: %s file\n", argv[0]);
        exit(-1);
    }

    if ((ifd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(-1);
    }

    if ((fstat(ifd, &st)) == -1) {
        perror("fstat");
        exit(-1);
    }

    if ((mbuf = mmap(0, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, ifd, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }

    printf("file size: %d \n", st.st_size);
    printf("mmap size: %d \n", strlen(mbuf));

    {
        long int randomdata;
        Elf32_Ehdr *elfhead = (Elf32_Ehdr *)mbuf;
        Elf32_Ehdr *shead   = elfhead->e_shoff + (void *)mbuf;
        int shead_num       = elfhead->e_shnum;
        int shheadsize      = elfhead->e_shentsize;
        randomdata          = random();

        printf("elfhead->e_shoff = %x\n", elfhead->e_shoff);
        memset(shead, random(), shead_num * shheadsize);
        memset(&elfhead->e_shoff, INT_MAX, sizeof(elfhead->e_shoff));
        memset(&elfhead->e_shnum, INT_MAX, sizeof(elfhead->e_shnum));
        memset(&elfhead->e_shentsize, random(), sizeof(elfhead->e_shentsize));

    }
    munmap(mbuf, st.st_size);
    close(ifd);

    
    return 0;

}
