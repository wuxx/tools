#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>


int main(int argc, char **argv)
{
    int addr = 0;
    int ifd1, ifd2; 
    struct stat st1, st2;
    char fdata1, fdata2;
    char edata1, edata2;
    int count1, count2;


    if (argc != 5) {
        printf("%s file1 file2 data1 data2\n", argv[0]);
        exit(-1);
    }

    if ((ifd1 = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(-1);
    }

    if ((ifd2 = open(argv[2], O_RDWR)) == -1) {
        perror("open");
        exit(-1);
    }

    edata1 = strtol(argv[3], NULL, 0);
    edata2 = strtol(argv[4], NULL, 0);
    printf("edata1: 0x%x; edata2: 0x%x\n", edata1, edata2);

    if ((fstat(ifd1, &st1)) == -1) {
        perror("fstat");
        exit(-1);
    }

    if ((fstat(ifd2, &st2)) == -1) {
        perror("fstat");
        exit(-1);
    }

    assert(st1.st_size == st2.st_size);

    while (1) {

        count1 = read(ifd1, &fdata1, 1);
        count2 = read(ifd2, &fdata2, 1);
        
        assert(count1 == count2);

        if (count1 == 1) {
            if ((fdata1 == edata1) && (fdata2 == edata2)) {
                printf("[%x] match!\n", addr);
            }
            addr++;

        } else if (count1 == 0) {
            break;
        } else {
            assert(0);
        }
    }

    close(ifd1);
    close(ifd2);
}
