// NOTE: compile with gcc -lm filename.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM_WIDTH   (1440)
#define DIM_HEIGHT  (2560)

#define _sq(x) ((x)*(x)) // square
#define _cb(x) abs((x)*(x)*(x)) // absolute value of cube
#define _cr(x) (unsigned char)(pow((x),1.0/3.0)) // cube root

unsigned char GR(int,int);
unsigned char BL(int,int);

unsigned char RD(int x,int y){
    return 255;
}
 
unsigned char GR(int x,int y){
    return 255;
}
 
unsigned char BL(int x,int y){
    return 255;
}


void pixel_write(int,int);
FILE *fp;

int main()
{
    int x, y;
    fp = fopen("MathPic.ppm","wb");
    fprintf(fp, "P6\n%d %d\n255\n", DIM_WIDTH, DIM_HEIGHT);
    for( y = 0; y < DIM_HEIGHT; y++) {
        for( x = 0; x < DIM_WIDTH; x++) {
            pixel_write(x, y);
        }
    }

    fclose(fp);
    return 0;
}

void pixel_write(int x, int y)
{
    static unsigned char color[3];
    color[0] = RD(x, y) & 255;
    color[1] = GR(x, y) & 255;
    color[2] = BL(x, y) & 255;
    fwrite(color, 1, 3, fp);
}
