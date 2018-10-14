#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;
typedef   signed int s32;

#define get_bit(x, index)   (((x) >> (index)) & 0x1)

int main(int argc, char **argv)
{

    s32 i;
    u32 hex;
    if (argc != 2) {
        fprintf(stderr, "usage: %s [hex-num]\n", argv[0]);
        exit(-1);
    }

    hex = strtoul(argv[1], NULL, 0);
    fprintf(stdout, "input: [0x%08x]\n", hex);

    for(i = 31; i >= 0; i--) {
        fprintf(stdout, "%02d ", i);
        if (i % 4 == 0) {
            fprintf(stdout, " ");
        }
    }
    fprintf(stdout, "\n");
    for(i = 31; i >= 0; i--) {
        fprintf(stdout, " %d ", get_bit(hex, i));
        if (i % 4 == 0) {
            fprintf(stdout, " ");
        }
    }

    fprintf(stdout, "\n");

    //printf();

    return 0;
}

