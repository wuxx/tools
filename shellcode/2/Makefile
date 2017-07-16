
CC = gcc
CFLAGS = -Wall -g

.PHONY: all

all: sctest

sctest:	
	$(CC) $(CFLAGS) -m32 -o sctest32 sctest.c
	$(CC) $(CFLAGS)      -o sctest   sctest.c

nasm:	
	nasm -o shell2 shell2.s
	od -t x1 shell2 | sed -e 's/[0-7]*//' | sed -e 's/ /\\x/g' | tr -d '\n'

test:
	 ./sctest32 ../shell2

clean:	
	rm -f sctest32 sctest
