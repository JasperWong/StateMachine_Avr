#include<iom16v.h>
#include"music.h"
#include<macros.h>


/*void bell(uchar select)

 	while(1)
	{
		Music(song);
	}
 
}*/

void Bell_Init()
{
	 DDRD|=(1<<PD7);     //����PORTAΪ���
	 PORTD&=~(1<<PD7);     
 	 TCCR1B = 0x01;     //Timer1��ʼ����������Ƶ����Ƶϵ��Ϊ1
 	// SEI();             //��ȫ���ж�	
}