#include <stdio.h>
#include <string.h>


//char *s="https://muselab-tech.aliexpress.com";

char *s="https://miusecn-muselab-tech.aliexpress.com";

int main()
{
    int i, len;
    len = strlen(s);

    for (i = 0; i < len; i++) {

        if ((i != 0) && (i % 4 == 0)) {
            printf("\n");
        }

        printf("0x%02x, ", s[i] ^ 0x55);
    }

    return 0;
}

