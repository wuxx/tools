CC = gcc

ROOT = .

CFLAGS = -Wall 

.PHONY: all

all: 
	$(CC) $(CFLAGS) actuator.c -lwiringPi -o actuator

clean:	
	-rm -f actuator
