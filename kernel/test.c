#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>


int g_var = 0x0badbeef;

int main()
{
    int l_var = 0xdeadbeef;

    printf("pid: %d \n", getpid());
    printf("g_var: [%p]: %x;\n", &g_var, g_var);
    printf("l_var: [%p]: %x;\n", &l_var, l_var);
    while(1) {
    };

    return 0;
}
