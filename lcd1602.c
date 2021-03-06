#include<iom16v.h>
#include"lcd1602.h"
#include"delay.h"



/*显示屏命令写入函数*/
void LCD_write_com(uchar com) 
{
	RS_CLR;
	RW_CLR;
	EN_SET;
	PORTC=com;
	delay_us(5);
	EN_CLR;
}

/*显示屏命令写入函数*/
void LCD_write_data(uchar data) 
{
	RS_SET;
	RW_CLR;
	EN_SET;
	PORTC = data;
	delay_us(5);
	EN_CLR;
}

/*显示屏清空显示*/
void LCD_clear(void) 
{
	LCD_write_com(0x01);
	delay_ms(5);
}

/*显示屏字符串写入函数*/
void LCD_write_str(uchar x,uchar y,uchar *s) 
{
    if (y == 0) 
	{
    	LCD_write_com(0x80 + x);
    }
    else 
	{
    	LCD_write_com(0xC0 + x);
    }
    while (*s) 
	{
    	LCD_write_data( *s);
    	s ++;
    }
}

/*显示屏单字符写入函数*/
void LCD_write_char(uchar x,uchar y,uchar data) 
{
    if (y == 0) 
	{
    	LCD_write_com(0x80 + x);
    }
    else 
	{
    	LCD_write_com(0xC0 + x);
    }
    	LCD_write_data(data);  
}

/*显示屏初始化函数*/
void LCD_Init(void)
{
	DDRC = 0xFF;										/*I/O口方向设置						*/
	DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD6);
	LCD_write_com(0x38);								/*显示模式设置						*/
	delay_ms(5);
	LCD_write_com(0x38);
	delay_ms(5);
	LCD_write_com(0x38);
	delay_ms(5);
	LCD_write_com(0x38);
	
	LCD_write_com(0x08);								/*显示关闭							*/
	LCD_write_com(0x01);								/*显示清屏							*/
	LCD_write_com(0x06);								/*显示光标移动设置					*/
	delay_ms(5);
	LCD_write_com(0x0C);								/*显示开及光标设置					*/
}
