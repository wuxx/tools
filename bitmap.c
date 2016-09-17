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

typedef unsigned char u8; 
typedef   signed char s8; 

typedef unsigned short u16;
typedef   signed short s16;

typedef unsigned int u32;
typedef   signed int s32;

#define BIT_MAX 1024

u8 bitmap[BIT_MAX / 8]  = {0};

u8 get_bit(void *map, u32 bit_max, u32 bit_index)
{
    u8  bit;
    u32 word_index, word_offset;
    u32 *pmap;

    bit_index = bit_index % bit_max;

    pmap = map;
    word_index  = bit_index / 32;
    word_offset = bit_index % 32;

    bit = pmap[word_index] & (0x1 << word_offset);

    return bit;
}

u8 set_bit(void *map, u32 bit_max, u32 bit_index, u8 bit)
{
    u32 word_index, word_offset;
    u32 *pmap;
    u32 bit_mask;

    bit_index = bit_index % bit_max;

    pmap = map;
    word_index  = bit_index / 32;
    word_offset = bit_index % 32;

    if (bit == 0) {
        bit_mask = ~(0x1 << word_offset);
        pmap[word_index] = (pmap[word_index]) & bit_mask;
    } else {    /* b == 1 */
        bit_mask = (0x1 << word_offset);
        pmap[word_index] = (pmap[word_index]) | bit_mask;
    }

    bit = pmap[word_index] & (0x1 << word_offset);
}

s32 find_first_bit(void *map, u32 bit_max, u8 bit)
{
    u32 i;

    bit = bit & 0x1;

    for(i = 0; i < bit_max; i++) {
        if (get_bit(map, bit_max, i) == bit) {
            return i;
        }
    }

    return -1;
}

u32 count_bit(void *map, u32 bit_max, u8 bit)
{
    u8 b;
    u32 i;
    u32 zero_count = 0, one_count = 0;

    for(i = 0; i < bit_max; i++) {
        b = get_bit(map, bit_max, i);
        switch (b) {
            case (0):
                zero_count++;
                break;
            case (1):
                one_count++;
                break;
            default:
                assert(0);
        }
    }

    return bit == 0 ? zero_count : one_count;
}


int main(int argc, char **argv)
{

    int ifd;
    char *mbuf;
    struct stat st; 

    if (argc != 2) {
        printf("usage: %s bitmapfile\n", argv[0]);
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

    return 0;
}
