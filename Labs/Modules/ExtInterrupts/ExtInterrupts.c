#include "ExtInterrups.h"

void initExtInterrupt0(){ // Rising edge trigger on int0 (PD2)
	// int0 uses pin PD2
	global uint8_t falling0 = 0;
	
	EICRA |= (0 << ISC01) | (1 << ISC00);
	EIMSK |= (1 << INT0);	
	
	sei();
}

void checkDistance0(){
	if(TCNT1 < 5*cent){
		PORTC |= (1 << PC0);
	} else {
		PORTC &= ~(1 << PC0);
	}

	TCNT1 = 0x00;
	TCCR1B = 0x00; // turn counter 0 off
	falling0 = 0;
}

ISR(INT0_vect){ // Toggle port C0 on rising edge of int0(PD2)
	cli();
	
	if(falling0 == 0){
		TCCR1B |= (1 << CS10); // turn counter 0 off
		falling0 = 1;
	} else {
		TCCR1B &= ~(1 << CS10);
	}

	sei();
}