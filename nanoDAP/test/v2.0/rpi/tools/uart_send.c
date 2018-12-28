#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	int fd;
    int i, count;
    char buf[1024] = {0};
    int debug = 0;

	if(wiringPiSetup() < 0) {
        return 1;
    }

    if (argv[1] == NULL) {
        printf("usage: %s [string]\n", argv[0]);
        return 1;
    }
    if ((argv[2] != NULL) && (strcmp(argv[2], "-d") == 0)) {
        debug = 1;
    }

	//if((fd = serialOpen("/dev/ttyAMA0",115200)) < 0)return 1;
	if((fd = serialOpen("/dev/ttyS0",115200)) < 0)
        return 1;

	//printf("start send [%s]...\n", argv[1]);
	serialPrintf(fd, "%s\r\n", argv[1]);
    usleep(100000);

    count = serialDataAvail(fd);

    if (count > sizeof(buf)) {
        count = sizeof(buf);
    }

    for(i = 0; i < count; i++) {
        buf[i] = (char)serialGetchar(fd);
        //printf("[%d]: %c\n", i, buf[i]);
    }

    if (debug) {
        printf("[%s]\n", buf);
    }

	serialClose(fd);
	return 0;
}
