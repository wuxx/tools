#!/bin/bash

help() {
    echo "usage: $0 "
    echo -e "\t\t--ca-level [0,1,2] "
    echo -e "\t\t--help"
}

CA_LEVEL="1"

while [ ! -z "$1" ]; do
    case "$1" in
        "--ca-level")
            shift
            CA_LEVEL="$1"
            shift
            ;;  
        "--server")
            shift
            ;;  
        "--client")
            shift
            ;;  
        "--help")
            help
            shift
            exit 0
            ;;  
        *)  
            echo "illegal param $1"
            shift
            help
            exit 1
            ;;  
    esac
done

case "$CA_LEVEL" in
    "0")
        #level 0 CA

        CA0_DIR=./demoCA

        mkdir -p $CA0_DIR/private
        mkdir -p $CA0_DIR/newcerts

        touch $CA0_DIR/index.txt
        echo 01 > $CA0_DIR/serial
        cp ./demoCA.cnf ./$CA0_DIR/demoCA.cnf
        openssl genrsa -des3 -out $CA0_DIR/private/cakey.pem 2048
        #openssl req -new -x509 -config $CA0_DIR/demoCA.cnf -key $CA0_DIR/private/cakey.pem -out $CA0_DIR/careq.pem -days 3650 -passin pass:123456 
        openssl req -new -x509 -config /etc/ssl/openssl.cnf -key $CA0_DIR/private/cakey.pem -out $CA0_DIR/careq.pem -days 3650 -passin pass:123456 
        ;;  
    "1")
        #level 1 CA
        CA1_NAME="ca1"
        CA1_DIR=./ca1

        mkdir -p $CA1_DIR
        cp ./openssl.cnf $CA1_DIR/$CA1_NAME.cnf
        
        openssl genrsa -des3 -out $CA1_DIR/$CA1_NAME.key 2048
        openssl rsa -in $CA1_DIR/$CA1_NAME.key -out $CA1_DIR/$CA1_NAME.key
        openssl req -new -days 3650 -key $CA1_DIR/$CA1_NAME.key -out $CA1_DIR/$CA1_NAME.csr
        #openssl ca -extensions v3_ca -in $CA1_DIR/$CA1_NAME.csr -config $CA1_DIR/$CA1_NAME.cnf -days 3000 -out $CA1_DIR/$CA1_NAME.crt -cert $CA0_DIR/careq.pem -keyfile $CA0_DIR/private/cakey.pem
        #openssl ca -extensions v3_ca -in $CA1_DIR/$CA1_NAME.csr -config /etc/ssl/openssl.cnf -days 3000 -out $CA1_DIR/$CA1_NAME.crt -cert $CA0_DIR/careq.pem -keyfile $CA0_DIR/private/cakey.pem
        openssl ca -extensions v3_ca -in ./ca1/ca1.csr -days 3000 -out ./ca1/ca1.crt -cert ./demoCA/careq.pem -keyfile ./demoCA/private/cakey.pem 
        ;;  
    *)  
        echo "illegal CA_LEVEL [$CA_LEVEL]"
        exit 1
        ;;  
esac

