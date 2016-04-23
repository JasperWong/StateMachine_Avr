CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -DATMega16  -l -g -MLongJump -MHasMul -MEnhanced 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x4000 -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:30 -beeprom:0.512 -fihx_coff -S2
FILES = main.o ad_key.o lcd1602.o delay.o IO_Init.o usart.o music.o led.o 16SPI.o 595.o reset.o motor.o eeprom.o password.o 

FINAL:	$(FILES)
	$(CC) -o FINAL $(LFLAGS) @FINAL.lk   -lcatmega
main.o: D:\iccv7avr\include\iom16v.h D:\iccv7avr\include\macros.h D:\iccv7avr\include\AVRdef.h .\ad_key.h .\lcd1602.h .\IO_Init.h .\usart.h .\reset.h .\LED.h .\music.h .\eeprom.h .\Password.h
main.o:	main.c
	$(CC) -c $(CFLAGS) main.c
ad_key.o: D:\iccv7avr\include\iom16v.h .\ad_key.h D:\iccv7avr\include\macros.h D:\iccv7avr\include\AVRdef.h
ad_key.o:	ad_key.c
	$(CC) -c $(CFLAGS) ad_key.c
lcd1602.o: D:\iccv7avr\include\iom16v.h .\lcd1602.h .\delay.h
lcd1602.o:	lcd1602.c
	$(CC) -c $(CFLAGS) lcd1602.c
delay.o: D:\iccv7avr\include\iom16v.h
delay.o:	delay.c
	$(CC) -c $(CFLAGS) delay.c
IO_Init.o: D:\iccv7avr\include\iom16v.h
IO_Init.o:	IO_Init.c
	$(CC) -c $(CFLAGS) IO_Init.c
usart.o: D:\iccv7avr\include\iom16v.h D:\iccv7avr\include\macros.h D:\iccv7avr\include\AVRdef.h .\usart.h
usart.o:	usart.c
	$(CC) -c $(CFLAGS) usart.c
music.o: D:\iccv7avr\include\iom16v.h .\music.h D:\iccv7avr\include\macros.h D:\iccv7avr\include\AVRdef.h
music.o:	music.c
	$(CC) -c $(CFLAGS) music.c
led.o: D:\iccv7avr\include\iom16v.h .\595.h .\16SPI.h .\delay.h
led.o:	led.c
	$(CC) -c $(CFLAGS) led.c
16SPI.o: .\16SPI.h D:\iccv7avr\include\iom16v.h
16SPI.o:	16SPI.c
	$(CC) -c $(CFLAGS) 16SPI.c
595.o: .\16SPI.h D:\iccv7avr\include\iom16v.h .\595.h
595.o:	595.c
	$(CC) -c $(CFLAGS) 595.c
reset.o: D:\iccv7avr\include\iom16v.h D:\iccv7avr\include\macros.h D:\iccv7avr\include\AVRdef.h
reset.o:	reset.c
	$(CC) -c $(CFLAGS) reset.c
motor.o: D:\iccv7avr\include\iom16v.h D:\iccv7avr\include\macros.h D:\iccv7avr\include\AVRdef.h .\delay.h .\motor.h .\lcd1602.h
motor.o:	motor.c
	$(CC) -c $(CFLAGS) motor.c
eeprom.o: D:\iccv7avr\include\iom16v.h .\eeprom.h
eeprom.o:	eeprom.c
	$(CC) -c $(CFLAGS) eeprom.c
password.o: D:\iccv7avr\include\iom16v.h .\Password.h
password.o:	password.c
	$(CC) -c $(CFLAGS) password.c
