#include<iom16v.h>
#include"ad_key.h"
#include<macros.h>


void ADC_Init(void)
{
 	ADCSR = 0x00;   //ADC�ر�
 	ADMUX = 0x67;  	//�ⲿ�ο�ԴAVCC,�����,ѡ��ADC7ͨ��
 	ACSR =  0x80;   //ģ��Ƚ������ƺ�״̬�Ĵ���ACSR��ACD��1,ʹģ��Ƚ�������
 	ADCSR = 0x83;   //����ADC��8��Ƶ
}

void T2_Init()						//T2 ctc �ж�
{
	TCCR2=0x0A;
	TIMSK|=(1<<OCIE2);
	OCR2=125;			//1ms
	
}	