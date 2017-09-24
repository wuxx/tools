#include <stdio.h>

void foo()
{
    printf("foo\n");
}

void test()
{
    foo();
}

int main()
{
    printf("hello!\n");
    test();
    return 100;
}
