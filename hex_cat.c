#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

void dump_byte(char *buf, int size)
{
    int i;
    for(i = 0; i < size; i++) {
        printf("[%d]: [0x%02x] [%c]\n", i, buf[i], buf[i]);
    }
}

int main(int argc, char **argv)
{
    int ifd;
    int word, count;
    struct stat st;

    if (argc != 2) {
        printf("[%s] file\n", argv[0]);
        exit(-1);
    }

    if ((ifd = open(argv[1], O_RDONLY)) == -1) {
        perror("open");
        exit(-1);
    }

    if ((fstat(ifd, &st)) == -1) {
        perror("fstat");
        exit(-1);
    }

    assert(st.st_size % 4 == 0);

    count = st.st_size / 4;

    while (1) {
        count = read(ifd, &word, 4);
        if (count == 4) {
            printf("0x%08X\n", word);
        } else if (count == 0) {
            break;
        } else {
            assert(0);
        }
    }


    return 0;
}
