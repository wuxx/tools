#!/bin/bash

digest_list=$(openssl dgst --help 2>&1 | grep "to use the" | awk '{print $1}')

echo $digest_list

out_dir="./digest_out"

key="1234567890"
ifile="../plaintext.txt"

#echo $cipher_list

for digest in $digest_list
do
    echo "$digest"
    openssl dgst $digest $ifile > $out_dir/digest$digest.txt
done
