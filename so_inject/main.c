#include <stdio.h>

extern int lib_func1(int x, int y);


int main()
{
    int *addr;
    int var;
    var = lib_func1(100, 200);
    printf("var: %d\n", var);

    addr = (int *)lib_func1;

    addr[0] = 0x12345678;

    return 0;
}
