#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#define PRINT_VAR(v) printf(#v": %d\n", v)

#define DUMP printf

#define FORMAT_STR_HEX_1    "%02x "
#define FORMAT_STR_HEX_2    "%04x "
#define FORMAT_STR_HEX_4    "%08x "

typedef unsigned char u8;
typedef   signed char s8;

typedef unsigned short u16;
typedef   signed short s16;

typedef unsigned int u32;
typedef   signed int s32;

enum MODE {
    DUMP_MODE,
    EDIT_MODE,
};

enum ENDIAN {
    LE,
    BE,
};

void usage(char *program_name)
{
    printf("Usage: %s: [OPTION] [FILE] \n", program_name);
    fputs (("\
             -d | --dump                    dump mode                                       \n\
             -m | --edit                    edit mode                                       \n\
             -o offset | --offset offset    offset bytes in file                            \n\
             -h | --help                    display help info                               \n\n\
             * dump mode parameters *                                                       \n\
             -c cols | --col cols                                                           \n\
             -C | --canonical               canonical hex+ASCII display                     \n\
             -g bytes | --groupsize bytes                                                   \n\
             -e | --little-endian                                                           \n\
             -E | --big-endian                                                              \n\n\
             * edit mode parameters *                                                       \n\
             -n bytes | --len bytes         len of bytes write to the file, 1-4 bytes       \n\
             -v data  | --value data                                                        \n\
"), stdout);
    exit(0);
}

static struct option const long_options[] =
{
  {"dump",          no_argument,        NULL, 'd'},
  {"edit",          no_argument,        NULL, 'm'},
  {"offset",        required_argument,  NULL, 'o'},
  {"help",          no_argument,        NULL, 'h'},

    /* dump mode parameters */
  {"col",           required_argument,  NULL, 'c'},
  {"canonical",     no_argument,        NULL, 'C'},
  {"groupsize",     required_argument,  NULL, 'g'},
  {"little-endian", no_argument,        NULL, 'e'},
  {"big-endian",    no_argument,        NULL, 'E'},

    /* edit mode parameters */
  {"len",           required_argument,  NULL, 'n'},
  {"value",         required_argument,  NULL, 'v'},

};

/*....12.... read 2 byte return 0x3231 in old_word, so it's' little-endian style. */
u32 gen_new_word(u32 old_word, u32 endian, u32 groupsize)
{
    u32 new_word = 0;

    char *pc = (char *)(&old_word);

    switch (endian) {
        case (LE):
            new_word = old_word;
            break;
        case (BE):
            switch (groupsize) {
                case (1):
                    new_word = old_word;
                    break;
                case (2):
                    new_word = pc[0] << 8 | pc[1];
                    break;
                case (4):
                    new_word = pc[0] << 24 | pc[1] << 16 | pc[2] << 8 | pc[3];
                    break;
                default:
                    assert(0);
                    break;
            }
            break;
        default:
            assert(0);
            break;
    }

    return new_word;
}

void dump_word(u32 new_word, u32 groupsize, u32 col, u32 group_index)
{
    switch (groupsize) {
        case (1):
            DUMP(FORMAT_STR_HEX_1, (u8)(new_word));
            break;
        case (2):
            DUMP(FORMAT_STR_HEX_2, (u16)(new_word));
            break;
        case (4):
            DUMP(FORMAT_STR_HEX_4, (u32)(new_word));
            break;
        default:
            assert(0);
            break;
    }

    if ((group_index + 1) % col == 0) {
        DUMP("\n%08x: ", (group_index + 1) * groupsize);
    }
}

int get_host_endian()
{
    int x = 0x12345678;
    char *px;
    px = (char *)&x;
    if (*px == 0x78) {
        return LE;

    } else if (*px == 0x12) {
        return BE;

    } else {
        assert(0);
    }
}

u32 swap_endian(u32 old_word)
{
    char *pc = (char *)(&old_word);

    u32 new_word;
    new_word = pc[0] << 24 | pc[1] << 16 | pc[2] << 8 | pc[3];
    return new_word;

}

u8 get_byte(u32 word, u32 groupsize, u32 endian, u32 index)
{
    u8 *pc = (u8 *)(&word);

    assert(index <= (groupsize - 1));
#if 0
    printf("%s %x %x %x \n", __func__, word, index, pc[index]);
#endif
    switch (endian) {
        case (LE):
            return pc[index];
            break;
        case (BE):
            return pc[(groupsize - 1) - index];
            break;
        default:
            assert(0);
    }

}

int dump(s32 ifd, u32 col, u32 endian, u32 groupsize, u32 canonical)
{

    u32 old_word, new_word;
    u32 count;
    u32 group_index = 0;
    u8  byte;
    s32 i;

    DUMP("%08x: ", group_index);

    while (1) {
        old_word = 0;
        if ((count = read(ifd, &old_word, groupsize)) == -1) {
            perror("read");
            exit(-1);
        }

        if (count == groupsize) {
            new_word = gen_new_word(old_word, endian, groupsize);
            dump_word(new_word, groupsize, col, group_index);
            group_index ++;

        } else if (count <= groupsize) {
            if (count == 0) {
                break;
            } else {
                new_word = gen_new_word(old_word, endian, groupsize);

#if 0
                printf("count %d ; groupsize %d\n", count, groupsize);
                printf("old_word: %08x \n", old_word);
                printf("new_word: %08x \n", new_word);
#endif

                if (endian == BE) {
                    for(i = 0; i < count; i++) {
                        byte = get_byte(new_word, groupsize, endian, i);
                        DUMP("%02x", byte);
                    }

                    for(i = 0; i < (groupsize - count); i++) {
                        DUMP("  ");
                    }
                    DUMP("\n");

                } else if (endian == LE) {

                    for(i = 0; i < (groupsize - count); i++) {
                        DUMP("  ");
                    }

                    for(i = (count - 1); i >= 0; i--) {
                        byte = get_byte(new_word, groupsize, endian, i);
                        DUMP("%02x", byte);
                    }
                    DUMP("\n");
                }
            }
            
        } else {
            printf("unexpect count %d \n", count);
            exit(-1);

        }
    }
    
    return 0;
}

int edit(s32 ifd, u32 len, u32 value) 
{
    if (write(ifd, &value, len) != len) {
        perror("write");
        exit(-1);
    }

    return 0;
}

int main(int argc, char **argv)
{
    s32 c;
    s32 option_index;
    s32 ifd;

    u32 mode      = DUMP_MODE; 
    u32 endian    = BE;
    u32 groupsize = 1; 
    u32 col       = 16 / groupsize; /* always 16 bytes per line */
    u32 len       = 1; 
    u32 value     = 0x0;
    u32 canonical = 0;
    u32 offset    = 0;

    if (argc == 1) {
        usage(argv[0]);
    }
    while ((c = getopt_long (argc, argv, "c:deg:hmn:o:v:CE", 
                long_options, &option_index)) != -1) {
        switch (c) {
            case ('c'):
                col = atoi(optarg);
                break;
            case ('d'):
                mode = DUMP_MODE;
                break;
            case ('e'):
                endian = LE;
                break;
            case ('g'):
                groupsize = atoi(optarg);
                break;
            case ('h'):
                usage(argv[0]);
                break;
            case ('m'):
                mode = EDIT_MODE;
                break;
            case ('n'):
                len = strtol(optarg, NULL, 0);
                break;
            case ('o'):
                offset = strtol(optarg, NULL, 0);
                break;
            case ('v'):
                value = strtol(optarg, NULL, 0);
                break;
            case ('C'):
                canonical = 1;
                break;
            case ('E'):
                endian = BE;
                break;
            default:
                usage(argv[0]);
                break;
        }
    }

    PRINT_VAR(mode);
    PRINT_VAR(col);
    PRINT_VAR(endian);
    PRINT_VAR(groupsize);
    PRINT_VAR(canonical);
    PRINT_VAR(offset);
    PRINT_VAR(len);
    PRINT_VAR(value);

    col = 16 / groupsize; /* always 16 bytes per line */
    assert(get_host_endian() == LE);

    if (!(groupsize == 1 || groupsize == 2 || groupsize == 4)) {
        printf("groupsize choice: {1, 2, 4}\n");
        exit(-1);
    }

    if ((ifd = open(argv[argc-1], O_RDWR)) == -1) {
        perror("open");
        exit(-1);
    }   

    if (lseek(ifd, offset, SEEK_SET) == -1) {
        perror("lseek");
        exit(-1);
    }


    switch (mode) {
        case (DUMP_MODE):
            dump(ifd, col, endian, groupsize, canonical);
            break;
        case (EDIT_MODE):
            edit(ifd, len, value);
            break;
        default:
            printf("unknown mode %d \n", mode);
            exit(-1);
    }

    close(ifd);
    return 0;
}
