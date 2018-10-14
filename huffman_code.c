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
#include <endian.h>


#define CH_MAX (256)

struct c_struct {
    char c;
    int weight;
    unsigned int code;
    int len;
    struct c_struct *parent;
    struct c_struct *lchild, *rchild;
};

struct c_struct *huffman_root;

struct c_struct b_st[CH_MAX];   /* root & body */
struct c_struct c_st[CH_MAX];   /* leaf */
struct c_struct * c_sort[CH_MAX];
int bindex = 0;
int cindex = 0;

struct c_struct * get_free_node()
{
    assert(bindex < CH_MAX);
    bindex++;
    return &b_st[bindex-1];
}

#define get_bit(x, bit_index) ((x >> bit_index) & 0x1)

void set_bit(unsigned int *x, unsigned int bit_index, unsigned int b) 
{
    unsigned int _x; 
    unsigned int bit_mask;
    _x = *x; 
    if (get_bit(_x, bit_index) != b) {
        if (b == 0) {
            bit_mask = ~(0x1 << bit_index);
            *x = (_x) & bit_mask;
        } else {    /* b == 1 */
            bit_mask = (0x1 << bit_index);
            *x = (_x) | bit_mask;
        }   
    }   
}

void dumpw(int *buf, int size)
{
    int i, j;

    j = 0;
    printf("\n0x%02x\t", 0);
    for(i = 0; i < size; i++) {
        printf("0x%08x ", buf[i]);
        j++;
        if (j % 4 == 0) {
            printf("\n0x%02x\t", j);
        }
    }

    printf("\n");
}

void sort(struct c_struct * *cs, int size)
{
    int i, j;

    struct c_struct *tmp;

    int max_index;

    for(i = 0; i < size; i++) {
        max_index = i;

        for(j = i + 1; j < size; j++) {
            if (cs[j]->weight > cs[max_index]->weight) {
                max_index = j;
            }
        }

        tmp   = cs[i];
        cs[i] = cs[max_index];
        cs[max_index] = tmp;
    }

}

void gen_huffman_tree()
{
    int i;
    int size = CH_MAX;
    struct c_struct *node;
    struct c_struct *n1, *n2;

    for (i = (size - 1); i >= 0; i--) {
        if (c_sort[i]->weight != 0) {
            break;
        }
    }
    size = i + 1;
    cindex = size;

    while (1) {

        if (size == 1) {
            break;
        }

        n1 = c_sort[size - 1];
        n2 = c_sort[size - 2];
        node = get_free_node();
        node->weight = n1->weight + n2->weight;
        node->lchild = n1;
        node->rchild = n2;
        n1->parent = node;
        n2->parent = node;
        c_sort[size - 2] = node;
        size--;
        sort(c_sort, size);
    }
}

void update_c_code()
{
    int i;
    unsigned int index  = 0;
    unsigned int code   = 0;
    struct c_struct *node;

    for(i = 0; i < cindex; i++) {
        node   = &c_st[i];
        code   = 0;
        index  = 0;
        while (node->parent != NULL) {
            if (node->parent->lchild == node) {
                set_bit(&code, index, 0);
            } else if (node->parent->rchild == node) {
                set_bit(&code, index, 1);
            } else {
                assert(0);
            }
            index++;
            node = node->parent;
        }
        c_st[i].code = code;
        c_st[i].len  = index;
    }
}

int main(int argc, char **argv)
{

    int i, j;
    int ifd;
    unsigned char *mbuf;
    struct stat st; 

    /* init */
    for(i = 0; i < CH_MAX; i++) {
        b_st[i].c    = 0;
        b_st[i].weight = 0;
        b_st[i].code = 0;
        b_st[i].len  = 0;
        b_st[i].parent = NULL;
        b_st[i].lchild = NULL;
        b_st[i].rchild = NULL;

        c_st[i].c    = i;
        c_st[i].weight = 0;
        c_st[i].code = 0;
        c_st[i].len  = 0;
        c_st[i].parent = NULL;
        c_st[i].lchild = NULL;
        c_st[i].rchild = NULL;

        c_sort[i] = &c_st[i];
    }

    printf("enter!\n");
    if (argc != 2) {
        printf("usage: %s file\n", argv[0]);
        exit(-1);
    }

    if ((ifd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(-1);
    }

    if ((fstat(ifd, &st)) == -1) {
        perror("fstat");
        exit(-1);
    }

    if ((mbuf = mmap(0, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, ifd, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }

    /* statistic */
    for(i = 0; i < st.st_size; i++) {
        c_st[mbuf[i]].weight++;
    }

    for(i = 0; i < CH_MAX; i++) {
        printf("[0x%02x]: %d \n", i, c_st[i].weight);
    }

    /* sort */
    sort(c_sort, CH_MAX);

    for(i = 0; i < CH_MAX; i++) {
        printf("[0x%02x]: %d \n", i, c_sort[i]->weight);
    }

    gen_huffman_tree();

    printf("bindex: %d; cindex: %d\n", bindex, cindex);

/*
    dot -Tsvg -Kdot -Gcharset=utf-8 ./huffman_tree.dot -o huffman_tree.svg
     digraph G { 
        edge [fontname="FangSong"];
        node [shape=circle, fontname="FangSong" size="20,20"];
        size="10,8"; ratio = fill;
     }
*/

    for(i = 0; i < bindex; i++) {
        if (b_st[i].lchild != 0) {
            printf("\"[%x]\" -> \"[%x]\"\n", &b_st[i], b_st[i].lchild);
        }

        if (b_st[i].rchild != 0) {
            printf("\"[%x]\" -> \"[%x]\"\n", &b_st[i], b_st[i].rchild);
        }
    }

    for(i = 0; i < cindex; i++) {
        if (c_st[i].lchild != 0) {
            printf("\"[%x]\" -> \"[%x]\"\n", &c_st[i], c_st[i].lchild);
        }

        if (c_st[i].rchild != 0) {
            printf("\"[%x]\" -> \"[%x]\"\n", &c_st[i], c_st[i].rchild);
        }

    }

    update_c_code();

    for(i = 0; i < cindex; i++) {
        printf("[%d]:len: %02d; code:", i, c_st[i].len);

        for (j = c_st[i].len - 1; j >= 0; j--) {
            printf("%d", get_bit(c_st[i].code, j)); 
        }
        printf("\n");

    }

    munmap(mbuf, st.st_size);

    printf("exit!\n");
    return 0;

}
