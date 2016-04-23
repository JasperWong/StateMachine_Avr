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
	 DDRD|=(1<<PD7);     //设置PORTA为输出
	 PORTD&=~(1<<PD7);     
 	 TCCR1B = 0x01;     //Timer1开始工作，不分频，分频系数为1
 	// SEI();             //打开全局中断	
}