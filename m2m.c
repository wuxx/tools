#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* convert mm to mil or mil to mm */

void usage(char *program_name)
{
    printf("%s [ xxxmm | xxxmil ]\n", program_name);
    exit(1);
}

/* 1 inch = 2.54 cm */
/* 1000 mil = 25.4 mm */
/* 1000 / 25.4 mil = 1 mm */
/* 1 mil = 25.4 / 1000 mm */

int main(int argc, char **argv)
{
    float mm, mil;
    char *unit = NULL;

    if (argc == 1) {
        usage(argv[0]);
    }

    unit = strchr(argv[1], 'm');

    if (unit == NULL) {
        usage(argv[0]);
    }

    if (strcmp(unit, "mm") == 0) {
        *unit = '\0';
        //printf("argv[1]: %s\n", argv[1]);
        sscanf(argv[1], "%f", &mm);
        mil = mm * 1000.0 / 25.4;

    } else if (strcmp(unit, "mil") == 0) {
        *unit = '\0';
        //printf("argv[1]: %s\n", argv[1]);
         sscanf(argv[1], "%f", &mil);
         mm  = mil * 25.4 / 1000;

    } else {
        usage(argv[0]);
    }
    printf("%f mm\n",  mm);
    printf("%f mil\n", mil);

    return 0;
}
