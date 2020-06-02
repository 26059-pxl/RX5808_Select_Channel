#include "all.h"

/*************EEPROM��д*************/
//**************************************************************** 
//  �������� 
//---------------------------------------------------------------- 
void EEPROM_Eares(u16 addres) 
{      
	IAP_ADDRL=addres;     //��λ��ַ 
	IAP_ADDRH=addres>>8;  //��λ��ַ 
	IAP_CONTR=0x01;  
	IAP_CONTR=IAP_CONTR|0x82; //��ʱ�����ISP����
	IAP_CMD=0x03;         //���������� 
	IAP_TRIG=0x5a;        //���� 
	IAP_TRIG=0xa5;        //���������� 
	_nop_();_nop_();_nop_();_nop_();
	IAP_ADDRL=0xff; 
	IAP_ADDRH=0xff; 
	IAP_CONTR=0x00; 
	IAP_CMD=0x00; 
	IAP_TRIG=0x00;  
} 
//**************************************************************** 
//  ������ 
//---------------------------------------------------------------- 
u8 EEPROM_Read(u16 addres) 
{ 
	IAP_ADDRL=addres;     //��λ��ַ 
	IAP_ADDRH=addres>>8;  //��λ��ַ 
	IAP_CONTR=0x01;  
	IAP_CONTR=IAP_CONTR|0x82; //��ʱ�����ISP����
	IAP_CMD=0x01;         //д���� 
	IAP_TRIG=0x5a;        //���� 
	IAP_TRIG=0xa5;        //���������� 
	_nop_();_nop_();_nop_();_nop_(); 
	IAP_ADDRL=0xff; 
	IAP_ADDRH=0xff; 
	IAP_CONTR=0x00; 
	IAP_CMD=0x00; 
	IAP_TRIG=0x00; 

	return(IAP_DATA);         
} 
//**************************************************************** 
//  д���� 
//---------------------------------------------------------------- 
void EEPROM_Write(u16 addres,u8 write_data) 
{ 
	IAP_DATA=write_data;  //Ҫд������ݡ� 
	IAP_ADDRL=addres;     //��λ��ַ 
	IAP_ADDRH=addres>>8;  //��λ��ַ 
	IAP_CONTR=0x01;  
	IAP_CONTR=IAP_CONTR|0x82; //��ʱ�����ISP������ 
	IAP_CMD=0x02;         //д���� 
	IAP_TRIG=0x5a;        //���� 
	IAP_TRIG=0xa5;        //���������� 
	_nop_();_nop_();_nop_();_nop_();
	IAP_ADDRL=0xff; 
	IAP_ADDRH=0xff; 
	IAP_CONTR=0x00; 
	IAP_CMD=0x00; 
	IAP_TRIG=0x00;   
} 
