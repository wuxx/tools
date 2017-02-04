#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void swap(int *a, int *b)
{
    char x;
    x  = *a;
    *a = *b;
    *b = x;
}

void permutation(int *a, int k,int m)  
{  
    int i,j;  
    if(k == m) {
        for(i = 0; i <= m; i++) {
            printf("%02d ", a[i]);
        }
        printf("\n");
    } else {
        for(j = k; j <= m; j++) {

            swap(&a[j],&a[k]);
            permutation(a,k+1,m);
            swap(&a[j],&a[k]);
        }
    }
}

#define get_bit(x, bit_index) ((x >> bit_index) & 0x1)

int main(int argc, char **argv)
{
    FILE *fp;
    int len, num;
    char line[1024] = {0};

    int input[9];

    if (argc != 2) {
        printf("%s ifile\n", argv[0]);
        exit(-1);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("fopen");
        exit(-1);
    }   

    fgets(line, sizeof(line), fp);

    while(!feof(fp)) {

        /* printf("get [%s]\n", line); */
        len = strlen(line);
        num =  (len - 1) / 3;   /* forget the '\n' */

        sscanf(line, "%d %d %d %d %d %d %d %d %d", 
                &input[0], &input[1], &input[2], &input[3], 
                &input[4], &input[5], &input[6], &input[7], 
                &input[8]);

        permutation(input, 0, num - 1);

        memset(line,  0, sizeof(line));
        memset(input, 0, sizeof(input));

        fgets(line, sizeof(line), fp);
    }

    fclose(fp);
    return 0;
}
