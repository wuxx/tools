#include<stdio.h>
#include<wiringPi.h>
 
void init();

int main()
{
        init();
        int angle=0;
        scanf("%d",&angle);
 
        int i=0;
        float x=0;
 
        int k=180;//180次循环的时间够了
        while(k--)
        {
                x=11.11*i;
                digitalWrite(25,HIGH);
                delayMicroseconds(500+x);
                digitalWrite(25,LOW);
                delayMicroseconds(19500-x);
                if(i==angle)
                    break;
 
                i++;
         }
        
        return 0;
}
 
 
void init()
{
        wiringPiSetup();
        pinMode(25, OUTPUT);
}

