
CC = gcc
#CFLAGS = -m32 -g
CFLAGS = -Wall -g

.PHONY: all

#ulimit -c unlimited

all: 
	gcc test.c -g -o test

run: 
	./test

debug: 
	gdb test core

clean:	
	rm -f test core
