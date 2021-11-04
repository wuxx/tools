#include <stdio.h>

//char *s="first,25.5,second,15";

char *s1="<Idle,MPos:6.000,6.000,0.000,WPos:5.000,5.000,0.000,SC:0>\n";

char *s2="<Idle|MPos:1.000,2.000,0.000|FS:0,0|Pn:P|WCO:5.000,0.000,0.000>\n";

int main()
{
    char dummy[64][64];
    char a[64], b[64], c[64], d[64];
    char e[64], f[64], g[64], h[64];
    float x, y;


#if 0
    //sscanf(s, "%[^','],MPos:%[^',']f,%[^',']f,%[^','],WPos:%[^','],%[^','],%s", a, x, y, d, e, f, g);
    sscanf(s, "%[^','],MPos:%f,%f,%[^','],WPos:%[^','],%[^','],%s", a, &x, &y, d, e, f, g);
    printf("a: [%s]\n", a);

    //printf("b: [%s]\n", b);
    //printf("c: [%s]\n", c);

    printf("x: [%.3f]\n", x);
    printf("y: [%.3f]\n", y);

    printf("d: [%s]\n", d);
    printf("e: [%s]\n", e);
    printf("f: [%s]\n", f);
    printf("g: [%s]\n", g);
#endif

    sscanf(s2, "%[^'|']|MPos:%f,%f,%s", a, &x, &y, d);
    printf("a: [%s]\n", a);


    printf("x: [%.3f]\n", x);
    printf("y: [%.3f]\n", y);

    printf("d: [%s]\n", d);

}
