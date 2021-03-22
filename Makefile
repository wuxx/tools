
#CURRENT_DIR=$(cd $(dirname $0); pwd)
CURRENT_DIR=$(shell pwd)



mkfile_path       := $((abspath $(lastword $(MAKEFILE_LIST)))  #获取当前正在执行的makefile的绝对路径
cur_makefile_path := $(dir $(mkfile_path)) #
CURRENT_DIR       := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

$(warning mkfile_path ${mkfile_path} )
$(warning cur_makefile_path ${cur_makefile_path} )
$(warning CURRENT_DIR ${CURRENT_DIR} )

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

test: 
	echo test

clean:	
	rm -f hextool hexdump hexedit hex_cat readcap jbdump tags *.bin
