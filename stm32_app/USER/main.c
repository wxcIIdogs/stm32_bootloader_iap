

/* http://zq281598585.taobao.com/  
�������	  ELH    enlighten  sunny
STM32F103RBT6 ������ �⺯������	  */

/*СͼƬ ˢ��Ļ
  ������ �õ���TFT Ϊ ���ǵ�� TFT  ����оƬΪ ili9325	
  TFT�õ���GPIO  PBΪ���ݿ�	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES ����ϵͳ��λ
  �˺��� �üĴ�����ʽ����GPIO  ��TFT������ ������������õ��ǼĴ���  �����ܴ�����������ٶ�
*/

#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "usart.h"
void main(void)
{
 SCB->VTOR = FLASH_BASE | 0x10000;
 u8 buff[100];
 delay_init();	    	 //��ʱ������ʼ��	  
 LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�			
 Lcd_Init();			 //LCD  ��ʼ��
 TFT_CS(0);			 //��LCDƬѡʹ�� 
 uart_init(115200);
 GUI_Clear(White);		//����	 
	while(1)
   {			 		 		
		 sprintf((char *)buff,"the Voltage");
		 GUI_sprintf_hzstr16x(30,40,(u8 *)buff,Red,White);
		 delay_ms(5000);
			//GUI_Clear(White);			//����
   }
}

