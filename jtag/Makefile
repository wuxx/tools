
CC = gcc
#CFLAGS = -m32 -g
CFLAGS = -Wall -g

.PHONY: all

all: 
	#$(CC) $(CFLAGS) jtag_gpio.c -o jtag_gpio
	$(CC) $(CFLAGS) swd_gpio.c -o swd_gpio

clean:	
	#-rm -f jtag_gpio
	-rm -f swd_gpio
