#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f10x.h"
#include "string.h"
#define USART_REC_LEN  			(1026*2)  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收


struct Fifo_usart
{
	volatile uint32_t count;
	volatile uint32_t index;
	volatile uint32_t head;
	volatile uint8_t buff[USART_REC_LEN];
};

extern struct Fifo_usart uartFifo;


extern int getDataforFifo(uint8_t *pdata);
void inputDataToFifo(uint8_t dat);
extern u8  USART_RX_BUF[USART_REC_LEN/2]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void sentUsart(char * data);
//void usart1_getData(void );

extern int rev_flag;
#endif


