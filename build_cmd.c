#include <stdio.h>

#define GROUP_SIZE (16)
int main(int argc, char **argv)
{

    FILE *fp;
    char *ifile;
    int i, size, len, count;
    int addr;
    int buf[4] = {0};

    if (argc != 3) {
        printf("%s file addr\n", argv[0]);
        return -1;
    }

    ifile = argv[1];
    addr  = strtoul(argv[2], NULL, 0);
    printf("ifile: [%s]\n", ifile);
    printf("addr : [0x%08x]\n", addr);

    if ((fp = fopen(ifile, "r+")) == NULL) {
        printf("fopen fail!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);
    len = ftell(fp);

    if ((len % GROUP_SIZE) != 0) {
        printf("file size must algn by %d bytes!\n", GROUP_SIZE);
        return -1;
    }

    fseek(fp, 0L, SEEK_SET);

    count = len / GROUP_SIZE;

    for(i = 0; i < count; i++) {
        fread(buf, sizeof(int), 4, fp);
        printf("fw 0x%08x 4 0x%08x 0x%08x 0x%08x 0x%08x\n",
                addr, buf[0], buf[1], buf[2], buf[3]);
        addr += GROUP_SIZE;
    }

    fclose(fp);
    return 0;
}
