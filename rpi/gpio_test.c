#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>

/* pi@raspberrypi:~$ gcc gpio_test.c -lwiringPi */
/*
    command:
    write
    $gpio mode 8 out
    $gpio write 8 0
    $gpio write 8 1

    read
    $gpio mode 8 in
    $gpio read 8

*/

#if 0
int main(void)
{
  wiringPiSetup() ;
  pinMode (8, OUTPUT) ;
  for(;;)
  {
    digitalWrite(8, HIGH) ; delay (500) ;
    digitalWrite(8,  LOW) ; delay (500) ;
  }
}
#endif

// What GPIO input are we using?
//      This is a wiringPi pin number

#define BUTTON_PIN      (8)

static volatile int globalCounter = 0 ;

void myInterrupt (void)
{
  ++globalCounter ;
}


int main (void)
{
  int myCounter = 0 ;

  if (wiringPiSetup () < 0)
  {
    fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiISR (BUTTON_PIN, INT_EDGE_FALLING, &myInterrupt) < 0)
  {
    fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
    return 1 ;
  }


  for (;;)
  {
    printf ("Waiting ... ") ; fflush (stdout) ;

    while (myCounter == globalCounter)
      delay (100) ;

    printf (" Done. counter: %5d\n", globalCounter) ;
    myCounter = globalCounter ;
  }

  return 0 ;
}
