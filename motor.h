//���������ٶ�
//#define  Rspeed 250
//���������ٶ�
//#define  Lspeed 30

//IN1����ߵ�ƽ
#define  IN1_HIGH  PORTB|=(1<<PB0)
//IN1����͵�ƽ
#define  IN1_LOW   PORTB&=~(1<<PB0)

//IN2����ߵ�ƽ
#define  IN2_HIGH  PORTB|=(1<<PB1)
//IN2����͵�ƽ
#define  IN2_LOW   PORTB&=~(1<<PB1)

//IN3����ߵ�ƽ
#define  IN3_HIGH  PORTB|=(1<<PB2)
//IN3����͵�ƽ
#define  IN3_LOW   PORTB&=~(1<<PB2)

//IN4����ߵ�ƽ
#define  IN4_HIGH  PORTB|=(1<<PB3)
//IN4����͵�ƽ
#define  IN4_LOW   PORTB&=~(1<<PB3)

#define  uchar   unsigned char
#define  uint  	 unsigned int


void motor(uint Lspeed,uint Rspeed);
void Motor_Init();
void Motor();