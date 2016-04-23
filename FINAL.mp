NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0304 =    772. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0358  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0358   0EEA =   3818. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       01AC  __start
       01AC  __text_start
       01CE  _exit
       01CF  _main
       024A  _Init
       025B  _UartRecvData
       029D  _timer1_ovf_isr
       02C6  _Bell
       02EA  _Music
       0319  _LED
       0364  _Motor
       03C0  _Confirm
       0418  _Write_password
       045C  _Read_password
       0472  _t2_isr
       0706  _ADC_Init
       070F  _T2_Init
       0717  _LCD_write_com
       0724  _LCD_write_data
       0731  _LCD_clear
       0737  _LCD_write_str
       0752  _LCD_write_char
       0764  _LCD_Init
       0789  _delay_us
       0794  _delay_ms
       07A5  _IO_Init
       07BE  _Usart_init
       07C9  _USART_Transmit
       07CD  _USART_Receive
       07D1  _newline
       07D5  _blank
       07D7  _Bell_Init
       07DC  _SPI_Init
       07E5  _Send_Byte
       07EE  _Driver_595
       07FE  _Driver_595_Init
       0800  _reset
       0806  _motor
       080F  _Motor_init
       0820  _eeprom_write
       0833  _eeprom_read
       0844  _eeprom_write_string
       085C  empy16s
       086C  empy32s
       086C  empy32u
       08A0  pop_xgset00FC
       08A7  push_xgsetF0FC
       08A9  push_xgset30FC
       08AB  push_xgset00FC
       08AD  push_xgset003C
       08B2  push_xgsetF000
       08B7  pop_xgsetF000
       08BC  push_xgsetF00C
       08C3  pop_xgsetF00C
       08CA  push_xgset303C
       08D1  pop_xgset303C
       08D8  long_prolog
       08E6  long_epilog
       08F1  tstzero1
       08F7  tstzero2
       08FD  lsr32
       0909  asgnblk
       0921  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0304 =    772. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _AdcConCom
       0061  _select
       0062  _IsPress
       0063  _function
       0064  _IsReset
       0362  _right
       0363  _left
       0364  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0364   0012 =     18. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0364  __bss_start
       0364  _i
       0366  _Try_password
       036A  _Right_password
       036E  _beat
       0370  _AdcData
       0372  _Lspeed
       0374  _Rspeed
       0376  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0030 =     48. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
main.o	[ main.c ]
ad_key.o	[ ad_key.c ]
lcd1602.o	[ lcd1602.c ]
delay.o	[ delay.c ]
IO_Init.o	[ IO_Init.c ]
usart.o	[ usart.c ]
music.o	[ music.c ]
led.o	[ led.c ]
16SPI.o	[ _16SPI.c ]
595.o	[ _595.c ]
reset.o	[ reset.c ]
motor.o	[ motor.c ]
eeprom.o	[ eeprom.c ]
password.o	[ password.c ]
<library>	[ emul16s.s, emul32.s, gpop3.s, gpush.s, gpushy.s, gpushz.s, gpusha.s, longutil.s, lsr32.s, struct.s ]


User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512

