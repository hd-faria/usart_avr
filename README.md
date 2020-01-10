# usart_avr

Library to use usart communication on AT90CAN uC.

- USART0:
  - RXD0(PDI): PE0
  - TXD0(PDO): PE1
- USART1:
  - RXD1(INT2): PD2
  - TXD1(INT3): PD3

## Manifesto

- .vscode
- .gitignore
- README.md
- Makefile
- test_usart.cpp
- usart.c
- usart.h

## Microcontroller Fuses

- BODLEVEL = DISABLED
- TA0SEL = [ ]
- OCDEN = [ ]
- JTAGEN = [X]
- SPIEN = [X]
- WDTON = [ ]
- EESAVE = [ ]
- BOOTSZ = 4096W_7000
- BOOTRST = [ ]
- CKDIV8 = [ ]
- CKOUT = [ ]
- SUT_CKSEL = EXTXOSC_8MHZ_16MHZ_1KCK_65MS

- EXTENDED = 0xFF (valid)
- HIGH = 0x99 (valid)
- LOW = 0xCF (valid)
