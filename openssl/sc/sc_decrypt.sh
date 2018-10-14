#!/bin/bash

cipher_list=$(openssl enc --help 2>&1 | sed '1,/Cipher Types/d')

ciphertext_dir="./sc_ciphertext_out"
plaintext_dir="./sc_plaintext_out"

key="1234567890"
ifile="../plaintext.txt"

ifiles=$(ls $ciphertext_dir/*)

for ifile in $ifiles
do
    file_name=$(basename $ifile)
    cipher_pre=${file_name##ciphertext}
    cipher=${cipher_pre%%.txt}
    echo "$cipher"
    openssl enc -d $cipher -pass pass:$key -in $ifile -out $plaintext_dir/plaintext$cipher.txt
done
