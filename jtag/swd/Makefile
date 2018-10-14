CC = gcc

ROOT = .

INCLUDE=$(ROOT)/locallib/include/raspidmx

CFLAGS = -Wall -I$(INCLUDE) 

.PHONY: all

all: 
	$(CC) $(CFLAGS) -c gpio.c -o gpio.o
	$(CC) $(CFLAGS) -c swd.c  -o swd.o
	$(CC) gpio.o swd.o $(ROOT)/locallib/lib/libwiringPi.a -lpthread -o swd_gpio

clean:	
	-rm -f *.o
	-rm -f swd_gpio
