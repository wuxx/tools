#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>


/* gcc uart_send.c -lwiringPi -o uart_send */
int main(int argc, char **argv)
{
	int fd;

	if(wiringPiSetup() < 0) {
        return 1;
    }

    if (argv[1] == NULL) {
        printf("usage: %s [serial_port] [string]\n", argv[0]);
        return 1;

    }

	//if((fd = serialOpen("/dev/ttyAMA0",115200)) < 0)return 1;
	if((fd = serialOpen(argv[1],115200)) < 0) {
        printf("serialOpen fail!\n");
        return 1;
    }

	printf("start send [%s]...\n", argv[2]);
	serialPrintf(fd, "%s\n", argv[2]);
	serialClose(fd);
	return 0;
}
