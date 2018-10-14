
CC = gcc
#CFLAGS = -m32 -g
CFLAGS = -Wall -g -l dbus-1 -I/usr/lib/arm-linux-gnueabihf/dbus-1.0/include/ -I/usr/include/dbus-1.0/

.PHONY: all

all:
	$(CC) $(CFLAGS) server.c -o server
	$(CC) $(CFLAGS) client.c -o client

clean:	
	rm -f hextool
