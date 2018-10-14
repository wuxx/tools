
CC = gcc
CFLAGS = -Wall -lcrypto

.PHONY: all

all: 
	$(CC) sha1.c -o sha1 $(CFLAGS) 
	$(CC) combination.c -o combination
	$(CC) permutation.c -o permutation

run: 
	./combination > c.txt
	./permutation c.txt > p.txt
	./sha1 p.txt > s.txt


clean:	
	rm -f sha1
