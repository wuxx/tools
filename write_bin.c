#include <stdio.h>
#include <stdint.h>

uint8_t array[1024]  = {0x00, 0x02};

int main()
{
    write(1, array, sizeof(array));
    return 0;
}
