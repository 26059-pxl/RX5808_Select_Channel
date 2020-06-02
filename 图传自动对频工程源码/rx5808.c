#include "all.h"
/*
Project:RX5808ͼ���Զ���Ƶ
Made By:ͺͺ�ĿƼ�լ
�׷��� ��bilibili

���ǵĿں��ǣ���Դ����

Note���˴�����ȫ��Դ�����д�����ȥ���ƣ���һ�������ƹ��Ĵ��뿪Դ������

2020.05.16
*/


/*
����֡��ʽ��
			4λ		�Ĵ�����ַ
      1λ		�����д����
			20λ	����
			
20λ���ݸ�ʽ��
			7λ		A
			13λ	N
			
A��N�ļ��㹫ʽ��
			F_rf-479=F_lo=2*(N*32+A)*(F_osc/R)
			���У�F_osc=8Mhz	R=8

�ȷ���λ������������������������������������

Ӳ���Ķ�����ȥ��һ�����裬�����޷�ʹ��

����ȥ�ٶȲ鿴RX5808������ܣ��ٶ��Ŀ���ַ��
https://wenku.baidu.com/view/40e85b9e6037ee06eff9aef8941ea76e59fa4a6e.html
*/

#define Synthesizer_Register_B 				0x01  //Ƶ�����üĴ���
#define Power_Down_Control_Register   0x0a  //��Դ���ƼĴ���
#define State_Register                0x0f  //״̬���ƼĴ���

u16 code Freq_Buff[48]=
{
	5865,5845,5825,5805,5785,5765,5745,5725,		//A	CH1-8
	5733,5752,5771,5790,5809,5828,5847,5866,		//B	CH1-8
	5705,5685,5665,5645,5885,5905,5925,5945,		//C	CH1-8
	5740,5760,5780,5800,5820,5840,5860,5880,		//D	CH1-8
	5658,5695,5732,5769,5806,5843,5880,5917,		//E	CH1-8
	5362,5399,5436,5473,5510,5547,5584,5621,		//F	CH1-8
};

u8 channel=0;

//spi����һλ����
void SPI_Send_Bit(bit Value)
{
  SCK =0;
	_nop_();
	MOSI=Value;
	_nop_();
	SCK =1;
	_nop_();
}

//spi���ͳ���Ϊlenλ����
//����ʱ��ͼ��Ҫ���ȷ������ݵ�λ
void SPI_Send_Bits(u32 Value,u8 len)
{
  u8 i;
	for(i=0;i<len;i++)
	{
	  SPI_Send_Bit((bit)(Value&0x01));
		Value>>=1;
	}
}

void Send_Register_Data(u8 addr,u32 Dat)   //���ַΪaddr�Ĵ�����������
{
  LE=0;                   //�൱��CS���͵�ƽѡ��оƬ������������
	SPI_Send_Bits(addr,4);  //�ȷ��ͼĴ���4λ��ַ
	SPI_Send_Bit(1);        //����д��
	SPI_Send_Bits(Dat,20);  //����20λ��������
	
	//һ֡���ݴ������
	LE=1;
	SCK=0;
	MOSI=0;
}

void RX5808_Set_Freq(u16 F_rf)   //RX5808����һ��Ƶ��
{
  u32 dat;
	u16 F_lo=(F_rf-479)/2;
	u16 SYN_RF_N;
	u16 SYN_RF_A;
	
	SYN_RF_N=F_lo/32;    //�����Ƶ����Nֵ
	SYN_RF_A=F_lo%32;    //�����Ƶ����Aֵ
	
	dat=SYN_RF_N;
	dat<<=7;
	dat|=SYN_RF_A;       //�õ�20λ��������
	
	//����Ƶ�ʿ��ƼĴ���
	Send_Register_Data(Synthesizer_Register_B,dat);
}

void Channel_Scan()  //�Զ���Ƶ
{
	u8 i;
	u8 sig;
	u8 sig_max=0;
	
	ADC_Translate();
	
	for(i=0;i<48;i++)
	{
	  RX5808_Set_Freq(Freq_Buff[i]);
		delay_ms(15);
		sig=ADC_Translate();
//		Uart_Up_CH_Sig(i,sig);
		
		if(sig>sig_max)sig_max=sig,channel=i;
	}
	
//	Uart_Up_Buf("\r\n");
//	Uart_Up_Buf("The final channel is :  ");
//	Uart_Up_CH_Sig(channel,sig_max);
	
	EEPROM_Eares(0);
	EEPROM_Write(0,channel);      //Ƶ����ֵ����eeprom
	RX5808_Set_Freq(Freq_Buff[channel]);    //����Ƶ��
}
