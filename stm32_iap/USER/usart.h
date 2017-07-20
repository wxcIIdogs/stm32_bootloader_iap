#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f10x.h"
#include "string.h"
#define USART_REC_LEN  			(1026*2)  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����


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
extern u8  USART_RX_BUF[USART_REC_LEN/2]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void sentUsart(char * data);
//void usart1_getData(void );

extern int rev_flag;
#endif


