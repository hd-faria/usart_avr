#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

bool test1(void);

int main(){

	
	DDRG |= (1 << PG0)|(1 << PG1)|(1 << PG2)|(1<<PG3);	//Make pins PG[0...3] output.
	
	while(1){
		PORTG &= ~(1<<PG3);			//Clear Pin 5 in PORTB
		_delay_ms(500);
		PORTG |= (1<<PG3);
		_delay_ms(500);
	}
}

bool test1(void){

}