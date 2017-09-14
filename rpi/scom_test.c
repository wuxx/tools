#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#define BAUDRATE B115200 ///Baud rate : 115200
#define DEVICE "/dev/ttyAMA0"
#define SIZE 1024

int bindex = 0;
char buffer_cache[4096] = {0};

int sfd = 0;

struct termios st_new;
struct termios st_old;

//open port & set port
int serialinit()
{
    sfd = open(DEVICE, O_RDWR|O_NOCTTY|O_NDELAY);
    if(-1 == sfd)
    {
        perror("open serial port fail!\n");
        return -1;
    }
    if( (fcntl(sfd, F_SETFL, 0)) < 0 )
    {
        perror("fcntl F_SETFL fail!\n");
        return -1;
    }
    if(tcgetattr(sfd, &st_old) != 0)
    {
        perror("tcgetattr fail!\n");
        return -1;
    }

    st_new = st_old;
    cfmakeraw(&st_new);//将终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理

    //set speed
    cfsetispeed(&st_new, BAUDRATE);//115200
    cfsetospeed(&st_new, BAUDRATE);

    //set databits
    st_new.c_cflag |= (CLOCAL|CREAD);
    st_new.c_cflag &= ~CSIZE;
    st_new.c_cflag |= CS8;

    //set parity
    st_new.c_cflag &= ~PARENB;
    st_new.c_iflag &= ~INPCK;

    //set stopbits
    st_new.c_cflag &= ~CSTOPB;
    st_new.c_cc[VTIME]=0;    //指定所要读取字符的最小数量
    st_new.c_cc[VMIN]=1;     //指定读取第一个字符的等待时间，时间的单位为n*100ms
                            //如果设置VTIME=0，则无字符输入时read（）操作无限期的阻塞
    tcflush(sfd,TCIFLUSH);  //清空终端未完成的输入/输出请求及数据。
    if( tcsetattr(sfd,TCSANOW,&st_new) != 0 )
    {
        perror("tcsetattr fail!\n");
        return -1;
    }

    return sfd;
}

int main(int argc, char **argv)
{
    int nret = 0;
    char buf[SIZE];

    if( serialinit() == -1 )
    {
        perror("serialinit fail!\n");
        return -1;
    }

    bzero(buf, SIZE);

    /* nret = write(sfd, "hello, world!\r\n", 16); */
#if 1   /* read */
    while(1)
    {
        nret = read(sfd, buf, SIZE);
        if(-1 == nret)
        {
            perror("read data error!\n");
            break;
        }
        if(0 < nret)
        {
            buf[nret] = 0;
            printf("recv data: [%s]\n", buf);
        }
    }
#endif


    //nret = write(sfd, "hello, world!\r\n", 14);

    close(sfd);
    return 0;

}
