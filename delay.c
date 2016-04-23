#include<iom16v.h>


/*延时函数*/
void delay_us(unsigned int n) 
{
	if (n == 0) 
	{
		return ;
	}
	while (--n);
}

/*延时函数*/
void delay_ms(unsigned int i)
{
	unsigned int a;
	unsigned char b;
	for (a = 1; a < i; a++) 
	{
		for (b = 1; b; b++) 
		{
			;
		}
	}
}