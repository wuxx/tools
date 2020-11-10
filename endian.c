#include <stdio.h>
#include <stdint.h>

#define BYTE_SWAP(x) ( (((uint8_t)(x)) << 8) | ((uint8_t)(x >> 8)) )

int main()
{
    unsigned short x = 0x1234;

    printf("0x%x\r\n", BYTE_SWAP(x));
    return 0;
}
