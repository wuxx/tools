#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <wiringPi.h>

extern int i2c_init();

int main()
{

    i2c_init();

    return 0;
}
