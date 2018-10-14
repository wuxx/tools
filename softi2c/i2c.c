#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <wiringPi.h>


//void gpio_write()

/* wiringPi GPIO num */
#define GPIO_I2C_SCL   (25)
#define GPIO_I2C_SDA   (24)

//#define BIT_TIME_US 104 /* 9600 baud */
//#define BIT_TIME_US 833 /* 1200 baud */

//#define BIT_TIME_US     (1000000 / 600) /* 600 baud */
#define BIT_TIME_US     (1000000 / 300) /* 300 baud */

#define UART_GPIO_SET(x) do {if(x) {digitalWrite(UART_GPIO, HIGH);} else {digitalWrite(UART_GPIO, LOW);}} while(0)

#define SCL_SET(x) do {if(x) {digitalWrite(GPIO_I2C_SCL, HIGH);} else {digitalWrite(GPIO_I2C_SCL, LOW);}} while(0)
#define SCL_GET()  digitalRead(GPIO_I2C_SCL) /* FIXME: config mode to input */

#define SDA_SET(x) do {if(x) {digitalWrite(GPIO_I2C_SDA, HIGH);} else {digitalWrite(GPIO_I2C_SDA, LOW);}} while(0)
#define SDA_GET()  digitalRead(GPIO_I2C_SDA)

void i2c_start()
{
    SCL_SET(1);
    SDA_SET(1);

    SDA_SET(0);
    SCL_SET(0);
}

void i2c_stop()
{
    SCL_SET(0);
    SDA_SET(0);

    SCL_SET(1);
    SDA_SET(1);
}

void i2c_writeb(unsigned char byte)
{
	unsigned char i;
    unsigned char ack;

	for(i = 0; i < 8; i++) {
		if(byte & 0x80) {
			SDA_SET(1);
		} else {
		    SDA_SET(0);
		}

		SCL_SET(1);
		SCL_SET(0);
		byte <<= 1;
	}

	SDA_SET(1);
	SCL_SET(1);
	SCL_SET(0);
}

int i2c_init()
{

    if (wiringPiSetup() < 0) {
        fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
        return 1;
    }

    /* wiringPi GPIO num */
    pinMode(GPIO_I2C_SCL, OUTPUT);
    pinMode(GPIO_I2C_SDA, OUTPUT);

    return 0;
}
