#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


typedef unsigned char u8;
typedef   signed char s8;

typedef unsigned short u16;
typedef   signed short s16;

typedef unsigned int u32;
typedef   signed int s32;

#define WIDTH   (656)
#define HEIGHT  (416)

struct rgb888 {
    u8 b;
    u8 g;
    u8 r;
    u8 reserved;
};

struct rgb888 pixel  = {0xFF, 0x0, 0x0, 0xFF};

/* 2048x1536 */
int main(int argc, char **argv)
{
    u32 i;
    u32 pixel_num;
    u8 *fb;
    struct rgb888 *p;

    pixel_num = WIDTH * HEIGHT;

    fb = malloc(pixel_num * sizeof(struct rgb888));
    p  = (struct rgb888 *)fb;

    for(i = 0; i < pixel_num; i++) {
        memcpy(&p[i], &pixel, sizeof(struct rgb888));
    }

    write(STDOUT_FILENO, fb, pixel_num * sizeof(struct rgb888));
    return 0;
}
