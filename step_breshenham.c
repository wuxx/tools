#include <stdio.h>

/*
https://blog.csdn.net/renjiankun/article/details/80555251
 */

#define max(x, y) ((x) > (y) ? (x) : (y))

int step_even_count; // 步数计数
int step_x,step_y,step_z; //各轴输出的步数 ΔY
int count_x,count_y,count_z;//各轴的Pi
int step_completed;//步数计数器
 
int x = 0, y = 0, z = 0;

void setup() {
	step_x = 160;
	step_y = 80;
	step_z = 40;
	step_even_count = max(step_x, step_y);
	step_even_count = max(step_z, step_even_count);//取各轴最大值作为X（ΔX）
	count_x = -(step_even_count>>1);//-ΔX/2  ΔX➗2，后边所有数据都是除2处理 
	count_y = count_x;
	count_z = count_x;

#if 0
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(8,OUTPUT);
	pinMode(9,OUTPUT);
	digitalWrite(2,1);
	digitalWrite(8,1);
	Serial.begin(9600);
#endif
}
 
 
 
void loop() {
  // put your main code here, to run repeatedly:
  // ΔX都是一致的
  // < 0 Pi + ΔY
  // > 0 Pi + ΔY - ΔX
  //并且应该注意到 P1 = ΔY - ΔX/2
  while(step_completed < step_even_count) {
      count_x += step_x;  //计算小于0 的情况 = Pi + ΔY
      if(count_x > 0)		//Pi >0
      {
          //digitalWrite(3,1);		  //输出一个脉冲
          count_x -= step_even_count; //由于Pi + ΔY已经计算，此处直接减去ΔX即可
          //digitalWrite(3,0);
          x++;
      }

      count_y += step_y;
      if(count_y > 0)
      {
          //digitalWrite(9,1);
          count_y -= step_even_count;
          //digitalWrite(9,0);
          y++;
      }

      count_z += step_z;
      if(count_z > 0)
      {
          //digitalWrite(10,1);
          count_z -= step_even_count;
          //digitalWrite(10,0);
          z++;
      }

      step_completed += 1;

      printf("[%d, %d, %d]\n", x, y, z);
      //delayMicroseconds(300);//脉冲间隔
  }

   while(1);
}

int main()
{
    setup();
    loop();
}
