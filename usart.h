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

#ifdef __cplusplus
}
#endif


#endif /* USART_H_ */