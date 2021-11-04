#include <stdio.h>


char *s="192.168.123.240:23";

int main()
{
    char ip[128];
    int port = 0;
    int ret;

    if ((ret = sscanf(s, "%[^:]:%d", ip, &port)) == 2) {
        printf("ip: [%s]; port: [%d]\n", ip, port);

    } else {
        printf("failed %d\n", ret);
        printf("ip: [%s]; port: [%d]\n", ip, port);
    }
}
