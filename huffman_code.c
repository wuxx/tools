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

#define CH_MAX (256)

struct c_struct {
    char c;
    int freq;
    struct c_struct *parent;
    struct c_struct *lchild, rchild;
};

void dumpw(int *buf, int size)
{
    int i, j;

    j = 0;
    printf("\n0x%02x\t", 0);
    for(i = 0; i < size; i++) {
        printf("0x%08x ", buf[i]);
        j++;
        if (j % 4 == 0) {
            printf("\n0x%02x\t", j);
        }
    }

    printf("\n");
}

int main(int argc, char **argv)
{

    int i;
    int ifd;
    unsigned char *mbuf;
    struct stat st; 
    struct c_struct c_st[CH_MAX];

    /* init */
    for(i = 0; i < CH_MAX; i++) {
        c_st[i].c    = i;
        c_st[i].freq = 0;
        c_st[i].parent = NULL;
        c_st[i].lchild = NULL;
        c_st[i].rchild = NULL;
    }

    printf("enter!\n");
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

    for(i = 0; i < st.st_size; i++) {
        c_st[mbuf[i]].freq++;
    }

    for(i = 0; i < CH_MAX; i++) {
        printf("[0x%02x]: %d \n", i, c_st[i].freq);
    }

    munmap(mbuf, st.st_size);

    printf("exit!\n");
    return 0;

}
