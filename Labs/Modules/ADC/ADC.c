#include "ADC.h"

void initADC(){
	//VCC voltage reference
	//Use pin C5 as ADC input
	ADMUX |= (1 << REFS0) | (1 << ADLAR) | (1 << MUX2) | (1 << MUX0);

	//ENable ADC
	//Start ADC Conversion
	//Enable auto-trigger
	//Set prescaler to 8 so the ADC runs at 125 kHZ
	ADCSRA |= (1 << ADATE);
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADEN) | (1 << ADSC);
}