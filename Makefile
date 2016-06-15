
#CFLAGS = -m32 -g
CFLAGS = -Wall -g

.PHONY: all

all: hextool

hextool: hextool.c
	gcc $(CFLAGS)  $< -o hextool
	cp hextool hexdump
	cp hextool hexedit

clean:	
	rm -f hextool hexdump hexedit tags *.bin
