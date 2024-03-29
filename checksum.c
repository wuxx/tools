/* java byte code dump */
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

    word_num = st.st_size / 4;
    wbuf = (unsigned int *)mbuf;
    printf("word_num: %d\n", word_num);

    for(i = 0; i < 16; i++) {
        checksum += wbuf[i];
    }

    printf("checksum: 0x%08x\n", checksum);
    
    return 0;

}
