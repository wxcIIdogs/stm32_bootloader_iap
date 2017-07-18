

/**********************************************************************************
 * ����1 ����
 * ����1 PA9 PA10���� �� �ж���Ӧ����
 * ��汾  ��ST_v3.5
**********************************************************************************/

#include "usart.h"


//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(unsigned char)ch);   
	return ch;
}
#endif 
void sentUsart(char * data)
{
	int len = strlen(data);
	int i =0;
	for(i = 0; i< len; i++)
		{
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
	  	  USART_SendData(USART1,(unsigned char)data[i]); 						
		}  
}
/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/



#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  

//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound){
    //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;				   //IO�����ýṹ��
	USART_InitTypeDef USART_InitStructure;				   //�������ýṹ��
	NVIC_InitTypeDef NVIC_InitStructure;				   //�ж����ýṹ��
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
 	USART_DeInit(USART1);          //��λ����1  �ڿ�������ǰ ��ö�Ҫ��λһ������
	 //USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������	 PA.9ѡ����״̬���ܽ��봮��ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
 
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10


   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;                //���������� һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;     //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;        //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	   //�շ�ģʽ   ����������ý��� �����

  USART_Init(USART1, &USART_InitStructure); //��ʼ������

#if EN_USART1_RX		  //���ʹ���˽���  
   //Usart1 NVIC ����
 NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
   
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�	 ���յ����ݽ����ж�

#endif

    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 

}


//���� ������һ��16λ����USART_RX_STA ����ʾ �ɼ������ݳ���  ����״̬�� �൱��һ���Ĵ���
//USART_RX_STA     15		    14	         13-0
//				 �������	���յ�0x0d	  ���յ����ݳ���  û���ռ�1 ��ʾ����һ���ֽ�
//USART_RX_STA=0 ��Ϊ����������׼��

//���ڽ����жϵ�ǰ���� ���ݵ�����Իس�Ϊ׼  ��  0x0d 0x0a  
int rev_flag = 0;
void USART1_IRQHandler(void)                	//����1�ж���Ӧ����		 �����ֲ�����㶨��
{	
	u8 Res;													//�����ڽ��յ�����  RXNE������1 
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������		
		if((USART_RX_STA&0x8000)==0)//����δ���
			{
			if(USART_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)
					USART_RX_STA=0;//���մ���,���¿�ʼ
				else 
					{
						USART_RX_STA |= 0x8000;	//��������� 			  //���յ��س��ĺ��ֽ�  ��λ״̬�Ĵ��� 
						printf("%s",USART_RX_BUF);
						rev_flag = 1;
						USART_RX_STA = 0;
					}
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)
					USART_RX_STA|=0x4000;					 //���յ��س���ǰһ�ֽ�  ��λ״̬�Ĵ���
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;			//�����յ����� ����������
					USART_RX_STA++;									//����+1 Ϊ��һ����׼��
					if(USART_RX_STA>(USART_REC_LEN-1))
						USART_RX_STA=0;//����������,���¿�ʼ����	  
					}		 
				}
			}

     } 
} 
#endif	















































