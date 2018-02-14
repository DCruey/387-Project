#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#inlcude <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>


/* Pin connections 
p4 = echo 1
p5 = echo 2
p23 = LED for echo 1
p24 = LED for echo 2
p28 = trigger to both echoes
*/

void initInterrupt0();
void initInterrupt1();

#define cent = 58 // 58 us per centimeter

int main(){
	
	DDRC = 0xFF;
	PORTC = 0x00;
	
	EICRA = 0x00;
	EIMSK = 0x00;

	initInterrupt0();
	initInterrupt1();
	
	while(1){
		_delay_ms(60);
		
		cli(); // Turn off interrupts
		
		// Output trigger signal on pin C5
		PORTC |= (1 << PC5);
		_delay_us(10);
		PORTC &= ~(1 << PC5);
		
		TCCR0B |= (1 << CS00); // turn counter 0 on with no pre-scaler (1 count per us)
		TCCR2B |= (1 << CS20); // turn counter 0 on with no pre-scaler (1 count per us)
		
		
		sei(); // Turn on interrupts
	}

	return 1;

}

void initInterrupt0(){ // Rising edge trigger on int0 (PD2)
	// int0 uses pin PD2
	EICRA |= (1 << ISC01) | (1 << ISC00);
	EIMSK |= (1 << INT0);	
	
	sei();
}

void initInterrupt1(){ // Rising edge trigger on int1 (PD3)
	// int1 uses pin PD3
	EICRA |= (1 << ISC11) | (1 << ISC10);
	EIMSK |= (1 << INT1);	
	
	sei();
}

void ISR(INT0_vect){ // Toggle port C0 on rising edge of int0(PD2)
	cli();
	
	if(TCNT0 < 2*cent){ // if it takes less than 2*cent for the signal to return, then the object is too close
		PORTC ^= (1 << PC0);
	}
	TCCR0B = 0x00; // turn counter 0 off
	TCNT0 = 0x00;
	
	sei();
}

void ISR(INT1_vect){ // Toggle port C1 on rising edge of int1(PD3)
	cli();
	
	if(TCNT2 < 2*cent){ // if it takes less than 2*cent for the signal to return, then the object is too close
		PORTC ^= (1 << PC1);
	}
	TCCR2B = 0x00; // turn counter 0 off
	TCNT2 = 0x00;
	
	
	sei();
}