CC = gcc

ROOT = .

CFLAGS = -Wall -I./locallib/include/wiringPi

.PHONY: all

all: 
	$(CC) $(CFLAGS) uart_send.c ./locallib/lib/libwiringPi.a -lpthread -o uart_send

clean:	
	-rm -f uart_send
