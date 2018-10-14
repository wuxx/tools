#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    int x;
    unsigned int hex;

    if (argc == 1) {
        printf("usage: %s [hex_num]\n", argv[0]);
        return 1;
    }

    hex = strtoul(argv[1], NULL, 0);
    x = (int)hex;

    printf("hex: 0x%x\n", hex);
    printf("int: %d\n", x);

    return 0;
}
