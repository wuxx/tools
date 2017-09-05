#include <stdio.h>

#define GROUP_SIZE (64) /* in bytes */

int main(int argc, char **argv)
{

    FILE *fp;
    char *ifile;
    int i, x, size, len, count;
    int oaddr, addr;
    int buf[GROUP_SIZE / sizeof(int)] = {0};
    unsigned int checksum = 0;

    if (argc != 3) {
        printf("%s file addr\n", argv[0]);
        return -1;
    }

    ifile = argv[1];
    oaddr = addr = strtoul(argv[2], NULL, 0);
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
        fread(buf, sizeof(buf[0]), sizeof(buf) / sizeof(buf[0]), fp);
#if 0
        printf("fw 0x%08x 4 0x%08x 0x%08x 0x%08x 0x%08x\n",
                addr, buf[0], buf[1], buf[2], buf[3]);
#endif
        printf("w 0x%08x ", addr);
        for(x = 0; x < sizeof(buf) / sizeof(buf[0]); x++) {
            printf("0x%08x ", buf[x]);
        }
        printf("\n");

        addr += GROUP_SIZE;

        for(x = 0; x < sizeof(buf) / sizeof(buf[0]); x++) {
            checksum += buf[x];
        }
    }
    printf("cksum 0x%08x 0x%08x\n", oaddr, len / 4);

    printf("checksum: 0x%08x\n", checksum);
    fclose(fp);
    return 0;
}
