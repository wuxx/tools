
CC = gcc
OBJDUMP = objdump
#READELF = readelf
READELF = /home/pi/share/oss/binutils-2.24/binutils/readelf
CFLAGS = -Wall -O3 -funwind-tables -g

.PHONY: unwind

unwind: unwind.c
	$(CC) $(CFLAGS) $< -o $@
	$(OBJDUMP) -d $@ > $@.disasm
	$(READELF) -a $@ > $@.elfinfo

clean:	
	rm -f unwind unwind.disasm unwind.elfinfo
