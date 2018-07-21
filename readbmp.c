#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <assert.h>  
#include <getopt.h>  
  
/* reference
    https://www.cnblogs.com/wainiwann/p/7086844.html
*/

/* 定义WORD为两个字节的类型 */  
typedef unsigned short WORD;  
/* 定义DWORD为四个字节的类型 */  
typedef unsigned long DWORD;  

typedef unsigned char u8;  
  
/* 位图文件头主要是对位图文件的一些描述 位图信息头主要是对位图图像方面信息的描述 */  
/*************************** 位图标准信息(54字节) ******************************************/  
/* 位图文件头 （位图头的字节数 = 位图文件字节数 - 位图图像数据字节数）*/  
typedef struct BMP_FILE_HEADER  
{  
    WORD bType;      // 文件标识符   
    DWORD bSize;     // 文件的大小   
    WORD bReserved1; // 保留值,必须设置为0    
    WORD bReserved2; // 保留值,必须设置为0   
    DWORD bOffset;   // 文件头的最后到图像数据位开始的偏移量   
}__attribute__ ((packed)) BMPFILEHEADER ;     // 14 字节  
  
/* 位图信息头 */  
typedef struct BMP_INFO  
{  
    DWORD bInfoSize;            // 信息头的大小     
    DWORD bWidth;               // 图像的宽度       
    DWORD bHeight;              // 图像的高度       
    WORD bPlanes;               // 图像的位面数     
    WORD bBitCount;             // 每个像素的位数   
    DWORD bCompression;         // 压缩类型   
    DWORD bmpImageSize;         // 图像的大小,以字节为单位   
    DWORD bXPelsPerMeter;       // 水平分辨率   
    DWORD bYPelsPerMeter;       // 垂直分辨率   
    DWORD bClrUsed;             // 使用的色彩数   
    DWORD bClrImportant;        // 重要的颜色数   
}__attribute__ ((packed))  BMPINF;            // 40 字节  
  
/* 彩色表:调色板 */  
typedef struct RGB_QUAD   
{  
    WORD rgbBlue;     // 蓝色强度   
    WORD rgbGreen;    // 绿色强度   
    WORD rgbRed;      // 红色强度   
    WORD rgbReversed; // 保留值   
} RGBQUAD;  
  
static struct option const long_options[] =
{
  {"ifile",          required_argument,  NULL, 'i'},
  {"debug",          no_argument,        NULL, 'd'},
  {"help",           no_argument,        NULL, 'h'},
};

int debug = 0;

#define DEBUG(fmt, ...)     do { if (debug) { printf(fmt, ##__VA_ARGS__); } } while (0)

int bwidth, bheight;
int byte_per_line;

#define get_bit(x, bit_index) ((x >> bit_index) & 0x1)
void set_bit(u8 *x, u8 bit_index, u8 b)
{
    u8 _x;
    u8 bit_mask;
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

u8 convert(u8 c)
{
    int i;
    u8 c0 = 0, c1 = 0;

	for(i = 0; i < 8; i++) {
        set_bit(&c0, i, get_bit(c, 7 - i));
    }

    c1 = ~c0;

    return c1;
}

int main(int argc, char **argv)
{  
    int i, x;
    FILE *fp;                     // 定义一个文件指针  
    BMPFILEHEADER bmpFileHeader;  // 定义一个 BMP 文件头的结构体  
    BMPINF bmpInfo;               // 定义一个 BMP 文件信息结构体   

    u8 *bmp;
  
    int c, option_index;
    char *ifile = NULL;
    char out_name[256] = {0};
    char *pc;
    int offset;

    while ((c = getopt_long (argc, argv, "i:dh",
                    long_options, &option_index)) != -1) {
        switch (c) {
            case ('d'):
                debug = 1;
                break;
            case ('i'):
                ifile = optarg;
                break;
            case ('h'):
                break;
            default:
                break;
        }
    }

    DEBUG("bmpFileHeader size: %d\n", sizeof(BMPFILEHEADER));
    DEBUG("bmpInfo       size: %d\n", sizeof(BMPINF));

    // "rb" 只读打开一个二进制文件，只允许读数据。'b'指的是让这个库函数以二进制形式打开此文件。  
    // 读取失败会返回空指针，读取成功后，fp 会指向一块具有 bmp 属性的内存,我们可以对这块内存开始操作  
    if((fp = fopen(ifile, "rb")) == NULL) // fp = 0x00426aa0  
    {  
        printf("Cann't open the file!\n");  
        return -1;
    }
  
    // 让 fp 指向 bmp 文件的开始   
    // 第 2 个参数是偏移量 第三个参数是文件起始地址 所以此函数执行成功后文件指针会指向文件的开始  
    fseek(fp, 0, SEEK_SET);                            // fp = 0x00426aa0  
  
    // 读取文件信息  
    /* 
        参数1: 读出数据的存放缓冲区 
        参数2: 读取多少个字节的数据 
        参数3: 读取几包这样的数据 
        参数4: 文件指针（源数据） 
    */  
    DEBUG("%s-%d\n", __func__, __LINE__);
    fread(&bmpFileHeader, sizeof(BMPFILEHEADER), 1, fp);   
      
    DEBUG("%s-%d\n", __func__, __LINE__);
    fread(&bmpInfo, sizeof(bmpInfo), 1, fp);  

#if 0  
    printf("%s-%d\n", __func__, __LINE__);
    // 输出BMP文件的位图文件头的所有信息  
    printf("位图文件头主要是对位图文件的一些描述:BMPFileHeader\n\n");  
    printf("文件标识符 = 0X%X\n", bmpFileHeader.bType);  
    printf("BMP 文件大小 = %d 字节\n", bmpFileHeader.bSize);  
    printf("保留值1 = %d \n", bmpFileHeader.bReserved1);  
    printf("保留值2 = %d \n", bmpFileHeader.bReserved2);  
    printf("文件头的最后到图像数据位开始的偏移量 = %d 字节\n", bmpFileHeader.bOffset);  
  
    // 输出BMP文件的位图信息头的所有信息  
    printf("\n\n位图信息头主要是对位图图像方面信息的描述:BMPInfo\n\n");  
    printf("信息头的大小 = %d 字节\n", bmpInfo.bInfoSize);  
    printf("位图的高度 = %d \n", bmpInfo.bHeight);  
    printf("位图的宽度 = %d \n", bmpInfo.bWidth);  
    printf("图像的位面数(位面数是调色板的数量,默认为1个调色板) = %d \n", bmpInfo.bPlanes);   
    printf("每个像素的位数 = %d 位\n", bmpInfo.bBitCount);  
    printf("压缩类型 = %d \n", bmpInfo.bCompression);  
    printf("图像的大小 = %d 字节\n", bmpInfo.bmpImageSize);  
    printf("水平分辨率 = %d \n", bmpInfo.bXPelsPerMeter);  
    printf("垂直分辨率 = %d \n", bmpInfo.bYPelsPerMeter);  
    printf("使用的色彩数 = %d \n", bmpInfo.bClrUsed);  
    printf("重要的色彩数 = %d \n", bmpInfo.bClrImportant);  
  
    printf("\n\n\n压缩说明：有0（不压缩），1（RLE 8，8位RLE压缩），2（RLE 4，4位RLE压缩，3（Bitfields，位域存放）");  
#endif

    DEBUG("%s-%d\n", __func__, __LINE__);
    // 输出BMP文件的位图文件头的所有信息  
    DEBUG("BMPFileHeader\n\n");  
    DEBUG("bmpFileHeader.bType = 0X%X\n", bmpFileHeader.bType);  
    DEBUG("bmpFileHeader.bSize = %d Bytes\n", bmpFileHeader.bSize);  
    DEBUG("bmpFileHeader.bReserved1 = %d \n", bmpFileHeader.bReserved1);  
    DEBUG("bmpFileHeader.bReserved2 = %d \n", bmpFileHeader.bReserved2);  
    DEBUG("bmpFileHeader.bOffset = %d Bytes\n", bmpFileHeader.bOffset);  
  
    // 输出BMP文件的位图信息头的所有信息  
    DEBUG("\n\nBMPInfo\n\n");  
    DEBUG("bmpInfo.bInfoSize = %d Bytes\n", bmpInfo.bInfoSize);  
    DEBUG("bmpInfo.bHeight   = %d \n", bmpInfo.bHeight);  
    DEBUG("bmpInfo.bWidth    = %d \n", bmpInfo.bWidth);  
    DEBUG("bmpInfo.bPlanes   = %d \n", bmpInfo.bPlanes);   
    DEBUG("bmpInfo.bBitCount = %d bit\n", bmpInfo.bBitCount);  
    DEBUG("bmpInfo.bCompression = %d \n", bmpInfo.bCompression);  
    DEBUG("bmpInfo.bmpImageSize = %d Bytes\n", bmpInfo.bmpImageSize);  
    DEBUG("bmpInfo.bXPelsPerMeter = %d \n", bmpInfo.bXPelsPerMeter);  
    DEBUG("bmpInfo.bYPelsPerMeter = %d \n", bmpInfo.bYPelsPerMeter);  
    DEBUG("bmpInfo.bClrUsed = %d \n", bmpInfo.bClrUsed);  
    DEBUG("bmpInfo.bClrImportant = %d \n", bmpInfo.bClrImportant);  
  
    //printf("\n\n\n压缩说明：有0（不压缩），1（RLE 8，8位RLE压缩），2（RLE 4，4位RLE压缩，3（Bitfields，位域存放）");  
  
    
    bmp = (u8 *)malloc(bmpInfo.bmpImageSize);

    {
        u8 palette[8];
        fread(palette, sizeof(palette), 1, fp);

        for(i = 0; i < sizeof(palette); i++) {
            DEBUG("palette[%d]: [0x%02x]\n", i, palette[i]);
        }
    }

    fread(bmp, bmpInfo.bmpImageSize, 1, fp);  

    fread(bmp, bmpInfo.bmpImageSize, 1, fp);  

    bwidth  = bmpInfo.bWidth;
    bheight = bmpInfo.bHeight;

    if ((bwidth % 8) == 0) {
        byte_per_line = bwidth / 8;
    } else {
        byte_per_line = (bwidth / 8) + 1;
    }

    assert(bmpInfo.bBitCount == 1);
    assert(bmpInfo.bmpImageSize == (byte_per_line * bheight));


    /* 1. up-left to up-right */
    /* 2. up to down */

#if 0
    for(i = 0; i < bmpInfo.bmpImageSize; i++) {
        if ((i != 0) && (i % 16 == 0)) {
            printf("\n");
        }

        printf("0x%02x ", bmp[i]);
    }
    printf("\n");
#endif

    memcpy(out_name, ifile, strlen(ifile));
    pc = strchr(ifile, '.');
    offset = (int)(pc - ifile);
    memcpy(&out_name[offset], "_Icon", 6);

    DEBUG("out_name: %s\n", out_name);

    printf("// %d x %d\n", bwidth, bheight);

    printf("const unsigned char %s[] = {\n", out_name);

    for(i = bheight - 1; i >= 0; i--) {
        for(x = 0; x < byte_per_line; x++) {
            if ((i == (bheight - 1)) && (x == 0)) {
                printf("0x%02x", convert(bmp[byte_per_line * i + x]));
            } else {
                printf(", 0x%02x", convert(bmp[byte_per_line * i + x]));
            }
        }
    }

    printf("};\n");

    fclose(fp);  
  
    return 0;  
  
}
