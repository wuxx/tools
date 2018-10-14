#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>
#include <errno.h>

#define GPIO_CTRL   (25)

/* 0.5ms -> 0   */
/* 1.0ms -> 45  */
/* 1.5ms -> 90  */
/* 2.0ms -> 135 */
/* 2.5ms -> 180 */

int angle_ctrl(int ang)
{
    int count = 1;
    int us_1, us_0;
    switch(ang) {
        case (0):
            while(count--)
            {
                digitalWrite(GPIO_CTRL, HIGH);
                delayMicroseconds(500);
                digitalWrite(GPIO_CTRL, LOW);
                delayMicroseconds(19500);
            }
            break;
        case (45):
            while(count--)
            {
                digitalWrite(GPIO_CTRL, HIGH);
                delayMicroseconds(1000);
                digitalWrite(GPIO_CTRL, LOW);
                delayMicroseconds(19000);
            }
            break;
        case (90):
            while(count--)
            {
                digitalWrite(GPIO_CTRL, HIGH);
                delayMicroseconds(1500);
                digitalWrite(GPIO_CTRL, LOW);
                delayMicroseconds(19000);
            }
            break;
        case (135):
            while(count--)
            {
                digitalWrite(GPIO_CTRL, HIGH);
                delayMicroseconds(2000);
                digitalWrite(GPIO_CTRL, LOW);
                delayMicroseconds(19000);
            }
            break;
        case (180):
            while(count--)
            {
                digitalWrite(GPIO_CTRL, HIGH);
                delayMicroseconds(2500);
                digitalWrite(GPIO_CTRL, LOW);
                delayMicroseconds(17500);
            }
            break;

        default:
            while(count--)
            {
                us_1 = ((ang * 1000) / 90);
                us_1 = us_1 + 500;
                us_0 = 20000 - us_1;
                printf("[%d, %d]\n", us_1, us_0);
                digitalWrite(GPIO_CTRL, HIGH);
                delayMicroseconds(us_1);
                digitalWrite(GPIO_CTRL, LOW);
                delayMicroseconds(us_0);
            }
            break;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int angle;

    if (argv[1] == NULL) {
		fprintf(stderr, "usage: %s [angle]\n", argv[0]);
		return 1;
    }

	if (wiringPiSetup() < 0) {
		fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
		return 1;
	}

    angle = atoi(argv[1]);
	pinMode(GPIO_CTRL, OUTPUT);

	angle_ctrl(angle);

	return 0;
}
