#include "all.h"
/*
Project:RX5808ͼ���Զ���Ƶ
Made By:ͺͺ�ĿƼ�լ
�׷��� ��bilibili

���ǵĿں��ǣ���Դ����

Note���˴�����ȫ��Դ�����д�����ȥ���ƣ���һ�������ƹ��Ĵ��뿪Դ������

2020.05.16
*/

u8 ADC_Translate()
{
  P1ASF=0x10;
	ADC_CONTR=0xec;
	while(!(ADC_CONTR&0x10));    //�ȴ�ת�����
	
	return ADC_RES;
}
