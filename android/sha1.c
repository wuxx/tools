#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <openssl/sha.h>
 
char * sha1(char *buf, int size) 
{
    int i;
    unsigned char digest[SHA_DIGEST_LENGTH];
 
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, buf, size);
    SHA1_Final(digest, &ctx);
 
    static char mdstring[SHA_DIGEST_LENGTH*2+1];

    for (i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdstring[i*2], "%02x", (unsigned int)digest[i]);
 
    return mdstring;
}


int main(int argc, char **argv)
{
    FILE *fp;
    int i, len, num;
    char line[1024] = {0};

    char cinput[9];
    int  iinput[9];

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
                &iinput[0], &iinput[1], &iinput[2], &iinput[3], 
                &iinput[4], &iinput[5], &iinput[6], &iinput[7], 
                &iinput[8]);

        for(i = 0; i < 9; i++) {
            cinput[i] = (char)iinput[i];
        }

        for(i = 0; i < num; i++) {
            printf("%02d ", cinput[i]);
        }
        printf("-sha1: %s \n", sha1(cinput, num));


        memset(line,   0, sizeof(line));
        memset(iinput, 0, sizeof(iinput));
        memset(cinput, 0, sizeof(cinput));

        fgets(line, sizeof(line), fp);
    }

    fclose(fp);
    return 0;
}
