#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
    time_t seconds;

    seconds = time((time_t *)NULL);
    printf("%d\n", seconds);

    return 0;
}
