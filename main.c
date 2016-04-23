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

uint  AdcData;                        //存放ADC转换的结果
uchar AdcConCom = 0;				  //ADC转换完成标志
uchar select=0;						  //键盘选择标志
					
uint  beat;							  //音乐调子
uchar IsPress=0;					  //是否按下标志位
uchar function=0;					  //功能选择标志位
uchar Right_password[4];			  //设定的密码
uchar Try_password[4];				  //尝试匹配的密码
uint  i;
uchar IsReset=0;
	
void main()
{	
	uchar *p;
	p="by Jasper";	
	Init();
	IsReset=0;
	IsReset=eeprom_read(100);
	
	if(!IsReset)										//首次进入输入密码和显示欢迎界面
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
	
													
	LCD_clear();										//正式进入系统
	LCD_write_str(0,0,"1bell2led3motor");				
	LCD_write_str(0,1,"4fix_password");
	
	while(1)
	{
		eeprom_write(100,0);
		if(select=='1')  								//蜂鸣器模式
		{
			LCD_clear();
			LCD_write_str(0,0,"buzz..send * or");
			LCD_write_str(0,1,"shutdown to exit");
			Bell();
		}
		
		if(select=='2')  LED(); 						//led模式
		
		if(select=='3')  Motor();						//电机模式
		
		if(select=='4')  Write_password();				//修改密码模式
		
	}
		
}

/*总初始化*/
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
/*总初始化*/


/*串口*/
#pragma interrupt_handler UartRecvData:12											//串口
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
/*串口*/


/*蜂鸣器改变调子需要*/
#pragma interrupt_handler timer1_ovf_isr:iv_TIM1_OVF
void timer1_ovf_isr(void)															//蜂鸣器改变调子需要
{
 	if(beat)
 	{	
 	 	PORTD ^= BIT(7);     //蜂鸣器接入口电平翻转
 	 	TCNT1H=beat/256;			
  	 	TCNT1L=beat%256;     //将音符对应的计数值写入计时器
 	}
 	
}
/*蜂鸣器改变调子需要*/


/*蜂鸣器*/
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
 		0xFF //音乐结尾符
	};
						
	Bell_Init();			//初始化
	while(1)
	{
		Music(song);
	}
}

/*播放音乐*/
void Music(unsigned int *pMusic) 
{ 
	
  	while(*pMusic!=0xFF) 			//0xFF为音乐结尾符 
    { 
		
      	TIMSK=0x04;				//Timer1溢出中断使能      
	  	beat=*pMusic;             //取出音符
	  	TCNT1H=beat/256;			 
	  	TCNT1L=beat%256;          //将音符对应的计数值写入计时器,开始发声
                
      	pMusic++;					//乐谱音符指针+1 ,取拍数
      	delay_ms((*pMusic)*52);   //节拍延时，可以通过这里调整音乐播放速度

      	TIMSK=0x00;			   	//当前音符结束,屏蔽Timer1溢出中断
                
      	pMusic++;
							//乐谱音符指针+1，指向下一音符
    }        
}
/*播放音乐*/


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



/*电机*/
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
/*电机*/


/*校验密码*/
void Confirm()
{
	uchar i;				//用于计次数
	uchar Isture=1;
	uchar ture=0;
	Read_password();		//首先读取储存的密码
	while(1)
	{
		
		LCD_clear();
		LCD_write_str(0,0,"password:");
		
		if(Isture==0) LCD_write_str(9,0,"Wrong!");
	
		ture=0;
		
		for(i=0;i<4;i++)			//输入密码
		{	
			delay_ms(100);
			while(!IsPress);
			Try_password[i]=select;
			LCD_write_char(i,1,'*');
		}

		for(i=0;i<4;i++)									//与储存的对比
		{
			if(Right_password[i]==Try_password[i]) ture++;
		}

		if(ture==4) 					//如果密码正确				
		{
			break;
			select='N';
		}
		else Isture=0;
	}	
		
}
/*校验密码*/


/*向eeprom写入密码*/
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
/*向eeprom写入密码*/


/*读取eeprom中储存的密码*/
void Read_password()
{
	uchar i=0;
	delay_ms(300);
	for(i=0;i<4;i++)
	{
		Right_password[i]=eeprom_read(i);
	}
	
}
/*读取eeprom中储存的密码*/


/*键盘扫描以及判断*/
#pragma interrupt_handler t2_isr:4
void t2_isr()													//select对应键盘上的数字,不要说我魔鬼数字...																							
{
	
	ADCSRA|= (1<<ADSC);
	while(!(ADCSRA & 0x10));
	AdcData=(uint)((ulong)ADCH * 4930 / 256);
	ADCSRA &= ~(0x10);															

	IsPress=0;						//按下标志位清零													
 	if(AdcData==4660)											//因为在proteus中每次电压都不会有误差,所以只需"=="不用取一个范围,在现实中则需要范围
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
	
 	AdcConCom = 1; //置ADC转换完成标志
}
/*键盘扫描以及判断*/
	
