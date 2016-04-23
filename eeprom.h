#include<iom16v.h>

#define uchar unsigned char
#define uint  unsigned int

void eeprom_write(uchar add,uchar data);
uchar eeprom_read(uchar add);
void eeprom_write_string(uchar add,uchar temp[]);