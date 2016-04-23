#ifndef __DRIVER_595_H
#define __DRIVER_595_H

#include <iom16v.h>

#define uchar 			unsigned char
#define uint 			unsigned int

/* ��һ��595������λ��������ܵĶ�ѡ
 * �ڶ���595������λ��������ܵ�λѡ
 * Q0~Q7��a~dp��ѡ
 * Q0~Q3��1~4λѡ
 * ����595ʱ���߲��ӣ������ߴ���
 * ����λ�ͣҽӸߵ�ƽ�����ʹ�ܣϣŽӵ͵�ƽ
 */

#define SET_DD_SH_CP		DDRB |= 1<<PB7
#define SET_DD_DS			DDRB |= 1<<PB5
#define SET_DD_ST_CP 		DDRB |= 1<<PB4
#define EN_595_OUTPUT 		PORTB &= ~(1<<PB4);PORTB |= 1<<PB4;PORTB &= ~(1<<PB4)
void Driver_595(uchar left,uchar right);
//void Driver_595(uchar high,uchar low);
void Driver_595_Init(void);

#endif 

