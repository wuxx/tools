/* client */  
#include <stdio.h>  
#include <sys/types.h>  
#include <netinet/in.h>  
#include <sys/socket.h>  
#include <netdb.h>  
#include <unistd.h>  
#include <string.h>  
#include <arpa/inet.h>  
#include <errno.h>  
#define PORT 8848  
#define MAXDATASIZE 100  

int main(int argc, char *argv[])  
{  
    char hostname[100];  
    gethostname(hostname,sizeof(hostname));  
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%s\n",hostname);  
    int sockfd, numbytes;  
    char buf[MAXDATASIZE];  
    struct hostent *he;  
    struct sockaddr_in serv_addr;  
    if (argc != 2)  
    {  
        fprintf(stderr, "usage: cilent hostname\n");  
        return 0;  
    }  
    if ((he = gethostbyname(argv[1])) == NULL)  
    {  
        fprintf(stderr, "gethostbyname error!\n");  
        return 0;;  
    }  
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
    {  
        fprintf(stderr, "socket error!\n");  
        return 0;  
    }  
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(PORT);  
    serv_addr.sin_addr = *((struct in_addr *)he->h_addr);  
    bzero(&(serv_addr.sin_zero), 8);  
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)  
    {  
        fprintf(stderr, "connect error!\n");  
        return 0;  
    }  
    if ((numbytes = read(sockfd, buf, MAXDATASIZE)) == -1)  
    {  
        fprintf(stderr, "read error!\n");  
        return 0;  
    }  
    buf[numbytes] = '\0';  
    printf("Received %d bytes: [%s]", numbytes, buf);

    write(sockfd, buf, numbytes + 1);

    while(1);
    close(sockfd);  
}  
