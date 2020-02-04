/*
 * usart.c
 *
 * Created: 09/jan/2020 
 * Author: Henrique
 * Based on: 
 *  - http://ww1.microchip.com/downloads/en/devicedoc/doc7679.pdf
 *  - https://github.com/abcminiuser/avr-tutorials/blob/master/USART/Output/USART.pdf
 */ 

#include <avr/io.h>
#include <string.h>
#include "usart.h"

void USART0_Init (unsigned int baud, unsigned char config){
	/* Set baud rate */
	UBRR0H = (unsigned char) (((((F_CPU / 16) + (baud / 2)) / (baud)) - 1) >> 8);
	UBRR0L = (unsigned char) ((((F_CPU / 16) + (baud / 2)) / (baud)) - 1);

	/* Set frame format */
	UCSR0C = config;
	/* Enable receiver and transmiter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

}

void USART0_Init8 (unsigned int baud){
	/* Set baud rate */

	UBRR0H = (unsigned char) (BAUD_PRESCALE >> 8);
	UBRR0L = (unsigned char) (BAUD_PRESCALE);

	/* Set frame format: 8data, no parity and 2stop bits */
	UCSR0C = (0 << UMSEL0) | (0 << UPM0) | (1 << USBS0) | (3 << UCSZ0);
	/* Enable receiver and transmiter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

}

void USART0_Transmit8 (unsigned char data){
	
	/* Wait for empty transmit buffer */
	while ( !(UCSR0A & (1 << UDRE0))){
		/* WAITING */
	}

	/* Put data into buffer, sends the data */
	UDR0 = data;
	
}

// TODO: Modify USART0_Init to setup 9bit data config.
void USART0_Transmit9 (unsigned int data){
	
	/* Wait for empty transmit buffer */
	while ( !(UCSR0A & (1 << UDRE0))){
		/* WAITING */
	}

	/* Copy 9th bit to TXB8*/
	UCSR0B &= ~(1 << TXB80);
	if ( data & 0x0100){
		UCSR0B |= (1 << TXB80);
	}
	
	/* Put data into buffer, sends the data */
	UDR0 = data;

}
unsigned char USART0_Receive8 (void){

	/* Wait for data to be received */
	while ( !(UCSR0A & (1 << RXC0))){
		/* WAITING ... */
	}

	/* Get and return data from buffer */
	return UDR0;

}
unsigned int USART0_Receive9 (void){

	unsigned char status, resh, resl;
	
	/* Wait for data to be received */
	while( !(UCSR0A & (1 << RXC0))){
		/* WAITING ... */
	}

	/* Get status and 9th bit, then data from buffer*/
	status = UCSR0A;
	resh = UCSR0B;
	resl = UDR0;

	/* If error, return -1 */
	if( status & ((1 << FE0) | (1 << DOR0) | (1 << UPE0)) ){
		return -1;
	}

	/* Filter 9th bit, then return */
	resh = (resh >> 1) & 0x01;
	return ((resh << 8) | resl);
	
}

void USART0_Flush (void){
	unsigned char dummy;
	while(UCSR0A & (1 << RXC0)){
		dummy = UDR0;
	}
}

void USART1_Init8 (unsigned int baud){
	/* Set baud rate */
	UBRR1H = (unsigned char) (BAUD_PRESCALE >> 8);
	UBRR1L = (unsigned char) (BAUD_PRESCALE);

	/* Set frame format: 8data, no parity and 2stop bits */
	UCSR1C = (0 << UMSEL1) | (0 << UPM1) | (1 << USBS1) | (3 << UCSZ1);
	/* Enable receiver and transmiter */
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);

}

void USART1_Transmit8 (unsigned char data){
	
	/* Wait for empty transmit buffer */
	while ( !(UCSR1A & (1 << UDRE1))){
		/* WAITING */
	}

	/* Put data into buffer, sends the data */
	UDR1 = data;

}

// TODO: Modify USART1_Init to setup 9bit data config.
void USART1_Transmit9 (unsigned int data){
	
	/* Wait for empty transmit buffer */
	while ( !(UCSR1A & (1 << UDRE1))){
		/* WAITING */
	}

	/* Copy 9th bit to TXB8*/
	UCSR1B &= ~(1 << TXB81);
	if ( data & 0x0100){
		UCSR1B |= (1 << TXB81);
	}
	
	/* Put data into buffer, sends the data */
	UDR1 = data;

}

unsigned char USART1_Receive8 (void){
	
	/* Wait for data to be received */
	while ( !(UCSR1A & (1 << RXC1))){
		/* WAITING ... */
	}

	/* Get and return data from buffer */
	return UDR1;

}
unsigned int USART1_Receive9 (void) {
	
	unsigned char status, resh, resl;
	
	/* Wait for data to be received */
	while( !(UCSR1A & (1 << RXC1))){
		/* WAITING ... */
	}

	/* Get status and 9th bit, then data from buffer*/
	status = UCSR1A;
	resh = UCSR1B;
	resl = UDR1;

	/* If error, return -1 */
	if( status & ((1 << FE1) | (1 << DOR1) | (1 << UPE1)) ){
		return -1;
	}

	/* Filter 9th bit, then return */
	resh = (resh >> 1) & 0x01;
	return ((resh << 8) | resl);
	
}

void USART1_Flush (void){
	unsigned char dummy;
	while(UCSR0A & (1 << RXC0)){
		dummy = UDR0;
	}
}

void USART0_print(char msg[]){
	int i = 0;
	while (i < strlen(msg)){
		USART0_Transmit8(msg[i]);
		i++;
	}
}

void USART0_println(char msg[]){
	int i = 0;
	while (i < strlen(msg)){
		USART0_Transmit8(msg[i]);
		i++;
	}
	USART0_Transmit8(0x0A); // new line
}

char * USART0_read(void){
	int i = 0;
	unsigned char buffer[UART_BUFFER];
	do{
		buffer[i] = USART0_Receive8();
		i++;
	}while ((i<UART_BUFFER)&& ~(buffer[i-1]=='\n'));
	buffer[i] = '\0'; // new line

	return buffer;
}