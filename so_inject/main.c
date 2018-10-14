#include <stdio.h>

extern int lib_func1(int x, int y);


int main()
{
    int *addr;
    int var;
    var = lib_func1(100, 200);
    printf("var: %d\n", var);

#if 0
    addr = (int *)lib_func1;

    addr[0] = 0x12345678;
#endif

    return 0;
}
