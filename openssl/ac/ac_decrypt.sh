#!/bin/bash

key_dir="./key"
out_dir="./ac_ciphertext_out"

ifile="../plaintext.txt"

public_key_rsa="./key/public_key_rsa.txt"
private_key_rsa="./key/private_key_rsa.txt"
ciphertext_rsa="./ac_ciphertext_out/ciphertext_rsa.txt"
plaintext_rsa="./ac_plaintext_out/plaintext_rsa.txt"

#rsa

#1. decrypt
openssl rsautl -decrypt -in $ciphertext_rsa -inkey $private_key_rsa -out $plaintext_rsa
