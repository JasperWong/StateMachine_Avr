#include <iom16v.h>

#define RS_CLR	PORTD &= ~(1 << PD2)
#define RS_SET	PORTD |= (1 << PD2)

#define RW_CLR	PORTD &= ~(1 << PD3)
#define RW_SET	PORTD |= (1 << PD3)

#define EN_CLR	PORTD &= ~(1 << PD6)
#define EN_SET	PORTD |= (1 << PD6)

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

void LCD_Init(void);
void LCD_clear(void);
void LCD_write_str(uchar X,uchar Y,uchar *s);
void LCD_write_char(uchar X,uchar Y,uchar data);


