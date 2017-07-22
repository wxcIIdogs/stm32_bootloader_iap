#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "usart.h"
#include  "jampToapp.h"
int flag_send = 0;
void sendToFlash(u8 *buff,int len)
{
	writeDataToflash((char *)buff,len);	 	
//	for(int i = 0 ; i < len ; i ++)
//	{
		printf("%d ",len);
//	}
}
int main(void)
 {	 
	 u8 buff[2000];	 
	 delay_init();	    	 //延时函数初始化	  
	 LED_Init();		  	 //初始化与LED连接的硬件接口			
	 Lcd_Init();			 //LCD  初始化
	 TFT_CS(0);			 //打开LCD片选使能 
	 uart_init(9600);
	 GUI_Clear(White);		//清屏		 
	 sprintf((char *)buff,"the Voltage :%0.1fv", 1.2);
	 GUI_sprintf_hzstr16x(30,40,(u8 *)buff,Black,White);
	 int len = 0;
	 memset(buff,1,2000);
	 initFlash();
	 while(1)
   {			 				 		
		 len = getDataforFifo(buff);	
		 if(flag_send) 
		 {
				saveFlash();
				printf("end\r\n");
				flag_send = 0;
				jampToload(WRITE_ADDRESS);
		 }
		 else
		 {
				 len > 0?sendToFlash(buff,len),memset(buff,1,2000):0;
		 }	 		 		 
		 delay_ms(50);
		}
 }

