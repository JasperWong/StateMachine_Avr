#include<iom16v.h>
#include<macros.h>
#include"ad_key.h"
#include"lcd1602.h"
#include"IO_Init.h"
#include"usart.h"
#include"reset.h"
#include"LED.h"
#include"music.h"
#include"eeprom.h"
#include"Password.h"

uint  AdcData;                        //���ADCת���Ľ��
uchar AdcConCom = 0;				  //ADCת����ɱ�־
uchar select=0;						  //����ѡ���־
					
uint  beat;							  //���ֵ���
uchar IsPress=0;					  //�Ƿ��±�־λ
uchar function=0;					  //����ѡ���־λ
uchar Right_password[4];			  //�趨������
uchar Try_password[4];				  //����ƥ�������
uint  i;
uchar IsReset=0;
	
void main()
{	
	uchar *p;
	p="by Jasper";	
	Init();
	IsReset=0;
	IsReset=eeprom_read(100);
	
	if(!IsReset)										//�״ν��������������ʾ��ӭ����
	{
		Confirm();
		LCD_clear();
		delay_ms(200);
		LCD_write_str(5,0,"welcome");
	
		while(*p)									
		{
			LCD_write_char(i,1,*p);
			p++;
			i++;
			delay_ms(100);
		}
	}
	
													
	LCD_clear();										//��ʽ����ϵͳ
	LCD_write_str(0,0,"1bell2led3motor");				
	LCD_write_str(0,1,"4fix_password");
	
	while(1)
	{
		eeprom_write(100,0);
		if(select=='1')  								//������ģʽ
		{
			LCD_clear();
			LCD_write_str(0,0,"buzz..send * or");
			LCD_write_str(0,1,"shutdown to exit");
			Bell();
		}
		
		if(select=='2')  LED(); 						//ledģʽ
		
		if(select=='3')  Motor();						//���ģʽ
		
		if(select=='4')  Write_password();				//�޸�����ģʽ
		
	}
		
}

/*�ܳ�ʼ��*/
void Init()																			
{
	CLI(); 
	IO_Init();
	ADC_Init();
	Usart_init(); 
	LCD_Init();
	Driver_595_Init();
	SPI_Init ();
	T2_Init();
 	SEI();  
}
/*�ܳ�ʼ��*/


/*����*/
#pragma interrupt_handler UartRecvData:12											//����
void UartRecvData(void)																		
{
 	uchar temp;
	temp = UDR;
	if(temp=='s')	
	{	
		eeprom_write(100,1);
		Driver_595(0x00,0x00);
		delay_ms(10);
		reset();
	}
}
/*����*/


/*�������ı������Ҫ*/
#pragma interrupt_handler timer1_ovf_isr:iv_TIM1_OVF
void timer1_ovf_isr(void)															//�������ı������Ҫ
{
 	if(beat)
 	{	
 	 	PORTD ^= BIT(7);     //����������ڵ�ƽ��ת
 	 	TCNT1H=beat/256;			
  	 	TCNT1L=beat%256;     //��������Ӧ�ļ���ֵд���ʱ��
 	}
 	
}
/*�������ı������Ҫ*/


/*������*/
void Bell()
{

	unsigned int song[]=
	{
 		N6,12,N7,4,H1,8,H2,4,H3,4,/**/H2,32,/**/N7,12,N6,4,N5,8,N3,4,N5,4,/**/
 		N6,32,/**/H1,12,N6,4,N6,8,H3,8,/**/H2,32,/**/N5,22,N6,4,N7,8,H1,4,N7,4,/**/
 		N6,32, /**/H3,24,N6,8,/**/H2,24,H3,4,H2,4,/**/H1,16,H1,4,N6,4,H1,4,H2,4,/**/
 		N7,24,H1,4,H2,4,/**/H3,24,H2,4,H1,4,/**/H2,32,/**/
 		N5,4,N6,4,N7,16,N7,4,N5,4,/**/N6,32,/**/
 		N6,12,N7,4,H1,8,H2,4,H3,4,/**/H2,32,/**/N7,12,N6,4,N5,8,N3,4,N5,4,/**/
 		N6,32,/**/H1,12,N6,4,N6,8,H3,8,/**/H2,32,/**/N5,12,N6,4,N7,8,H1,4,N7,4,/**/
 		N6,32,/**/H3,24,N6,8,/**/H2,24,H3,4,H2,4,/**/H1,16,H1,4,N6,4,H1,4,H2,4,/**/
 		N7,24,H1,4,H2,4,/**/H3,24,H2,4,H1,4,/**/H2,32,/**/
 		N5,4,N6,4,N7,16,N6,4,N5,4,/**/N6,32,/**/H3,24,H2,4,H1,4,/**/H2,32,/**/
 		H1,24,N7,4,N6,4,/**/N7,24,H1,4,H2,4,/**/H3,24,H3,4,N6,4,/**/H2,24,H3,4,H2,4, /**/
 		H1,16,H1,4,N6,4,H1,4,H2,4,/**/N7,32,/**/H3,24,N6,8,/**/H2,24,H3,4,H2,4,/**/
 		H1,16,H1,4,N6,4,H1,4,H2,4,/**/N7,24,H1,4,H2,4,/**/H3,24,H2,4,H1,4,/**/
 		H2,24,H3,4,H2,4,/**/H1,24,N6,8,/**/N7,24,H1,8,/**/N6,32,/**/N6,32,/**/
 		0xFF //���ֽ�β��
	};
						
	Bell_Init();			//��ʼ��
	while(1)
	{
		Music(song);
	}
}

/*��������*/
void Music(unsigned int *pMusic) 
{ 
	
  	while(*pMusic!=0xFF) 			//0xFFΪ���ֽ�β�� 
    { 
		
      	TIMSK=0x04;				//Timer1����ж�ʹ��      
	  	beat=*pMusic;             //ȡ������
	  	TCNT1H=beat/256;			 
	  	TCNT1L=beat%256;          //��������Ӧ�ļ���ֵд���ʱ��,��ʼ����
                
      	pMusic++;					//��������ָ��+1 ,ȡ����
      	delay_ms((*pMusic)*52);   //������ʱ������ͨ������������ֲ����ٶ�

      	TIMSK=0x00;			   	//��ǰ��������,����Timer1����ж�
                
      	pMusic++;
							//��������ָ��+1��ָ����һ����
    }        
}
/*��������*/


/*led*/
void LED()																			
{
	uchar left=0x01;
	uchar right=0x80;
	LCD_clear();
	LCD_write_str(0,0,"led..");
	LCD_write_str(0,2,"1(2):control");

	while(1)
	{
		Driver_595(left,right);
		if(select=='2')
		{
			LCD_write_str(6,0,"MODE:2");
			left<<=1;
			right>>=1;
		}
		
		else
		{
			right<<=1;
			left>>=1;
			LCD_write_str(6,0,"MODE:1");
		}
		
		if(left==0x00)
		{
			if(select=='2') 
			{
				left=0x01;
		        right=0x80;
			}
			
			else
			{
				right=0x01;
		        left=0x80;
			}
		}
		
		delay_ms(100);
	}
}	
/*led*/



/*���*/
void Motor()
{
	uint Rspeed=500;
	uint Lspeed=500;
	LCD_clear();
	LCD_write_str(0,0,"L:500 R:500");
	LCD_write_str(0,1,"1(2):L 4(5):R");
	Motor_init();
	while(1)
	{
		if(select=='1') 
		{
			Lspeed=100;
			LCD_write_str(0,0,"L:100");
		}
		if(select=='2') 
		{
			Lspeed=300;
			LCD_write_str(0,0,"L:300");
		}
		if(select=='4') 
		{
			Rspeed=100;
			LCD_write_str(6,0,"R:100");
		}
		if(select=='5') 
		{
			Rspeed=300;
			LCD_write_str(6,0,"R:300");
		}
		motor(Lspeed,Rspeed);
	}

}
/*���*/


/*У������*/
void Confirm()
{
	uchar i;				//���ڼƴ���
	uchar Isture=1;
	uchar ture=0;
	Read_password();		//���ȶ�ȡ���������
	while(1)
	{
		
		LCD_clear();
		LCD_write_str(0,0,"password:");
		
		if(Isture==0) LCD_write_str(9,0,"Wrong!");
	
		ture=0;
		
		for(i=0;i<4;i++)			//��������
		{	
			delay_ms(100);
			while(!IsPress);
			Try_password[i]=select;
			LCD_write_char(i,1,'*');
		}

		for(i=0;i<4;i++)									//�봢��ĶԱ�
		{
			if(Right_password[i]==Try_password[i]) ture++;
		}

		if(ture==4) 					//���������ȷ				
		{
			break;
			select='N';
		}
		else Isture=0;
	}	
		
}
/*У������*/


/*��eepromд������*/
void Write_password()
{
	uint i=0;
	uchar temp[4];
	
	LCD_clear();
	LCD_write_str(0,0,"please enter");
	LCD_write_str(0,1,"the password");
	for(i=0;i<4;i++)
	{	
		delay_ms(100);
		while(!IsPress);
		temp[i]=select;
	}
	eeprom_write_string(0,temp);
	Driver_595(0x00,0x00);
	eeprom_write(100,1);
	reset();

}
/*��eepromд������*/


/*��ȡeeprom�д��������*/
void Read_password()
{
	uchar i=0;
	delay_ms(300);
	for(i=0;i<4;i++)
	{
		Right_password[i]=eeprom_read(i);
	}
	
}
/*��ȡeeprom�д��������*/


/*����ɨ���Լ��ж�*/
#pragma interrupt_handler t2_isr:4
void t2_isr()													//select��Ӧ�����ϵ�����,��Ҫ˵��ħ������...																							
{
	
	ADCSRA|= (1<<ADSC);
	while(!(ADCSRA & 0x10));
	AdcData=(uint)((ulong)ADCH * 4930 / 256);
	ADCSRA &= ~(0x10);															

	IsPress=0;						//���±�־λ����													
 	if(AdcData==4660)											//��Ϊ��proteus��ÿ�ε�ѹ�����������,����ֻ��"=="����ȡһ����Χ,����ʵ������Ҫ��Χ
	{
		ADCSRA|= (1<<ADSC);															
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);		
		if(AdcData==4660)
		{
			IsPress=1;
			select='1';
		}
	}
	
	if(AdcData==4390)										
	{
		ADCSRA|= (1<<ADSC);
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);
		if(AdcData==4390)
		{
			IsPress=1;
			select='2';
		}
	}
    if(AdcData==4140)	
	{
		ADCSRA|= (1<<ADSC);
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);
		if(AdcData==4140)
		{
			IsPress=1;
			select='3';
		}
	}
	if(AdcData==3870)	
	{
		ADCSRA|= (1<<ADSC);
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);
		if(AdcData==3870)
		{
			IsPress=1;
			select='4';
		}
	}
	if(AdcData==3601)	
	{
		ADCSRA|= (1<<ADSC);
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);
		if(AdcData==3601)
		{
			IsPress=1;
			select='5';
		}
	}
	if(AdcData==3350)	
	{
		ADCSRA|= (1<<ADSC);
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);
		if(AdcData==3350)
		{
			IsPress=1;
			select='6';
		}
	}
	if(AdcData==3100)	
	{
		ADCSRA|= (1<<ADSC);
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);
		if(AdcData==3100)
		{
			IsPress=1;
			select='7';
		}
	}
	if(AdcData==2830)  
	{
		ADCSRA|= (1<<ADSC);
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);
		if(AdcData==2830)
		{
			IsPress=1;
			select='8';
		}
	}
	if(AdcData==2580)	
	{
		ADCSRA|= (1<<ADSC);
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);
		if(AdcData==2580)
		{
			IsPress=1;
			select='9';
		}
	}
	if(AdcData==2310)	
	{
		ADCSRA|= (1<<ADSC);
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);
		if(AdcData==2310)
		{
			IsPress=1;
			select='*';		
			if(function!=5) 
			{
				Driver_595(0x00,0x00);
				eeprom_write(100,1);
				reset();
			}
		}
		
	}
		
	if(AdcData==2060)	
	{
		ADCSRA|= (1<<ADSC);
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);
		if(AdcData==2060)
		{
			IsPress=1;
			select='0';
		}
	}
	if(AdcData==1810)	
	{
		ADCSRA|= (1<<ADSC);
		while(!(ADCSRA & 0x10));
		AdcData=(uint)((ulong)ADCH * 4930 / 256);
		ADCSRA &= ~(0x10);
		if(AdcData==1810)
		{
			IsPress=1;
			select='#';
		}
	}
	
 	AdcConCom = 1; //��ADCת����ɱ�־
}
/*����ɨ���Լ��ж�*/
	
