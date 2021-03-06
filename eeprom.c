#include<iom16v.h>
#include"eeprom.h"

void eeprom_write(uchar add,uchar data)
{	
		uint sreg;									//��ʱ����״̬
		sreg=SREG;
		SREG = ~0x80;
		while(EECR&(1<<EEWE));
		EEARH=0x00;
		EEARL=add;
		EEDR=data;
		EECR|=(1<<EEMWE);
		EECR&=~(1<<EEWE);
		EECR|=(1<<EEWE);
		SREG=sreg;
}

uchar eeprom_read(uchar add)
{		
		
		uint sreg;									//��ʱ����״̬
		sreg=SREG;
		SREG = ~0x80;
		while(EECR&(1<<EEWE));
		EEARH=0X00;
		EEARL=add;
		EECR|=(1<<EERE);
		SREG=sreg;
		return EEDR;
}

void eeprom_write_string(uchar add,uchar temp[])
{
	uchar i=0;
	while(temp[i]!='\0')
	{
		eeprom_write(add,temp[i]);
		i++;
		add++;
	}
}


/*void write0(uchar add,uchar num,uchar *p_data)
{
	SREG=0x00;
		while(num--)
		while(EECR&(1<<EEPE));
		EEARH=0x00;
		EEARL=add;
		EEDR=data;
		EECR|=(1<<EEMPE);
		EECR&=~(1<<EEPE);
		EECR|=(1<<EEPE);
		*/