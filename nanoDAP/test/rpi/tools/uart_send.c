#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(int argc, char **argv)
{
	int fd;

	if(wiringPiSetup() < 0) {
        return 1;
    }

    if (argv[1] == NULL) {
        printf("usage: %s [string]\n", argv[0]);
        return 1;

    }

	//if((fd = serialOpen("/dev/ttyAMA0",115200)) < 0)return 1;
	if((fd = serialOpen("/dev/ttyS0",115200)) < 0)
        return 1;

	//printf("start send [%s]...\n", argv[1]);
	serialPrintf(fd, "%s\r\n", argv[1]);
	serialClose(fd);
	return 0;
}
