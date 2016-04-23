#include "16SPI.h"


/* ʹ��SPI
 * ����ģʽ
 * MSB�ȷ�
 * �ޱ���
 * ʧ���ж�
 * 4��Ƶ
 * SPIģʽ0
 */
void SPI_Init (void)
{
	SET_DD_MOSI_M;
	SET_DD_MISO_M;
	SET_DD_SCK_M;
	SET_DD_SS_M;
	
	SPCR = 0x50;
	SPSR = 0x00;
}

void Send_Byte(uchar data)
{
	uchar i;
	while((SPSR&(1<<WCOL)));
	SPDR = data;
	while (!(SPSR&(1<<SPIF)));
	i = SPDR;
}

