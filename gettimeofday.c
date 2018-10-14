#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int main()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    printf("time: %ld:%ld\n", tv.tv_sec, tv.tv_usec);

    return 0;
}
