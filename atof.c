#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;
typedef   signed int s32;

int main(int argc, char **argv)
{
    char *filename = NULL;
    u32 delay_us = 0;
    double zoom_in = 1.0;
    u32 xOffset = 0;
    u32 yOffset = 0;

    s32 ret;

    filename = argv[1];
    delay_us = atoi(argv[2]);
    zoom_in  = atof(argv[3]);
    xOffset  = atoi(argv[4]);
    yOffset  = atoi(argv[5]);

    printf("filename: %s\n", filename);
    printf("delay_us: %d\n", delay_us);
    printf("zoom_in:  %f\n", zoom_in); 
    printf("xOffset:  %d\n", xOffset); 
    printf("yOffset:  %d\n", yOffset); 
}
