
CC = gcc
#CFLAGS = -m32 -g
CFLAGS = -Wall -g

.PHONY: all

all: hextool hex_cat

hextool: hextool.c
	$(CC) $(CFLAGS) $< -o hextool
	cp hextool hexdump
	cp hextool hexedit

hextool: hex_cat.c
	$(CC) $(CFLAGS) $< -o hex_cat

clean:	
	rm -f hextool hexdump hexedit hex_cat tags *.bin
