#include<iom16v.h>
#include"ad_key.h"
#include<macros.h>


void ADC_Init(void)
{
 	ADCSR = 0x00;   //ADC关闭
 	ADMUX = 0x67;  	//外部参考源AVCC,左对齐,选择ADC7通道
 	ACSR =  0x80;   //模拟比较器控制和状态寄存器ACSR的ACD置1,使模拟比较器禁用
 	ADCSR = 0x83;   //开启ADC，8分频
}

void T2_Init()						//T2 ctc 中断
{
	TCCR2=0x0A;
	TIMSK|=(1<<OCIE2);
	OCR2=125;			//1ms
	
}	