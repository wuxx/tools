
CC = gcc
#CFLAGS = -m32 -g
CFLAGS = -Wall -g

.PHONY: all

all: dev_mem test

dev_mem: dev_mem.c
	$(CC) $(CFLAGS) $< -o $@

test: test.c
	$(CC) $(CFLAGS) $< -o $@
clean:	
	rm -f dev_mem test
