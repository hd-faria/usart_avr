#ifndef __cplusplus
	#define __cplusplus
#endif

#ifndef F_CPU
	#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

int test1echo(void);
int teste2(void);

int main(){

	//DDRB |= (1<<PB7) | (1<<PB1);
	//PORTB &= ~(1<<PB7) & ~(1<<PB1);
	
	//DDRG |= (1 << PG0)|(1 << PG1)|(1 << PG2)|(1<<PG3);	//Make pins PG[0...3] output.
	//PORTG |= (1 << PG0)|(1 << PG1)|(1 << PG2)|(1<<PG3); //Turn all LEDs off
	
	
	USART0_Init8(103);

	while (1){
		
		test1echo();

//		teste2();

	}
	
}

int test1echo(void){
	unsigned char byte;

	PORTG &= ~(1<<PG0); //Turn red LED on while receiving
	//PORTB |= (1<<PB7);
	_delay_ms(500);		
	byte = USART0_Receive8();
	
	PORTG |= (1<<PG0); //Turn red LED off after receiving
	//PORTB &= ~(1<<PB7);
	_delay_ms(500);

	
	PORTG &= ~(1<<PG3); //Turn green LED on while transmitting 
	//PORTB |= (1<<PB1);
	_delay_ms(500);
	USART0_Transmit8(byte);
	byte = 0x0A;
	USART0_Transmit8(byte);
	
	PORTG |= (1<<PG3); //Turn green LED off after transmition
	//PORTB &= ~(1<<PB1);
	_delay_ms(500);	
	return true;
}

int teste2(){
	USART0_println("Hello, World!");
	return 0;
}