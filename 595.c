#include "16SPI.h"
#include "595.h"

void Driver_595(uchar left,uchar right)
{
	Send_Byte(left);
	Send_Byte(right);
	EN_595_OUTPUT;
}

void Driver_595_Init(void)
{
	SET_DD_ST_CP;
}