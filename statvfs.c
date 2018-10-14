#define _FILE_OFFSET_BITS 64

#include <stdio.h>
#include <sys/statvfs.h>


typedef enum {
    TOTAL_SIZE,
    FREE_SIZE,
    USED_SIZE,
    AVAIL_SIZE 
}VFsize;


char * byte_size_to_string(fsblkcnt_t size)
{
#if 0
    const double k = 1024;
    const double m = k*1024;
    const double g = m*k;

    static char size_str[128] = {0};

    if(size>=g)
        sprintf(size_str,"%0.2lf GB",size/g);
    else if(size>=m)
        sprintf(size_str,"%0.2lf MB",size/m);
    else if(size>=k)
        sprintf(size_str,"%0.2lf KB",size/k);
    else
        sprintf(size_str,"%0.0lf Byte",size>=0?size:0.0);
#endif
    static char size_str[128] = {0};
    sprintf(size_str,"%d MB",(int)(size/(1024 * 1024)));

    return size_str;
}

fsblkcnt_t get_vfs_size(struct statvfs *buf,VFsize flag)
{
    fsblkcnt_t block;
    fsblkcnt_t bsize;

    bsize = buf->f_bsize;

    switch (flag){
    case TOTAL_SIZE:
        block = buf->f_blocks;
    break;
    case FREE_SIZE:
        block = buf->f_bfree;
    break;
    case USED_SIZE:
        block = buf->f_blocks - buf->f_bavail;
    break;
    case AVAIL_SIZE:
        block = buf->f_bavail;
    break;
    default:
        block = 0;
    break;
    }

    return  bsize * block;
}

int main(int argc, char **argv)
{
    char *pathname;
    struct statvfs buf;
    fsblkcnt_t total_size;
    fsblkcnt_t used_size;
    fsblkcnt_t avail_size;
    int error;

    pathname = "/";
    if(argc>1){
        pathname = argv[1];
    }

    error = statvfs(pathname,&buf);

    if(error <0){
        fprintf(stderr,"statvfs():%m\n");
        return error;
    }

    printf("FileSystem of \'%s\':\n",pathname);

    total_size = get_vfs_size(&buf,TOTAL_SIZE);
    printf("       total:%s\n",byte_size_to_string(total_size));

    used_size = get_vfs_size(&buf,USED_SIZE);
    printf("       used :%s\n",byte_size_to_string(used_size));

    avail_size = get_vfs_size(&buf,AVAIL_SIZE);
    printf("       Avail:%s\n",byte_size_to_string(avail_size));

    return 0;
}
