#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int     glvar = 42;
int     bssvar;

char *mycrypt(const char *key, const char *salt)
{
  bssvar = 2;
  printf(".:: crypt redirected -key- = %s (%u .::. %u) \n", 
        key, glvar, bssvar);
  exit(0);
}
