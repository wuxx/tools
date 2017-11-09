CC = gcc
CFLAGS = -Wall -g

PLAINTEXT  = plaintext.txt

.PHONY: all

all:
	gcc hash_test.c -lssl -lcrypto -o hash_test
	gcc aes_test.c  -lssl -lcrypto -o aes_test
	gcc rsa_test.c  -lssl -lcrypto -o rsa_test

clean:	
	rm -rf hash_test aes_test rsa_test
