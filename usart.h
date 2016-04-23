#define uchar unsigned char
#define uint  unsigned int


void Usart_init(void);
void USART_Transmit( uchar data );
uchar USART_Receive( void );

void newline(void);
void blank(void);
