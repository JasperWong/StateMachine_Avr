#include <iom16v.h>
#include <macros.h>
#include "usart.h"


#define uchar unsigned char
#define uint  unsigned int



void Usart_init(void)
{
 	UCSRB = 0x00; 					       //�ش���
 	UCSRA = 0x02;					       //����ģʽ   M16����P151
 	UCSRC = BIT(URSEL) | 0x06;		       //дUCSRC�Ĵ���,�趨8��bit��1ֹͣλ���첽
 	UBRR  = 12;	 	  	   		           //�趨���ڲ�����Ϊ9600
 	UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);//ʹ�ܽ��ս����жϣ�ʹ���շ�
}


/*���ڷ���*/
void USART_Transmit( uchar data )
{
while ( !( UCSRA & (1<<UDRE)) ) ;  //�ȴ����ͻ�����Ϊ��
UDR = data;                        // �����ݷ��뻺�������������� 
} 



uchar USART_Receive( void )
{
while ( !(UCSRA & (1<<RXC)) );  // �ȴ���������
return UDR;                     // �ӻ������л�ȡ����������
} 




void newline(void)   //����
{
   USART_Transmit(0x0d);  //����һ���س�
   USART_Transmit(0x0a);  //����һ������
}

void blank(void)    //�ո�
{
   USART_Transmit(0x20);  
}

