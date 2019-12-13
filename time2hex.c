#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char *time = __TIME__;


static uint32_t time2hex(char *time)
{
    char ascii[3] = {0};
    uint8_t hour, min, sec;

    strncpy(ascii, &time[0], 2);
    printf("ascii: %s\r\n", ascii);
    hour = atoi(ascii);
    hour = (hour / 10) * 16 + (hour % 10);

    strncpy(ascii, &time[3], 2);
    printf("ascii: %s\r\n", ascii);
    min = atoi(ascii);
    min = (min / 10) * 16 + (min % 10);

    strncpy(ascii, &time[6], 2);
    printf("ascii: %s\r\n", ascii);
    sec = atoi(ascii);
    sec = (sec / 10) * 16 + (sec % 10);

    return (hour << 16) | (min << 8) | sec;
}

int main()
{
    printf("time: %s\n", time);

    printf("[%x]\n", time2hex(time));
    return 0;
}

