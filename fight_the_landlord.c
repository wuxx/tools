#include <stdio.h>
#include <string.h>
#include <assert.h>


struct card_info
{
    char *desc;
    int count;
};

#define CI_SIZE (15)
struct card_info ci[CI_SIZE] = {
    {"BK",   1},
    {"LK",   1},
    {" 2",   4},
    {" A",   4},
    {" K",   4},
    {" Q",   4},
    {" J",   4},
    {"10",   4},
    {" 9",   4},
    {" 8",   4},
    {" 7",   4},
    {" 6",   4},
    {" 5",   4},
    {" 4",   4},
    {" 3",   4},
};

/* for back up */
static struct card_info _ci[CI_SIZE];

void card_info_save()
{
    memcpy(_ci, ci, sizeof(ci));
}

void card_info_restore()
{
    memcpy(ci, _ci, sizeof(ci));
}

void dump_card_info()
{
    int i;
    for(i = 0; i < (sizeof(ci) / sizeof(ci[0])); i++) {
        printf("[%s] ", ci[i].desc);
    }
    printf("\n");
    for(i = 0; i < (sizeof(ci) / sizeof(ci[0])); i++) {
        printf("  %d  ", ci[i].count);
    }
    printf("\n");

}

int reduce_card_count(char *card)
{
    int i;
    for(i = 0; i < (sizeof(ci) / sizeof(ci[0])); i++) {
        if(strcmp(ci[i].desc, card) == 0) {
            if (ci[i].count == 0) {
                break;
            }

            ci[i].count--;
            return 0;
        }
    }

    printf("illegal [%s]\n", card);
    return -1;
}


int update_card_info(char *input)
{
    char c;
    char card[3] = {'\0', '\0', '\0'};
    int i = 0;
    int len;
    len = strlen(input);

    while(input[i] != '\0') {

        if (input[i] == '\n') {
            return 0;
        }

        if (input[i] == 'B' || input[i] == 'L' ||input[i] == '1') {
            card[0] = input[i];
            i++;
            if (input[i] == 'K') {
                card[1] = input[i];
                reduce_card_count(card);
            } else if (input[i] == '0') {
                card[1] = input[i];
                reduce_card_count(card);
    
            } else {
                printf("illegal input [%s]\n", input);
                return -1;
            }
        } else {
            card[0] = ' ';
            card[1] = input[i];
            if (reduce_card_count(card) != 0) {
                return -1;
            }
        }
        i++;
    }

    return 0;
}

int main()
{
    char input[512];
    dump_card_info();
    while(1) {
        fgets(input, sizeof(input), stdin);
        printf("get [%s]\n", input);

        card_info_save();
        if (update_card_info(input) != 0) {
            card_info_restore();
        }

        dump_card_info();
    }
    return 0;
}
