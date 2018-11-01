Project:      .\exhibition1
Build Number: 10
Date:         Fri Oct 26 01:06:37 2018
Compiler:     ICCAVR
Version:      8.28.05
Device:       ATMega128

NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses
  ROM 3% full. 2876 out of 131072 bytes used (does not include absolute areas).
  RAM 43 bytes used (does not include stack usage).

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   00D4     28 =     40. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       00D4  __idata_start
       00FC  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   00FC    B14 =   2836. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       007E  __start
       007E  __text_start
       00A0  _exit
       00A1  _GLCD_Rectangle
       00D6  _GLCD_Circle
       014E  _GLCD_Line
       01FF  _delay
       020C  _GLCD_InitializeInterface
       0214  _GLCD_CheckStatus
       0224  _GLCD_WriteCommand
       0234  _GLCD_WriteData
       0244  _GLCD_ReadData
       0258  _GLCD_SetAddressPointer
       0267  _GLCD_ClearText
       027A  _GLCD_ClearCG
       028E  _GLCD_ClearGraphic
       02A1  _GLCD_WriteChar
       02A8  _GLCD_WriteString
       02B7  _GLCD_TextGoTo
       02CB  _GLCD_DefineCharacter
       02E9  _GLCD_SetPixel
       032F  _GLCD_WriteDisplayData
       0337  _GLCD_GraphicGoTo
       0353  _GLCD_Initialize
       037C  _delay_ms
       0392  _GLCD_Clear
       0395  _tx_char
       0399  _tx_string
       03A9  _Bluetooth
       03B3  _GLCD_select
       03D0  _GLCD_dselect
       03ED  _up
       043F  _down
       0491  _right
       04E3  _left
       0535  _main
       0567  <LIBRARY>
       0567  push_arg4
       0569  push_arg2
       056C  mod16s
       0570  div16s
       058A  mod16u
       058C  div16u
       058D  xdiv16u
       05A6  empy16s
       05B6  pop_xgset003C
       05BB  pop_xgset00FC
       05C2  pop_xgsetF0FC
       05CD  push_xgsetF0FC
       05CF  push_xgset30FC
       05D1  push_xgset00FC
       05D3  push_xgset003C
       05D8  push_xgsetF000
       05DD  pop_xgsetF000
       05E2  push_xgset303C
       05E9  pop_xgset303C
       05F0  push_xgsetF03C
       05F9  pop_xgsetF03C
       0602  lsl8
       0608  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100     28 =     40. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0100  __data_start
       0100  _color
       0101  _x
       0103  _y
       0105  _baudrate
       0128  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0128      3 =      3. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0128  _BUFF
       0128  __bss_start
       012A  _flag
       012B  __bss_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0004     7C =    124. bytes (abs,ovr,rom,code)

Files Linked      [ module(s) ]

C:\iccv8avr\lib\crtatmega.o	[ crtatmega.s ]
.\.objs\main.o	[ main.c ]
<library>	[ asave.s, div16s.s, div16u.s, emul16s.s, gpop2.s, gpop3.s, gpop5.s, gpush.s, gpushy.s, gpusha.s, gpushb.s ]
[ lsl8.s ]

User Global Definitions

ram_end = 0x10ff
hwstk_size = 0x14

Area Definitions

-bfunc_lit:0xd4.0x10000
-bdata:0x100.0x10ff

Additional Flags
  -e:0x20000
