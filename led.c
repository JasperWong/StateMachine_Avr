#include<iom16v.h>
#include"595.h"
#include"16SPI.h"
#include"delay.h"

uchar right=0x01;														
uchar left=0x80;

/*void led1(uchar left,uchar right)
{	
	Driver_595(left,right);
	right<<=1;
	left>>=1;
	delay_ms(500);	
}*/


/*void led2(uchar left,uchar right)
{
	left=0x01;														
	right=0x80;
	for(i=0;i<8;i++)
	{	
		delay_ms(500);
		Driver_595(left,right);
		left<<=1;
		right>>=1;
	}

}*/