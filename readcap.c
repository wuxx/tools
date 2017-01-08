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

#define offsetof(member,type) ((unsigned long) ( &( ((type *)0)->member)))

#define DUMP_VAR1(c, var) printf(#var "\t0x%02x\n", (c)->var)
#define DUMP_VAR2(c, var) printf(#var "\t0x%04x\n", be16toh((c)->var))
#define DUMP_VAR4(c, var) printf(#var "\t0x%08x\n", be32toh((c)->var))

typedef void (*dump_component_func)(unsigned char *buf, int size);

typedef unsigned char       u1;
typedef unsigned short      u2;
typedef unsigned int        u4;

#define COMPONENT_Min                   (0)

#define COMPONENT_Header                (1)
#define COMPONENT_Directory             (2)
#define COMPONENT_Applet                (3)
#define COMPONENT_Import                (4)
#define COMPONENT_ConstantPool          (5)
#define COMPONENT_Class                 (6)
#define COMPONENT_Method                (7)
#define COMPONENT_StaticField           (8)
#define COMPONENT_ReferenceLocation     (9)
#define COMPONENT_Export                (10)
#define COMPONENT_Descriptor            (11)
#define COMPONENT_Debug                 (12)

#define COMPONENT_Max                   (13)

char *COMPONENT_Desc[] = {
    "COMPONENT_Invalid",
    "COMPONENT_Header",
    "COMPONENT_Directory",
    "COMPONENT_Applet",
    "COMPONENT_Import",
    "COMPONENT_ConstantPool",
    "COMPONENT_Class",
    "COMPONENT_Method",
    "COMPONENT_StaticField",
    "COMPONENT_ReferenceLocation",
    "COMPONENT_Export",
    "COMPONENT_Descriptor",
    "COMPONENT_Debug",
};

#pragma pack(1)
struct component {
    u1 tag;
    u2 size;
    u1 info[0];
};

/* header */
typedef struct package_info_t {
    u1 minor_version;
    u1 major_version;
    u1 AID_length;
    u1 AID[0/*AID_length*/];
}package_info;

typedef struct package_name_info_t {
    u1 name_length;
    u1 name[0/*name_length*/];
}package_name_info;

struct header_component {
    u1 tag;
    u2 size;
    u4 magic;
    u1 minor_version;
    u1 major_version;
    u1 flags;
    package_info package;
    package_name_info package_name;
};

/* directory */
typedef struct static_field_size_info_t {
    u2 image_size;
    u2 array_init_count;
    u2 array_init_size;
}static_field_size_info;

typedef struct custom_component_info_t {
    u1 component_tag;
    u2 size;
    u1 AID_length;
    u1 AID[0/*AID_length*/];
}custom_component_info;

struct directory_component {
    u1 tag;
    u2 size;
    u2 component_sizes[12];
    static_field_size_info static_field_size;
    u1 import_count;
    u1 applet_count;
    u1 custom_count;
    custom_component_info custom_components[0/*custom_count*/];
};

/* applet */

typedef struct applet_info_t { 
    u1 AID_length;
    u1 AID[0/*AID_length*/];
    u2 install_method_offset;
} applet_info;

struct applet_component {
    u1 tag;
    u2 size;
    u1 count;
    applet_info applet[0/*count*/];
};

/* import */
struct import_component {
    u1 tag;
    u2 size;
    u1 count;
    package_info packages[0/*count*/];
};

/* constant_pool */
typedef struct cp_info_t {
    u1 tag;
    u1 info[3];
}cp_info;

struct constant_pool_component {
    u1 tag;
    u2 size;
    u2 count;
    cp_info constant_pool[0/*count*/];
};

/* class */
#if 0
struct class_component {
    u1 tag;
    u2 size;
    u2 signature_pool_length;
    type_descriptor signature_pool[];
    interface_info interfaces[];
    class_info classes[];
};
#endif
#pragma pack()
/* dump byte */
void dumpb(unsigned char *buf, int size, char *desc)
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

void dumpc(char *desc, unsigned char *buf, int size)
{
    int i;

    printf("%s\t", desc);

    printf("[");

    for (i = 0; i < size; i++) {
        printf("%c", buf[i]);
    }

    printf("]\n");

}

/* dump short */
void dumps(unsigned short *buf, int size, char *desc)
{
    int i, j;
    int len = strlen(desc);
    printf("%s\t", desc);

    j = 0;
    for(i = 0; i < size; i++) {
        printf("0x%04x ", be16toh(buf[i]));
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

void dump_component_header(unsigned char *buf, int size)
{
    int offset;
    package_name_info *ppackage_name;

    struct header_component *phcmpot = (struct header_component*)buf;

    DUMP_VAR4(phcmpot, magic);
    DUMP_VAR1(phcmpot, minor_version);
    DUMP_VAR1(phcmpot, major_version);
    DUMP_VAR1(phcmpot, flags);

    printf("package.");
    DUMP_VAR1(&(phcmpot->package), minor_version);
    printf("package.");
    DUMP_VAR1(&(phcmpot->package), major_version);
    printf("package.");
    DUMP_VAR1(&(phcmpot->package), AID_length);

    dumpb((&(phcmpot->package))->AID, (&(phcmpot->package))->AID_length, "package.AID[]");

    offset  = offsetof(package, struct header_component);
    offset += offsetof(AID, package_info);
    offset += (&(phcmpot->package))->AID_length;

    ppackage_name = (package_name_info *)&buf[offset];
    printf("package_name.");
    DUMP_VAR1(ppackage_name, name_length);
    dumpb(ppackage_name->name, ppackage_name->name_length, "package_name.name[]");
    dumpc("package_name.name[]", ppackage_name->name, ppackage_name->name_length);

    return;
}

void dump_component_directory(unsigned char *buf, int size)
{
    int i;
    int offset = 0;

    custom_component_info *pcustom_components;

    struct directory_component *phcmpot = (struct directory_component*)buf;

    dumps(phcmpot->component_sizes, sizeof(phcmpot->component_sizes) / sizeof(phcmpot->component_sizes[0]), "component_sizes[12]");
    printf("static_field_size.");
    DUMP_VAR2(&(phcmpot->static_field_size), image_size);
    printf("static_field_size.");
    DUMP_VAR2(&(phcmpot->static_field_size), array_init_count);
    printf("static_field_size.");
    DUMP_VAR2(&(phcmpot->static_field_size), array_init_size);

    DUMP_VAR1(phcmpot, import_count);
    DUMP_VAR1(phcmpot, applet_count);
    DUMP_VAR1(phcmpot, custom_count);

    offset = offsetof(custom_components, struct directory_component);

    for(i = 0; i < phcmpot->custom_count; i++) { /* TODO: need test */

        pcustom_components = (custom_component_info *)&buf[offset];

        printf("custom_components[%d].component_tag", i);
        DUMP_VAR1(pcustom_components, component_tag);
        printf("custom_components[%d].size", i);
        DUMP_VAR1(pcustom_components, size);
        printf("custom_components[%d].AID_length", i);
        DUMP_VAR1(pcustom_components, AID_length);
        dumpb(pcustom_components->AID, pcustom_components->AID_length, "custom_components[x].AID");
        offset += offsetof(AID, custom_component_info);
        offset += pcustom_components->AID_length;

    }

    return;
}

void dump_component_applet(unsigned char *buf, int size)
{
    int i, offset;

    struct applet_component *papplet_component;
    applet_info *papplet_info;

    papplet_component = (struct applet_component *)buf;
    DUMP_VAR1(papplet_component, count);

    offset = offsetof(applet, struct applet_component);

    papplet_info = (applet_info *)&buf[offset];

    for(i = 0; i < papplet_component->count; i++) {
        printf("applet_info[%d].", i);
        DUMP_VAR1(papplet_info, AID_length);
        dumpb(papplet_info->AID, papplet_info->AID_length, "applet_info[x].AID");

        printf("applet_info[%d].install_method_offset\t", i);
        printf("0x%02x\n", * ((u2 *)(&(papplet_info->AID[papplet_info->AID_length]))));

    }

    return;
}
void dump_component_import(unsigned char *buf, int size)
{
    int i, offset;

    struct import_component *pimport_component;
    package_info *ppackage_info;

    pimport_component = (struct import_component *)buf;
    DUMP_VAR1(pimport_component, count);

    offset = offsetof(packages, struct import_component);

    for(i = 0; i < pimport_component->count; i++) {
        ppackage_info = (package_info *)&buf[offset];
        printf("package_info[%d].", i);
        DUMP_VAR1(ppackage_info, minor_version);
        printf("package_info[%d].", i);
        DUMP_VAR1(ppackage_info, major_version);
        printf("package_info[%d].", i);
        DUMP_VAR1(ppackage_info, AID_length);

        dumpb(ppackage_info->AID, ppackage_info->AID_length, "package_info[x].AID");

        offset += offsetof(AID, package_info);
        offset += ppackage_info->AID_length;
    }

    return;
}

void dump_component_constantpool(unsigned char *buf, int size)
{
    int i;
    struct constant_pool_component *pconstant_pool_component;
    cp_info *pcp_info;

    pconstant_pool_component = (struct constant_pool_component *)buf;

    DUMP_VAR2(pconstant_pool_component, count);

    for(i = 0; i < be16toh(pconstant_pool_component->count); i++) {
        pcp_info = &(pconstant_pool_component->constant_pool[i]);

        printf("constant_pool[%d].", i);
        DUMP_VAR1(pcp_info, tag);

        dumpb(pcp_info->info, sizeof(pcp_info->info), "constant_pool[x].info");
    }

    return;
}

void dump_component_class(unsigned char *buf, int size)
{
    return;
}

void dump_component_method(unsigned char *buf, int size)
{
    return;
}

void dump_component_staticfield(unsigned char *buf, int size)
{
    return;
}

void dump_component_referencelocation(unsigned char *buf, int size)
{
    return;
}

void dump_component_export(unsigned char *buf, int size)
{
    return;
}

void dump_component_descriptor(unsigned char *buf, int size)
{
    return;
}

void dump_component_debug(unsigned char *buf, int size)
{
    return;
}

dump_component_func dump_component[COMPONENT_Max] = {
    NULL,
    dump_component_header,
    dump_component_directory,
    dump_component_applet,
    dump_component_import,
    dump_component_constantpool,
    dump_component_class,
    dump_component_method,
    dump_component_staticfield,
    dump_component_referencelocation,
    dump_component_export,
    dump_component_descriptor,
    dump_component_debug,
};

int main(int argc, char **argv)
{

    int ifd;
    unsigned char *mbuf;
    struct stat st; 

    struct component *pcmpot;

    printf("enter!\n");
    if (argc != 2) {
        printf("usage: %s capfile\n", argv[0]);
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
    
    pcmpot = (struct component *)mbuf;
    if (pcmpot->tag >= COMPONENT_Max || pcmpot->tag <= COMPONENT_Min) {
        printf("invalid tag [%d] \n", pcmpot->tag);
        exit(-1);
    }

    printf("%s\n", COMPONENT_Desc[pcmpot->tag]);
    DUMP_VAR1(pcmpot, tag);
    DUMP_VAR2(pcmpot, size);
    dumpb(pcmpot->info, be16toh(pcmpot->size), "info");

    dump_component[pcmpot->tag](mbuf, be16toh(pcmpot->size));

    munmap(mbuf, st.st_size);

    printf("exit!\n");
    return 0;

}
1234
1234
1234
1234
1234
  
