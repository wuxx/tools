
CC = gcc
#CFLAGS = -m32 -g
CFLAGS = -Wall -g -lm

.PHONY: all

all:
	$(CC) $(CFLAGS) build_ppm.c -o build_ppm

convert:
	 convert MathPic.ppm MathPic.png

clean:	
	rm -f build_ppm MathPic.ppm
