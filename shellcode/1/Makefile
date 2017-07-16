
CC = gcc
CFLAGS = -Wall -g -fno-stack-protector -m32 -Wl,-zexecstack

.PHONY: all

all: stack1

stack1: stack1.c
	$(CC) $(CFLAGS) -o $@ $<

ulimit:
	ulimit -c unlimited
	ulimit unlimited

test:
	perl -e 'printf "A"x40 . "B"x4' > bad.txt ; ./stack1

clean:	
	rm -f stack1
