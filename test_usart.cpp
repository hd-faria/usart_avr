#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

int main(){

	DDRG |= (1<<PG0);			//Make pin PB5 be an output.
	
	while(1){
		PORTG &= ~(1<<PG0);			//Clear Pin 5 in PORTB
		_delay_ms(500);
		PORTG |= (1<<PG0);
		_delay_ms(500);
	}
}