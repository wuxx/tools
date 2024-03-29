#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>

#define DEBUG_VAR(v) printf(#v": %d\n", v)

typedef unsigned char u8;
typedef   signed char s8;

typedef unsigned short u16;
typedef   signed short s16;

typedef unsigned int u32;
typedef   signed int s32;

void usage(char *program_name)
{
    printf("Usage: %s: [OPTION] [FILE] \n", program_name);
    fputs (("\
             -i | --ifile                   input file                                      \n\
             -m | --mfile                   search mode config file                         \n\
             -g | --groupsize               groupsize = [1|2|4]                             \n\
             -h | --help                    display help info                               \n\
"), stdout);
    exit(0);
}

static struct option const long_options[] =
{
  {"ifile",     required_argument,  NULL, 'i'},
  {"mfile",     required_argument,  NULL, 'm'},
  {"g",         required_argument,  NULL, 'g'},
  {"help",      no_argument,        NULL, 'h'},

};

int count_one_bit(unsigned int x)  
{  
    int count = 0;  

    while (x)  
    {  
        ++count;  
        x &= (x - 1);  
    }  
    return count;  
}

int match(int *buf1, int *buf2, int word_nr)
{
    int i;

    int count = 0;
    for(i = 0; i < word_nr; i++) {
        count += count_one_bit(~(buf1[i] ^ buf2[i]));
    }

    return count;
}

int main(int argc, char **argv)
{
    char *ifile, *mfile;
    int i, j;
    int c;
    int fd;
    FILE *fp;
    char line[1024] = {0};
    int word[128] = {0};
    int windex = 0;
    int mcount = 0;
    int mmax = 0;
    int max_offset[128] = {0};
    int mindex = 0;
    int group_size = 4;
    int *mbuf = NULL;
    struct stat st; 

    if (argc != 3) {
        printf("usage: %s file hex-num-file\n", argv[0]);
        exit(-1);
    }

    while ((c = getopt_long (argc, argv, "i:m:g:h",
                long_options, &option_index)) != -1) {
        switch (c) {
            case ('i'):
                ifile = optarg;
                break;
            case ('m'):
                mfile = optarg;
                break;
            case ('g'):
                groupsize = atoi(optarg);
                break;
            case ('h'):
                usage(argv[0]);
                break;
            default:
                usage(argv[0]);
                break;
        }
    }

    if (groupsize != 1 || groupsize != 2 || groupsize != 2) {
        printf("groupsize must be one of [1|2|4]\n");
        exit(-1);
    }

    if ((fd = open(ifile, O_RDWR)) == -1) {
        perror("open");
        exit(-1);
    }

    if ((fp = fopen(mfile, "r")) == NULL) {
        perror("fopen");
        exit(-1);
    }

    fgets(line, sizeof(line), fp);
    while(!feof(fp)) {
        
        /* printf("get [%s]\n", line); */

        sscanf(line, "%x", &word[windex++]);

        assert(windex <= (sizeof(word) / sizeof(word[0])));

        memset(line, 0, sizeof(line));
        fgets(line, sizeof(line), fp);
    }

    /*
    for(i = 0; i < (sizeof(word) / sizeof(word[0])); i++) {
        printf("[%d]: 0x%08x\n", i, word[i]);
    }
    */

    if ((fstat(fd, &st)) == -1) {
        perror("fstat");
        exit(-1);
    }   

    assert(st.st_size % 4 == 0);

    if ((mbuf = mmap(0, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }

    assert(windex <= (st.st_size / 4));

    /* match start, let's kick it */
    for(i = 0; i <= ((st.st_size / 4) - windex); i++) {
        mcount = match(word, &mbuf[i], windex);

        if (mcount == mmax) {
            max_offset[mindex++] = i * 4;
	    assert(mindex < (sizeof(max_offset) / sizeof(max_offset[0])));
        }

        if (mcount > mmax) {
            mmax = mcount;

            mindex = 0;
            max_offset[mindex++] = i * 4;
        }
    }

    printf("\t");
    for(i = 0; i < windex; i++) {
        printf("[%d]: 0x%08x\n", i, word[windex]);
    }

    printf("offset: 0x%08x; max: 0x%08x; match_max: %d\n", max_offset, windex * 32,  mmax);

    for(i = 0; i < mindex; i++) {

        printf("%d: 0x%08x\n\t", i, max_offset[i]);

        for(j = 0; j < windex; j++) {
            printf("0x%08x ", mbuf[(max_offset[i] / 4) + j]);
        }

        printf("\n");
    }

    munmap(mbuf, st.st_size);
    fclose(fp);
    close(fd);
    return 0;
}
