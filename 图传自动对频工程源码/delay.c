#include "all.h"
/*
Project:RX5808ͼ���Զ���Ƶ
Made By:ͺͺ�ĿƼ�լ
�׷��� ��bilibili

���ǵĿں��ǣ���Դ���꣡����

Note���˴�����ȫ��Դ�����д�����ȥ���ƣ���һ�������ƹ��Ĵ��뿪Դ������

2020.05.16
*/
void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}

void delay_ms(u16 time)
{
  while(time--)Delay1ms();
}