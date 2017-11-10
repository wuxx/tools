#!/bin/bash

openssl genrsa -out rsa_private_key.pem 2048
openssl rsa -in rsa_private_key.pem -pubout -out rsa_public_key.pem

./all_test rsa_public_key.pem rsa_private_key.pem
