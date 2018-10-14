#include <stdio.h>

/*
from http://blog.sina.com.cn/s/blog_73428e9a01016gnp.html
*/

/*
http://st251256589.blog.163.com/blog/static/16487644920114112817666/
 */

void Bresenhamline0(int x0, int y0, int x1, int y1, int color)
{ 
    int i;
	int x, y, dx, dy;
	float k, d;

	dx = x1 - x0;
    dy = y1 - y0;
    k  = ((float)dy) / ((float)dx);

	d = 0;
    x = x0;
    y = y0;

    printf("k: %lf\n", k);

	for( i = 0; i <= dx; i++) {
		//drawpixel (x, y, color);
        printf("[%d, %d]\n", x, y);
		x = x + 1;
		d = d + k;

        if (d >= 1) {
            d = d - 1;
        }

        printf("d: %lf\n", d);
		if (d >= 0.5) {
            y++;
        }

	}

    printf("\n");
}

void Bresenhamline01(int x0, int y0, int x1, int y1, int color)
{ 
    int i;
	int x, y, dx, dy;
	float k, d;

	dx = x1 - x0;
    dy = y1 - y0;
    k  = ((float)dy) / ((float)dx); // k -> [0, 1]

	d = 0;
    x = x0;
    y = y0;

	for( i = 0; i <= dx; i++) {
		//drawpixel (x, y, color);
        printf("[%d, %d]\n", x, y);
		x = x + 1;
		d = d + k; // e -> [-0.5, 0.5]


		if (d >= 0.5) {
            y++;
            d = d - 1;
        }

	}

    printf("\n");
}

void Bresenhamline1(int x0, int y0, int x1, int y1, int color)
{ 
    int i;
	int x, y, dx, dy;
	float k, e;

	dx = x1 - x0;
    dy = y1 - y0;
    k  = ((float)dy) / ((float)dx);

	e = -0.5;
    x = x0;
    y = y0;

	for( i = 0; i <= dx; i++) {
		//drawpixel (x, y, color);
        printf("[%d, %d]\n", x, y);
		x = x + 1;
		e = e + k;

		if (e >= 0) {
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
    k  = ((float)dy) / ((float)dx);

    e = -dx;
    x = x0;
    y = y0;

    for(i = 0; i <= dx; i++) { 
        //drawpixel(x, y, color);
        printf("[%d, %d]\n", x, y);
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
    int x0, y0, x1, y1;
    x0 = y0 = 0;
    x1 = 50;
    y1 = 2;

    printf("%s-%d-0\n", __func__, __LINE__);
    Bresenhamline0(0, 0, x1, y1, 1);

    printf("%s-%d-01\n", __func__, __LINE__);
    Bresenhamline01(0, 0, x1, y1, 1);

    printf("%s-%d-1\n", __func__, __LINE__);
    Bresenhamline1(0, 0, x1, y1, 1);

    printf("%s-%d-2\n", __func__, __LINE__);
    Bresenhamline2(0, 0, x1, y1, 1);
    return 0;
}
