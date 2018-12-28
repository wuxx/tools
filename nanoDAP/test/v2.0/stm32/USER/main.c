/******************** 鑫盛电子工作室 ********************
 * 文件名  ：main.c
 * 描述    ：串口1(USART1)向电脑的超级终端以1s为间隔打印当前ADC1的转换电压值         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.0.0
 * 淘宝店：http://shop66177872.taobao.com
**********************************************************************************/

#include "stm32f10x.h"
#include "usart.h"
#include "adc.h"       

extern __IO u16 ADC_ConvertedValue[8];	 
// 软件延时
void Delay(unsigned long time)
{unsigned long i,j;
  
	for(j=0; j<time; j++)
	{
	   for(i=0;i<12000;i++);
	}
}

u32 adc_channel_map[3][18] = 
{
          /*   0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16    17  */
/* ADC1 */	{0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xB0, 0xB1, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xFF, 0xFF},
/* ADC2 */	{0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xB0, 0xB1, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xFF, 0xFF},
/* ADC3 */	{0xA0, 0xA1, 0xA2, 0xA3, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFF, 0xC0, 0xC1, 0xC2, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF}
};

extern int32_t shell(char *cmd);

int adc_show()
{
	u32 i;
  u32 ADC1_value[8];

	for (i = 0; i < 8; i++) {
		 ADC1_value[i] = 3300000/4096*ADC_ConvertedValue[i]/1000;		 
	 }
		
	for (i = 0; i < 8; i++) {
		printf("P%X = %d mV\r\n", adc_channel_map[0][i], ADC1_value[i]);
	}
	
	return 0;
}

void delay_ms(uint32_t count)
{
	uint32_t i, x;
	for(; count != 0; count--) {
		for(i = 1000; i != 0; i--) {
			for(x = 72; x != 0; x--) {
			}
		}
	}
}

int gpio_init()
{		
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	gpio.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;	
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;   
	gpio.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &gpio);
	return 0;
}

char sys_banner[] = {"ATE system buildtime [" __TIME__ " " __DATE__ "] "};

int main(void)
{ 
	u32 i;
	
  u32 ADC1_value[8];
	
  /* 配置系统时钟为72M */      
  SystemInit();	

  USART_Config();
	
	gpio_init();
	
  /* 初始化ADC1 */
  //ADC1_Init();
	
	//shell("help\r\n");
	printf("%s\n", sys_banner);
	
	
	while (1) {
		GPIO_SetBits(GPIOB, GPIO_Pin_12 /* | GPIO_Pin_13 */);
		delay_ms(50);
		GPIO_ResetBits(GPIOB, GPIO_Pin_12 /* | GPIO_Pin_13 */);
		delay_ms(50);
	}
	
#if 0
  while (1)
  {
     Delay(500);

		for (i = 0; i < 8; i++) {
			 ADC1_value[i] = 3300000/4096*ADC_ConvertedValue[i]/1000;		 
		 }

		 for (i = 0; i < 8; i++) {
			printf("P%X ADC value = %d mV  \r\n", adc_channel_map[0][i], ADC1_value[i]);
		 }
	   
		 printf("\r\n");
  }
#endif

	while(1);
	
}



