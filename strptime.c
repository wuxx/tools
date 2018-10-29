#include <time.h>
#include <stdio.h>
#include <string.h>

 
int main() {
    struct tm tm; 
    char buf[255];
      
    strptime("24/Aug/2011:09:42:35", "%d/%b/%Y:%H:%M:%S" , &tm);

    printf("asctime:%s\n",asctime(&tm));
 
    memset(buf,0,sizeof(buf));
    strftime(buf, sizeof(buf), "%d %b %Y %H:%M", &tm);
    puts(buf);
    return 0;

}
