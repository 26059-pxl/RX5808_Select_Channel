#include "all.h"
/*
Project:RX5808ͼ���Զ���Ƶ
Made By:ͺͺ�ĿƼ�լ
�׷��� ��bilibili

���ǵĿں��ǣ���Դ���꣡����

Note���˴�����ȫ��Դ�����д�����ȥ���ƣ���һ�������ƹ��Ĵ��뿪Դ������

2020.05.16
*/

void main()
{
	UartInit();		//115200bps@12.000MHz
	P3M0&=0x7c;   //P3.0��P3.1��P3.7��Ϊ׼˫���
	P3M1&=0x7c;
	P3M0|=0x40;   //P3.6��Ϊ�������
	P3M1&=~0x40;
	P1M0&=0x1f;   //P1.7��P1.6��P1.5��Ϊ׼˫���
	P1M1&=0x1f;
	
	LED_A=1;
	delay_ms(100);
	//Channel_Scan();
	
	channel=EEPROM_Read(0);
	RX5808_Set_Freq(Freq_Buff[channel]);
	
  while(1)
	{
	  delay_ms(10);
		KEY_Scan();        //ɨ�谴��
	}
}
