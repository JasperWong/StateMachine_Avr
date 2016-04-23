#include<iom16v.h>
#include"lcd1602.h"
#include"delay.h"



/*��ʾ������д�뺯��*/
void LCD_write_com(uchar com) 
{
	RS_CLR;
	RW_CLR;
	EN_SET;
	PORTC=com;
	delay_us(5);
	EN_CLR;
}

/*��ʾ������д�뺯��*/
void LCD_write_data(uchar data) 
{
	RS_SET;
	RW_CLR;
	EN_SET;
	PORTC = data;
	delay_us(5);
	EN_CLR;
}

/*��ʾ�������ʾ*/
void LCD_clear(void) 
{
	LCD_write_com(0x01);
	delay_ms(5);
}

/*��ʾ���ַ���д�뺯��*/
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

/*��ʾ�����ַ�д�뺯��*/
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

/*��ʾ����ʼ������*/
void LCD_Init(void)
{
	DDRC = 0xFF;										/*I/O�ڷ�������						*/
	DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD6);
	LCD_write_com(0x38);								/*��ʾģʽ����						*/
	delay_ms(5);
	LCD_write_com(0x38);
	delay_ms(5);
	LCD_write_com(0x38);
	delay_ms(5);
	LCD_write_com(0x38);
	
	LCD_write_com(0x08);								/*��ʾ�ر�							*/
	LCD_write_com(0x01);								/*��ʾ����							*/
	LCD_write_com(0x06);								/*��ʾ����ƶ�����					*/
	delay_ms(5);
	LCD_write_com(0x0C);								/*��ʾ�����������					*/
}