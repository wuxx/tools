#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char buf[32];
    FILE *fp;

    fp = fopen("bad.txt", "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    fread(buf, 1024, 1, fp);
    printf("data: %s\n", buf);

    return 0;
}
