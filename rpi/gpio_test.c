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

