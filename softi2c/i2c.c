#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <wiringPi.h>
#include <unistd.h>


//void gpio_write()

/* wiringPi GPIO num */
#define GPIO_I2C_SCL   (25)
#define GPIO_I2C_SDA   (24)

#define SCL_SET(x) do {if(x) {digitalWrite(GPIO_I2C_SCL, HIGH);} else {digitalWrite(GPIO_I2C_SCL, LOW);}} while(0)

#define SDA_SET(x) do {if(x) {digitalWrite(GPIO_I2C_SDA, HIGH);} else {digitalWrite(GPIO_I2C_SDA, LOW);}} while(0)
#define SDA_GET()  digitalRead(GPIO_I2C_SDA)

#define SDA_OUTPUT() pinMode(GPIO_I2C_SDA, OUTPUT)
#define SDA_INPUT()  pinMode(GPIO_I2C_SDA, INPUT)

#define DELAY   (10)

void i2c_start()
{
    SDA_OUTPUT();

    SDA_SET(1);
    usleep(DELAY);

    SCL_SET(1);
    usleep(DELAY);

    SDA_SET(0);
    usleep(DELAY);
}

void i2c_stop()
{
    SDA_OUTPUT();

    SDA_SET(0);
    usleep(DELAY);

    SCL_SET(1);
    usleep(DELAY);

    SDA_SET(1);
    usleep(DELAY);
}

uint8_t i2c_send_ack(uint8_t ack)
{
    SDA_OUTPUT();

    SCL_SET(0);

    if (ack == 1) {
        SDA_SET(1);   /* NACK */
    } else if (ack == 0) { 
        SDA_SET(0); /* ACK */
    }

    SCL_SET(1);
    usleep(DELAY);
    SCL_SET(0);   //SCL = 0;
    usleep(DELAY);

}

uint8_t i2c_recv_ack()
{
    uint8_t ack;

    SDA_INPUT();

    SDA_SET(1);
    usleep(DELAY);

    SCL_SET(1);
    usleep(DELAY);

    if (SDA_GET() == 1) {
        ack = 1;
    } else {
        ack = 0;
    }

    SCL_SET(0);
    usleep(DELAY);

    return ack;
}

uint8_t i2c_send(uint8_t data)
{
    uint8_t i, rv;
    SDA_OUTPUT();

    SCL_SET(0);
    usleep(DELAY);

    for(i = 0; i < 8; i++) {

        if ((data << i) & 0x80) {
            SDA_SET(1);
        } else {
            SDA_SET(0);
        }

        usleep(DELAY);

        SCL_SET(1);
        usleep(DELAY);
        SCL_SET(0);
        usleep(DELAY);
    }

    rv = i2c_recv_ack();

    if (rv) {
        printf("%s-%d fail\n", __func__, __LINE__);
    }

    return rv;

}

uint8_t i2c_recv()
{
    uint8_t i, data = 0;

    SDA_INPUT();

    SCL_SET(1);
    usleep(DELAY);

    for(i = 0; i < 8; i++) {
        data <<= 1;
        data = data | (SDA_GET());
        usleep(DELAY);
        
        SCL_SET(0);
        usleep(DELAY);
        SCL_SET(1);
        usleep(DELAY);
    }

    return data;
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

    uint8_t addr, rv;

    if (wiringPiSetup() < 0) {
        fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
        return 1;
    }

    /* wiringPi GPIO num */
    pinMode(GPIO_I2C_SCL, OUTPUT);
    pinMode(GPIO_I2C_SDA, OUTPUT);

    for(addr = 0; addr < 0xff; addr++) {

        printf("0x%x ", addr);

        i2c_start();

        rv = i2c_send(addr);

        if (rv) {
            printf("fail!\n");
        } else {
            printf("succ!\n");
        }

        i2c_stop();
    }

    return 0;
}
