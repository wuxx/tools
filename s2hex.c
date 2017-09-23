#include <stdio.h>
#include <string.h>

unsigned int buf[1024];

int main(int argc, char **argv)
{
    int i;
    char *s;

    if (argv[1] == NULL) {
        printf("%s [string]\n", argv[0]);
        return 0;
    }

    s = argv[1];

    printf("byte view:\n");
    for(i = 0; s[i] != 0; i++) {
        printf("[%d]: 0x%02x (%c)\n", i, s[i], s[i]);
    }

    memcpy(buf, s, strlen(s));  /* FIXME: buf overflow! */

    i = 0;

    printf("word view:\n");
    while(buf[i] != 0) {

        printf("[%d]: 0x%08x\n", i, buf[i++]);
    }

    return 0;
}
