
#ifndef __TFT_H
#define __TFT_H
#include "stm32f10x.h"


void TFT_CS(u8 d);

void Lcd_Init(void);

void GUI_Clear(u16 color);

void Lcd_Write_Data(u16 data);								 //д16λ����

void Address_set(u8 x1,u16 y1,u8 x2,u16 y2,u8 xq,u16 yq);    //������ʾ��Χ
void GUI_sprintf_hzstr16x(u8 x1,u16 y1,u8 *str,u16 dcolor,u16 bgcolor);
//��ɫ����
/*���峣����ɫ��*/
#define Red      0xf800	//��
#define Yellow   0xffe0	//��
#define Green    0x07e0	//��
#define Cyan     0x07ff	//��
#define Blue     0x001f	//��
#define Purple   0xf81f	//��
#define Black    0x0000	//��
#define White    0xffff	//��
#define Gray     0x7bef	//��
#define Blue1    0xa5ff //����
#define Blue2	 0x7cdf
#define Purple1  0x8a9e //����
#define Green1   0x0410 //ī��
#define Green2   0x2616
#define Blue3	 0x751E
#define Purple2  0xcd9e //����
#define Red2	 0XF260	//����
#define Red3	 0X8000	//�غ�
#define window   0XDED7


//��Ļ�ߴ�
#define TFT_XMAX       239
#define TFT_YMAX       319



#endif






