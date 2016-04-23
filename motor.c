#include <iom16v.h>
#include <macros.h>
#include "delay.h"
#include "motor.h"
#include"lcd1602.h"

uint Rspeed;
uint Lspeed;

void motor(uint Lspeed,uint Rspeed)
{
		IN1_HIGH;
		IN2_LOW;
		IN3_HIGH;
		IN4_LOW;
		OCR1A=Lspeed;
		OCR1B=Rspeed;
}

void Motor_init()
{
  	DDRD|=((1<<PD4)|(1<<PD5));
  	PORTD&=~((1<<PD4)|(1<<PD5));
  	TCCR1A=0xa3;
  	TCCR1B=0x02;
  	OCR1A=0;
  	OCR1B=0;
}

