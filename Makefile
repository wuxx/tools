
CC = gcc
#CFLAGS = -m32 -g
CFLAGS = -Wall -g

.PHONY: all

all: hextool hex_cat readcap jbdump

hextool: hextool.c
	$(CC) $(CFLAGS) $< -o hextool
	cp hextool hexdump
	cp hextool hexedit

hex_cat: hex_cat.c
	$(CC) $(CFLAGS) $< -o hex_cat

readcap: readcap.c
	$(CC) $(CFLAGS) $< -o readcap

jbdump: jbdump.c
	$(CC) $(CFLAGS) $< -o jbdump

hexgrep: hexgrep.c
	$(CC) $(CFLAGS) $< -o hexgrep

clean:	
	rm -f hextool hexdump hexedit hex_cat readcap jbdump tags *.bin
