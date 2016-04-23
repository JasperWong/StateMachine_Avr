#ifndef __SPI_H
#define __SPI_H

#include <iom16v.h>


#define uchar 			unsigned char
#define uint			unsigned int

#define SET_DD_MOSI_M 	DDRB |= 1<<PB5
#define SET_DD_MOSI_S 	DDRB &= ~(1<<PB5)
#define SET_DD_MISO_M 	DDRB &= ~(1<<PB4)
#define SET_DD_MISO_S 	DDRB |= 1<<PB4
#define SET_DD_SCK_M  	DDRB |= 1<<PB7
#define SET_DD_SCK_S  	DDRB &= ~(1<<PB7)
#define SET_DD_SS_M	  	DDRB |= 1<<PB4
#define SET_DD_SS_S   	DDRB &= ~(1<<PB4)

void SPI_Init (void);
void Send_Byte(uchar data);

#endif