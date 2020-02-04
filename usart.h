/*
 * usart.h
 *
 * Created: 00/jan/2020 
 * Author: Henrique
 * Based on: 
 *  - http://ww1.microchip.com/downloads/en/devicedoc/doc7679.pdf
 *  - https://github.com/abcminiuser/avr-tutorials/blob/master/USART/Output/USART.pdf
 */ 


#ifndef USART_H_
#define USART_H_

// Modes of operation, based on Arduino`s HardwareSerial.h 
// Format:
// SERIAL_<WORD_SIZE><PARITY><STOP_BIT>
//  WORD_SIZE = [5,...,8]
//  PARITY = [N,O,E]
//      N for NONE
//      O for ODD
//      E for EVEN
//  STOP_BIT = [1,2]
#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x02
#define SERIAL_7N1 0x04
#define SERIAL_8N1 0x06
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x0A
#define SERIAL_7N2 0x0C
#define SERIAL_8N2 0x0E
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x22
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x2A
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x32
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x3A
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

#define UART_BUFFER 8

#define USART_BAUDRATE 9600 // TODO: Modify to allow programmer to set desired baudrate
#define BAUD_PRESCALE ((((F_CPU / 16) + (USART_BAUDRATE / 2)) / (USART_BAUDRATE)) - 1) 

/*
* Table 17-1 AT90CAN manual, page 180
*
* Asynchronous Normal Mode(U2Xn = 0)
** Equation for Calculating Baud Rate
*** BAUD = F_CPU / 16*(UBRRn + 1)
** Equation for Calculating UBRRn Value
*** UBRRn = (F_CPU / (16*BAUD)) - 1
*
* Asynchronous Double Speed Mode(U2Xn = 1)
** Equation for Calculating Baud Rate
*** BAUD = F_CPU / 8*(UBRRn + 1)
** Equation for Calculating UBRRn Value
*** UBRRn = (F_CPU / (8*BAUD)) - 1
*
* Synchronous Master Mode
** Equation for Calculating Baud Rate
*** BAUD = F_CPU / 2*(UBRRn + 1)
** Equation for Calculating UBRRn Value
*** UBRRn = (F_CPU / (2*BAUD)) - 1
*/

#ifdef __cplusplus
extern "C" {
#endif

void USART0_Init (unsigned int baud, unsigned char config);
void USART0_Init8 (unsigned int baud);
void USART0_Transmit8 (unsigned char data);
void USART0_Transmit9 (unsigned int data);
unsigned char USART0_Receive8 (void);
unsigned int USART0_Receive9 (void);
void USART0_Flush (void);

void USART1_Init8 (unsigned int baud);
void USART1_Transmit8 (unsigned char data);
void USART1_Transmit9 (unsigned int data);
unsigned char USART1_Receive8 (void);
unsigned int USART1_Receive9 (void);
void USART1_Flush (void);

void USART0_print(char msg[]);
void USART0_println(char msg[]);
char * USART0_read(void);

#ifdef __cplusplus
}
#endif


#endif /* USART_H_ */