#include <stdio.h>
#include <stdlib.h>

#define GROUP_SIZE (64) /* in bytes */

int main(int argc, char **argv)
{
    unsigned int data;
    data = strtoul(argv[1], NULL, 16);
    printf("data: [0x%08x]\n", data);
    return 0;
}
