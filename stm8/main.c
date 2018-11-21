#include "stm8s.h"

#define __nop() __asm nop __endasm

void delay()
{
    unsigned int a, b;

    for(a=1000; a > 0; a--) {
        for(b=200; b>=0; b--) {
            __nop();
        }
    }
}

void main()
{
    PD_DDR = 0x02; /* D1 mode OUTPUT */
    PD_CR1 = 0x02; /* OUTPUT push-pull mode */

    while (1) {

        PD_ODR ^= 0x02; /* OUTPUT value */
        delay();
    }

}
