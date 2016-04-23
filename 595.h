#ifndef __DRIVER_595_H
#define __DRIVER_595_H

#include <iom16v.h>

#define uchar 			unsigned char
#define uint 			unsigned int

/* 第一个595控制四位共阳数码管的段选
 * 第二个595控制四位共阳数码管的位选
 * Q0~Q7接a~dp段选
 * Q0~Q3接1~4位选
 * 两个595时钟线并接，数据线串接
 * 主复位ＭＲ接高电平，输出使能ＯＥ接低电平
 */

#define SET_DD_SH_CP		DDRB |= 1<<PB7
#define SET_DD_DS			DDRB |= 1<<PB5
#define SET_DD_ST_CP 		DDRB |= 1<<PB4
#define EN_595_OUTPUT 		PORTB &= ~(1<<PB4);PORTB |= 1<<PB4;PORTB &= ~(1<<PB4)
void Driver_595(uchar left,uchar right);
//void Driver_595(uchar high,uchar low);
void Driver_595_Init(void);

#endif 

