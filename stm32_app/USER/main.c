

/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny
STM32F103RBT6 开发板 库函数部分	  */

/*小图片 刷屏幕
  程序中 用到的TFT 为 我们店的 TFT  驱动芯片为 ili9325	
  TFT用到的GPIO  PB为数据口	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES 采用系统复位
  此函数 用寄存器方式配置GPIO  在TFT的数据 命令脚配置上用的是寄存器  这样能大幅度提高输出速度
*/

#include  "delay.h"
#include  "led.h"
#include  "tft.h"
#include  "usart.h"
void main(void)
{
 SCB->VTOR = FLASH_BASE | 0x10000;
 u8 buff[100];
 delay_init();	    	 //延时函数初始化	  
 LED_Init();		  	 //初始化与LED连接的硬件接口			
 Lcd_Init();			 //LCD  初始化
 TFT_CS(0);			 //打开LCD片选使能 
 uart_init(115200);
 GUI_Clear(White);		//清屏	 
	while(1)
   {			 		 		
		 sprintf((char *)buff,"the Voltage");
		 GUI_sprintf_hzstr16x(30,40,(u8 *)buff,Red,White);
		 delay_ms(5000);
			//GUI_Clear(White);			//清屏
   }
}

