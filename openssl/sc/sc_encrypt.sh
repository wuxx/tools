#!/bin/bash

cipher_list=$(openssl enc --help 2>&1 | sed '1,/Cipher Types/d')

out_dir="./sc_ciphertext_out"

key="1234567890"
ifile="../plaintext.txt"

#echo $cipher_list

for cipher in $cipher_list
do
    echo "$cipher"
    openssl enc $cipher -pass pass:$key -in $ifile -out $out_dir/ciphertext$cipher.txt
done
