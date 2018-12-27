
CC = sdcc
#CFLAGS = -m32 -g
CFLAGS = -mstm8 --out-fmt-ihx

.PHONY: all

all: main

main: main.c
	$(CC) $(CFLAGS)  -o main.hex $<

flash:
	sudo stm8flash -c stlinkv2 -d -d /dev/ttyUSB0 -p stm8s103f3

clean:	
	rm -f hextool hexdump hexedit hex_cat readcap jbdump tags *.bin
