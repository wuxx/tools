#include <stdio.h>

/* FIXME: something wrong here. */
void Bresenhamline1(int x0, int y0, int x1, int y1, int color)
{ 
    int i;
	int x, y, dx, dy;
	float k, e;

	dx = x1 - x0;
    dy = y1 - y0;
    k  = dy/dx;

	e = -0.5;
    x = x0;
    y = y0;

	for( i = 0; i <= dx; i++) {
		//drawpixel (x, y, color);
        printf("[%d, %d] ", x, y);
		x = x + 1;
		e = e + k;
		if ( e >= 0) {
            y++;
            e = e - 1;
        }
	}

    printf("\n");
}

void Bresenhamline2(int x0, int y0, int x1, int y1, int color)
{
    int i;
    int x, y, dx, dy;
    float k, e;

    dx = x1 - x0; 
    dy = y1 - y0;
    k  = dy/dx;

    e = -dx;
    x = x0;
    y = y0;

    for(i = 0; i <= dx; i++) { 
        //drawpixel(x, y, color);
        printf("[%d, %d] ", x, y);
        x = x + 1;
        e = e + 2 * dy;
        if (e >= 0) { 
            y++; 
            e = e - 2 * dx;
        }
    }

    printf("\n");

}

int main()
{
    Bresenhamline1(0, 0, 20, 10, 1);
    Bresenhamline2(0, 0, 20, 10, 1);
    return 0;
}
