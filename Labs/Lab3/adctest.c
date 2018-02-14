#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>

#define threshold 512

int main(){
	

ADMUX = 0x00;
ADCSRA = 0x00;
ADCSRB = 0x00;

DDRB = 0xFF;
DDRC = 0x00;
//PORTC = 0xFF;
PORTB = 0x00;

//uint16_t ADCValue = (ADCH << 8) | (ADCL << 1);

//VCC voltage reference
//Use pin C5 as ADC input
ADMUX |= (1 << REFS0)  | (1 << MUX2) | (1 << MUX0);

//ENable ADC
//Start ADC Conversion
//Enable auto-trigger
//Set prescaler to 8 so the ADC runs at 125 kHZ
ADCSRA |= (1 << ADATE);
ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
ADCSRA |= (1 << ADEN) | (1 << ADSC);

uint16_t ADCH_val;
// Use the ADC in freerunning mode
//ADCSRB |= ;

	while(1){

        PORTB ^= (1<<1);
        
        ADCH_val = (ADCL | (ADCH<<8));
		if(ADCH_val > threshold){
			PORTB |= (1<<0); 
		} else{
			PORTB &= ~(1<<0);
		} 
	}
		
	
	return 0;
}

