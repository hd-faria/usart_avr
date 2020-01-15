#ifndef __cplusplus
	#define __cplusplus
#endif

#ifndef F_CPU
	#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

bool test1echo(void);

int main(){

	
	DDRG |= (1 << PG0)|(1 << PG1)|(1 << PG2)|(1<<PG3);	//Make pins PG[0...3] output.
	PORTG |= (1 << PG0)|(1 << PG1)|(1 << PG2)|(1<<PG3); //Turn all LEDs off
	
	USART0_Init8(103);

	while (1){
		
		test1echo();

	}
	
}

bool test1echo(void){
	unsigned char byte;

	PORTG &= ~(1<<PG0); //Turn red LED on while receiving
	//_delay_ms(500);		
	byte = USART0_Receive8();
	
	PORTG |= (1<<PG0); //Turn red LED off after receiving
	//_delay_ms(500);	
	PORTG &= ~(1<<PG3); //Turn green LED on while transmitting 
	//_delay_ms(500);
	USART0_Transmit8(byte);
	byte = 0x0A;
	USART0_Transmit8(byte);
	
	PORTG |= (1<<PG3); //Turn green LED off after transmition
	//_delay_ms(500);	
	return true;
}
