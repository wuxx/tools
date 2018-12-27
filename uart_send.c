#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>


/* gcc uart_send.c -lwiringPi -o uart_send */
int main(int argc, char **argv)
{
	int fd;
<<<<<<< HEAD

	if(wiringPiSetup() < 0) {
=======
    int count = 0;

	if(wiringPiSetup() < 0) {
        printf("wiringPiSetup fail!\n");
>>>>>>> 3fec14219e625d7cedd8624dd663a406bf7ad7c9
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

<<<<<<< HEAD
	printf("start send [%s]...\n", argv[2]);
	serialPrintf(fd, "%s\n", argv[2]);
=======
    sleep(5);

    while (1) {
        printf("[%d]\n", count);

        printf("start send [G1 Z10]...\n");
        serialPrintf(fd, "G1 Z10\n");

        sleep(3);

        printf("start send [G1 Z0]...\n");
        serialPrintf(fd, "G1 Z0\n");

        sleep(3);

        count++;
    }


>>>>>>> 3fec14219e625d7cedd8624dd663a406bf7ad7c9
	serialClose(fd);
	return 0;
}
