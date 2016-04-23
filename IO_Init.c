#include<iom16v.h>


void IO_Init()
{
	
	DDRC=0xff;			//lcd
	PORTC=0xff;
	
	DDRD=0x00;			
	PORTD=0xff;
	
	DDRB|=0xff;			//595ºÍmotor
	PORTB&=~0x0f;
	
	DDRD|=(1<<PD2);		//lcd
	PORTD&=~(1<<PD2);
	DDRD|=(1<<PD3);		//lcd
	PORTD&=~(1<<PD3);
	
	DDRD|=(1<<PD4);		//motor
	PORTD&=~(1<<PD4);
	DDRD|=(1<<PD5);
	PORTD&=~(1<<PD5);
	
	DDRD|=(1<<PD6);		//lcd
	PORTD&=~(1<<PD6);
	
	DDRD|=(1<<PD7);		//buzz
	PORTD&=~(1<<PD7);
}