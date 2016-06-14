
#CFLAGS = -m32 -g
CFLAGS = -Wall -g

.PHONY: all

all: hextool

hextool: hextool.c
	gcc $(CFLAGS)  $< -o $@

clean:	
	rm -f hextool tags *.bin
