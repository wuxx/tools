#!/bin/bash

#cipher_list=$(openssl enc --help 2>&1 | sed '1,/Cipher Types/d')
cipher_list="-aes-128-cbc"

#echo $cipher_list

out_dir="./mac_out"

key="12345678901234567890123456789012"
ifile="../plaintext.txt"

#echo $cipher_list

for cipher in $cipher_list
do
    echo "$cipher"
    openssl dgst -mac cmac -macopt cipher:${cipher##-} -macopt hexkey:$key -sha1 $ifile > $out_dir/mac$cipher.txt
done

