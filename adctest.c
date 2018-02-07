#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>


int main(){
	

ADMUX = 0x00;
ADCSRA = 0x00;
ADCSRB = 0x00;

DDRB = 0xFF;
DDRC = 0x00;
PORTC = 0xFF;
PORTB = 0x00;


//VCC voltage reference
//Use pin C5 as ADC input
ADMUX |= (1 << REFS0) | (1 << ADLAR) | (1 << MUX2) | (1 << MUX0);

//ENable ADC
//Start ADC Conversion
//Enable auto-trigger
//Set prescaler to 8 so the ADC runs at 125 kHZ
ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADPS1) | (1 << ADPS0);

// Use the ADC in freerunning mode
//ADCSRB |= ;

	while(1){

    PORTB = ADCH;

	/*	if(ADCH > 0xC0){
			PORTB = 0xFF; 
		} else{
			PORTB = 0x00;
		} */
	}
		
	
	return 0;
}
