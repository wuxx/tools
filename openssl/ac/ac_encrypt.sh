#!/bin/bash

key_dir="./key"
out_dir="./ac_ciphertext_out"

ifile="../plaintext.txt"

public_key_rsa="./key/public_key_rsa.txt"
private_key_rsa="./key/private_key_rsa.txt"
ciphertext_rsa="./ac_ciphertext_out/ciphertext_rsa.txt"

#rsa
#1. generate private key
openssl genpkey -algorithm RSA -out $private_key_rsa -pkeyopt rsa_keygen_bits:1024

#2. generate public key
openssl rsa -pubout -in $private_key_rsa -out $public_key_rsa

#3. encrypt
openssl rsautl -encrypt -in $ifile -inkey $public_key_rsa -pubin -out $ciphertext_rsa
