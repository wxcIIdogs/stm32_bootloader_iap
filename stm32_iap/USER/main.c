#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "usart.h"
#include  "jampToapp.h"
int main(void)
 {	 
	 u8 buff[100];	 
	 delay_init();	    	 //延时函数初始化	  
	 LED_Init();		  	 //初始化与LED连接的硬件接口			
	 Lcd_Init();			 //LCD  初始化
	 TFT_CS(0);			 //打开LCD片选使能 
	 uart_init(115200);
	 GUI_Clear(White);		//清屏
	 memcpy(buff,"323231232222222222222222222222222222222222",sizeof(buff));
	 writeDataToflash((char *)buff);
	 while(1)
   {			 				 
		 printf("hello wxc \r\n");		 
		 sprintf((char *)buff,"the Voltage :%0.1fv", 1.2);
		 GUI_sprintf_hzstr16x(30,40,(u8 *)buff,Black,White);
		 delay_ms(5000);
		 //GUI_Clear(White);			//清屏
		}
 }

