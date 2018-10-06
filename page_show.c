#include <stdio.h>
#include <stdint.h>

/* stm32f103c8t6 */
uint32_t start = 0x08000000;
uint32_t size  = 64 * 1024;
uint32_t page_size = 1 * 1024;

int main()
{
    int i, page_num;
        
    page_num =  size / page_size;
    for(i = 0; i < page_num; i++) 
    {
        printf("page[%d]: [0x%08x - 0x%08x]\n", i, start + page_size * i, start + page_size * (i + 1) - 1);
    }

    return 0;
}
