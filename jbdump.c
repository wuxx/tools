/* java byte code dump */
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

struct jvm_bytecode {
    int dec;
    int hex;
    char *desc;
};

struct jvm_bytecode jvm_b[] = {
    {  0, 0x00, "nop"},
    {  1, 0x01, "aconst_null"},
    {  2, 0x02, "sconst_m1"},
    {  3, 0x03, "sconst_0"},
    {  4, 0x04, "sconst_1"},
    {  5, 0x05, "sconst_2"},
    {  6, 0x06, "sconst_3"},
    {  7, 0x07, "sconst_4"},
    {  8, 0x08, "sconst_5"},
    {  9, 0x09, "iconst_m1"},
    { 10, 0x0A, "iconst_0"},
    { 11, 0x0B, "iconst_1"},
    { 12, 0x0C, "iconst_2"},
    { 13, 0x0D, "iconst_3"},
    { 14, 0x0E, "iconst_4"},
    { 15, 0x0F, "iconst_5"},
    { 16, 0x10, "bspush"},
    { 17, 0x11, "sspush"},
    { 18, 0x12, "bipush"},
    { 19, 0x13, "sipush"},
    { 20, 0x14, "iipush"},
    { 21, 0x15, "aload"},
    { 22, 0x16, "sload"},
    { 23, 0x17, "iload"},
    { 24, 0x18, "aload_0"},
    { 25, 0x19, "aload_1"},
    { 26, 0x1A, "aload_2"},
    { 27, 0x1B, "aload_3"},
    { 28, 0x1C, "sload_0"},
    { 29, 0x1D, "sload_1"},
    { 30, 0x1E, "sload_2"},
    { 31, 0x1F, "sload_3"},
    { 32, 0x20, "iload_0"},
    { 33, 0x21, "iload_1"},
    { 34, 0x22, "iload_2"},
    { 35, 0x23, "iload_3"},
    { 36, 0x24, "aaload"},
    { 37, 0x25, "baload"},
    { 38, 0x26, "saload"},
    { 39, 0x27, "iaload"},
    { 40, 0x28, "astore"},
    { 41, 0x29, "sstore"},
    { 42, 0x2A, "istore"},
    { 43, 0x2B, "astore_0"},
    { 44, 0x2C, "astore_1"},
    { 45, 0x2D, "astore_2"},
    { 46, 0x2E, "astore_3"},
    { 47, 0x2F, "sstore_0"},
    { 48, 0x30, "sstore_1"},
    { 49, 0x31, "sstore_2"},
    { 50, 0x32, "sstore_3"},
    { 51, 0x33, "istore_0"},
    { 52, 0x34, "istore_1"},
    { 53, 0x35, "istore_2"},
    { 54, 0x36, "istore_3"},
    { 55, 0x37, "aastore"},
    { 56, 0x38, "bastore"},
    { 57, 0x39, "sastore"},
    { 58, 0x3A, "iastore"},
    { 59, 0x3B, "pop"},
    { 60, 0x3C, "pop2"},
    { 61, 0x3D, "dup"},
    { 62, 0x3E, "dup2"},
    { 63, 0x3F, "dup_x"},
    { 64, 0x40, "swap_x"},
    { 65, 0x41, "sadd"},
    { 66, 0x42, "iadd"},
    { 67, 0x43, "ssub"},
    { 68, 0x44, "isub"},
    { 69, 0x45, "smul"},
    { 70, 0x46, "imul"},
    { 71, 0x47, "sdiv"},
    { 72, 0x48, "idiv"},
    { 73, 0x49, "srem"},
    { 74, 0x4A, "irem"},
    { 75, 0x4B, "sneg"},
    { 76, 0x4C, "ineg"},
    { 77, 0x4D, "sshl"},
    { 78, 0x4E, "ishl"},
    { 79, 0x4F, "sshr"},
    { 80, 0x50, "ishr"},
    { 81, 0x51, "sushr"},
    { 82, 0x52, "iushr"},
    { 83, 0x53, "sand"},
    { 84, 0x54, "iand"},
    { 85, 0x55, "sor"},
    { 86, 0x56, "ior"},
    { 87, 0x57, "sxor"},
    { 88, 0x58, "ixor"},
    { 89, 0x59, "sinc"},
    { 90, 0x5A, "iinc"},
    { 91, 0x5B, "s2b"},
    { 92, 0x5C, "s2i"},
    { 93, 0x5D, "i2b"},
    { 94, 0x5E, "i2s"},
    { 95, 0x5F, "icmp"},
    { 96, 0x60, "ifeq"},
    { 97, 0x61, "ifne"},
    { 98, 0x62, "iflt"},
    { 99, 0x63, "ifge"},
    {100, 0x64, "ifgt"},
    {101, 0x65, "ifle"},
    {102, 0x66, "ifnull"},
    {103, 0x67, "ifnonnull"},
    {104, 0x68, "if_acmpeq"},
    {105, 0x69, "if_acmpne"},
    {106, 0x6A, "if_scmpeq"},
    {107, 0x6B, "if_scmpne"},
    {108, 0x6C, "if_scmplt"},
    {109, 0x6D, "if_scmpge"},
    {110, 0x6E, "if_scmpgt"},
    {111, 0x6F, "if_scmple"},
    {112, 0x70, "goto"},
    {113, 0x71, "jsr"},
    {114, 0x72, "ret"},
    {115, 0x73, "stableswitch"},
    {116, 0x74, "itableswitch"},
    {117, 0x75, "slookupswitch"},
    {118, 0x76, "ilookupswitch"},
    {119, 0x77, "areturn"},
    {120, 0x78, "sreturn"},
    {121, 0x79, "ireturn"},
    {122, 0x7A, "return"},
    {123, 0x7B, "getstatic_a"},
    {124, 0x7C, "getstatic_b"},
    {125, 0x7D, "getstatic_s"},
    {126, 0x7E, "getstatic_i"},
    {127, 0x7F, "putstatic_a"},
    {128, 0x80, "putstatic_b"},
    {129, 0x81, "putstatic_s"},
    {130, 0x82, "putstatic_i"},
    {131, 0x83, "getfield_a"},
    {132, 0x84, "getfield_b"},
    {133, 0x85, "getfield_s"},
    {134, 0x86, "getfield_i"},
    {135, 0x87, "putfield_a"},
    {136, 0x88, "putfield_b"},
    {137, 0x89, "putfield_s"},
    {138, 0x8A, "putfield_i"},
    {139, 0x8B, "invokevirtual"},
    {140, 0x8C, "invokespecial"},
    {141, 0x8D, "invokestatic"},
    {142, 0x8E, "invokeinterface"},
    {143, 0x8F, "new"},
    {144, 0x90, "newarray"},
    {145, 0x91, "anewarray"},
    {146, 0x92, "arraylength"},
    {147, 0x93, "athrow"},
    {148, 0x94, "checkcast"},
    {149, 0x95, "instanceof"},
    {150, 0x96, "sinc_w"},
    {151, 0x97, "iinc_w"},
    {152, 0x98, "ifeq_w"},
    {153, 0x99, "ifne_w"},
    {154, 0x9A, "iflt_w"},
    {155, 0x9B, "ifge_w"},
    {156, 0x9C, "ifgt_w"},
    {157, 0x9D, "ifle_w"},
    {158, 0x9E, "ifnull_w"},
    {159, 0x9F, "ifnonnull_w"},
    {160, 0xA0, "if_acmpeq_w"},
    {161, 0xA1, "if_acmpne_w"},
    {162, 0xA2, "if_scmpeq_w"},
    {163, 0xA3, "if_scmpne_w"},
    {164, 0xA4, "if_scmplt_w"},
    {165, 0xA5, "if_scmpge_w"},
    {166, 0xA6, "if_scmpgt_w"},
    {167, 0xA7, "if_scmple_w"},
    {168, 0xA8, "goto_w"},
    {169, 0xA9, "getfield_a_w"},
    {170, 0xAA, "getfield_b_w"},
    {171, 0xAB, "getfield_s_w"},
    {172, 0xAC, "getfield_i_w"},
    {173, 0xAD, "getfield_a_this"},
    {174, 0xAE, "getfield_b_this"},
    {175, 0xAF, "getfield_s_this"},
    {176, 0xB0, "getfield_i_this"},
    {177, 0xB1, "putfield_a_w"},
    {178, 0xB2, "putfield_b_w"},
    {179, 0xB3, "putfield_s_w"},
    {180, 0xB4, "putfield_i_w"},
    {181, 0xB5, "putfield_a_this"},
    {182, 0xB6, "putfield_b_this"},
    {183, 0xB7, "putfield_s_this"},
    {184, 0xB8, "putfield_i_this"},
    {254, 0xFE, "impdep1"},
    {255, 0xFF, "impdep2"},
};


#define DUMP_VAR1(c, var) printf(#var "\t0x%02x\n", c->var)
#define DUMP_VAR2(c, var) printf(#var "\t0x%04x\n", be16toh(c->var))

typedef unsigned char       u1;
typedef unsigned short      u2;
typedef unsigned int        u4;

void dumpb(char *desc, unsigned char *buf, int size)
{
    int i, j;
    int len = strlen(desc);
    printf("%s\t", desc);

    j = 0;
    for(i = 0; i < size; i++) {
        printf("0x%02x ", buf[i]);
        j++;
        if (j == 16) {
            printf("\n");
            for(j = 0; j < len; j++) {
                printf(" ");
            }
            printf("\t"); /* for align */
            j = 0;
        }
    }

    printf("\n");
}

int main(int argc, char **argv)
{

    int ifd;
    char *mbuf;
    struct stat st;

    if (argc != 2) {
        printf("usage: %s jbfile\n", argv[0]);
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

    return 0;

}
