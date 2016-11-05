CC = gcc
CFLAGS = -Wall -g

PLAINTEXT  = plaintext.txt

.PHONY: all

all: encrypt digest

encrypt: sc_encrypt ac_encrypt

decrypt: sc_decrypt ac_decrypt

sc_encrypt:
	@echo "$@"
	cd sc && sh sc_encrypt.sh

sc_decrypt:
	@echo "$@"
	cd sc && sh sc_decrypt.sh

ac_encrypt:
	@echo "$@"
	cd ac && sh ac_encrypt.sh

ac_decrypt:
	@echo "$@"
	cd ac && sh ac_decrypt.sh

digest:
	@echo "$@"
	cd dgst && sh digest.sh

clean:	
	rm -rf sc/ciphertext_out/* sc/plaintext_out/* ac/ciphertext_out/* ac/plaintext_out/* dgst/digest_out/*
