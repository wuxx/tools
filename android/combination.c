#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define get_bit(x, bit_index) ((x >> bit_index) & 0x1)

int main(void)
{
    int x, i, count;

    int bindex, len;
    char a[9] = {
                    0, 1, 2, 
                    3, 4, 5,
                    6, 7, 8,
                };

    char buf[128];

    count = 511 /* 2^9 - 1 */;

    for(x = 1; x <= count; x++) {

        bindex = 0;
        memset(buf, sizeof(buf), 0);

        for(i = 0; i < 32; i++) {
            if (get_bit(x, i) == 1) {
                len = sprintf(&buf[bindex], "%02d ", i);
                bindex += len;

            }
        }
        printf("%s\n", buf);
    }

    return 0;
}
