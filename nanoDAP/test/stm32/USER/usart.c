/******************** 鑫盛电子工作室 ********************
 * 文件名  ：usart1.c
 * 描述    ：将printf函数重定向到USART1。这样就可以用printf函数将单片机的数据
 *           打印到PC上的超级终端或串口调试助手。         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * 库版本  ：ST3.0.0  *
 * 淘宝店：http://shop66177872.taobao.com
**********************************************************************************/
#include "usart.h"
#include <stdarg.h>

#include <string.h>
#include "misc.h"

#include "shell.h"
// stm32f103c8t6 USART1
#if 0
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
//
#define  DEBUG_USART_TX_GPIO_PORT         GPIOA
#define  DEBUG_USART_TX_GPIO_PIN          GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  DEBUG_USART_IRQ                USART1_IRQn
#define  DEBUG_USART_IRQHandler         USART1_IRQHandler
#endif

// stm32f103c8t6 USART2
#define  DEBUG_USARTx                   USART2
#define  DEBUG_USART_CLK                RCC_APB1Periph_USART2
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
//
#define  DEBUG_USART_TX_GPIO_PORT         GPIOA
#define  DEBUG_USART_TX_GPIO_PIN          GPIO_Pin_2
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_3

#define  DEBUG_USART_IRQ                USART2_IRQn
#define  DEBUG_USART_IRQHandler         USART2_IRQHandler

uint32_t uart_recv_buf_index = 0;
char uart_recv_buf[UART_IO_SIZE] = {0};

static void NVIC_Configuration(void)
{

  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;

  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	NVIC_Configuration();
	
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	
	USART_Cmd(DEBUG_USARTx, ENABLE);		

}

/*****************  ?????? **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	if (ch == '\n') {
		USART_SendData(pUSARTx, '\r');			
		while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	}
	
	USART_SendData(pUSARTx,ch);
		
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  ????? **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	temp_h = (ch&0XFF00)>>8;
	temp_l = ch&0XFF;
	
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

void uart_putc(uint8_t byte)
{
	Usart_SendByte(DEBUG_USARTx, byte);
}

void uart_puts(char *s)
{
	Usart_SendString(DEBUG_USARTx, s);
}

void DEBUG_USART_IRQHandler(void)
{
	static uint8_t i;
	uint16_t ch;

	ch = (uint8_t)USART_ReceiveData(DEBUG_USARTx);

		if (ch == '\n') {   /* sscom will send '\r\n' we ignore the '\n' */
				return;
		}
		if (uart_recv_buf_index == (UART_IO_SIZE - 1) && ch != '\r') {
				uart_puts("cmd too long!\n");
				uart_recv_buf_index = 0;
				return;
		}

		if (ch == '\r') {
				uart_recv_buf[uart_recv_buf_index] = '\0';  /* terminate the string. */
				shell(uart_recv_buf);

				uart_recv_buf_index = 0;
				return;
		} else {
				uart_recv_buf[uart_recv_buf_index] = ch;
				uart_recv_buf_index++;
		}
		
		/* echo */
		printf("%c", ch);

}

void uart_init()
{
	USART_Config();
}
 


 /* 描述  ：重定向c库函数printf到USART1*/ 
int fputc(int ch, FILE *f)
{
/* 将Printf内容发往串口 */
	if (ch == '\n') {
		USART_SendData(DEBUG_USARTx, '\r');
		while (!(DEBUG_USARTx->SR & USART_FLAG_TXE));		
	}
	
  USART_SendData(DEBUG_USARTx, (unsigned char) ch);
  while (!(DEBUG_USARTx->SR & USART_FLAG_TXE));
 
  return (ch);
}



