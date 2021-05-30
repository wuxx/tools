#include <stdio.h>
#include <string.h>

char *s = "https://muselab-tech.aliexpress.com";

int main()
{
    int i;
    int len = strlen(s);
    char out[64] = {0};

    for (i = 0; i < len; i++) {
        printf("%02x, ", s[i] ^ 0x55);
    }

    printf("\r\n");

}
