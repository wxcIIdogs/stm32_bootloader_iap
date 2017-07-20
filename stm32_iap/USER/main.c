#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "usart.h"
#include  "jampToapp.h"
int main(void)
 {	 
	 u8 buff[2000];	 
	 delay_init();	    	 //��ʱ������ʼ��	  
	 LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�			
	 Lcd_Init();			 //LCD  ��ʼ��
	 TFT_CS(0);			 //��LCDƬѡʹ�� 
	 uart_init(115200);
	 GUI_Clear(White);		//����
	
	 //initFlash();
	 //writeDataToflash((char *)buff,sizeof(buff));
	 //saveFlash();
	 sprintf((char *)buff,"the Voltage :%0.1fv", 1.2);
	 GUI_sprintf_hzstr16x(30,40,(u8 *)buff,Black,White);
	 int len = 0;
	 while(1)
   {			 				 
		 //printf("hello wxc \r\n");		 
		 len = getDataforFifo(buff);	
			//printf("hello wxc %d\r\n",len);		 		 
		 len>0?printf("%s",buff),memset(buff,0,sizeof(buff)):0;
		 delay_ms(100);
		 //printf("%d\r\n",strlen(uartFifo.buff));
		 //GUI_Clear(White);			//����
		}
 }

