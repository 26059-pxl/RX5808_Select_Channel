#ifndef __rx5808
#define __rx5808
/*
Project:RX5808ͼ���Զ���Ƶ
Made By:ͺͺ�ĿƼ�լ
�׷��� ��bilibili

���ǵĿں��ǣ���Դ����

Note���˴�����ȫ��Դ�����д�����ȥ���ƣ���һ�������ƹ��Ĵ��뿪Դ������

2020.05.16
*/

sbit SCK =P1^5;
sbit LE  =P1^6;
sbit MOSI=P1^7;

extern u16 code Freq_Buff[48];
extern u8 channel;
void RX5808_Set_Freq(u16 F_rf);   //RX5808����һ��Ƶ��
void Channel_Scan();              //�Զ���Ƶ

#endif