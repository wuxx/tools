#include<stdio.h>
#include<string.h>
#include<time.h>

#include <sys/stat.h>
#include <sys/types.h>

int main( void )
{
	struct tm *newtime;
	char tmpbuf[128];
	time_t lt1;

	char date[128];

	time( &lt1 );
	newtime=localtime(&lt1);

	strftime( tmpbuf, 128, "Today is %A, day %d of %B in the year %Y./ %Fn", newtime);

    
	strftime(date, 128, "%F", newtime);

	//printf(tmpbuf);

	printf(date);

    if(mkdir(date, 0755) != 0) {
        perror("mkdir");
    }

	return 0;

}
