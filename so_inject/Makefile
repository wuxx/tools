
CC = gcc
#CFLAGS = -m32 -g
CFLAGS = -Wall -g

PWD=$(shell pwd -P)

SHELLCODE_SRC  = shellcode2.s shellcode3.s shellcode4.s shellcode5.s
SHELLCODE_OBJ  = $(patsubst %.s,%.o,$(SHELLCODE_SRC))
SHELLCODE_ELF  = $(patsubst %.s,%.elf,$(SHELLCODE_SRC))
.PHONY: all shellcode

all: 
	gcc -m32 -shared -fPIC lib_test.c -o libtest.so
	gcc -m32 main.c -o main -L./ -Wl,-rpath=$(PWD) -ltest
	#gcc -m32 main.c -o main -L ./ -ltest

disasm: 
	objdump -d libtest.so > libtest.asm
	objdump -d main > main.asm

shellcode: $(SHELLCODE_OBJ) $(SHELLCODE_ELF)

$(SHELLCODE_OBJ): %.o: %.s
	as --32 $< -o $@
	#objcopy shellcode2.o -O binary shellcode2.bin
	#ld shellcode2.o -o shellcode2

$(SHELLCODE_ELF): $(SHELLCODE_OBJ)
$(SHELLCODE_ELF): %.elf : %.o
	ld -m elf_i386 -o $@ $<

helloworld: 
	nasm -f elf hello.S
	ld -m elf_i386 -o hello hello.o

run: 
	LD_LIBRARY_PATH=./ ./main

clean:	
	rm -f libtest.so main
