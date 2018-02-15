
#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
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

uint8_t falling0 = 0;
uint8_t falling1 = 0;

uint8_t Time0_2 = 0x00; //second register for time 0 

#define cent 58 // 58 us per centimeter /  148 us per inch
#define velocity 340 // speed of the sound pulse




//10 cent: duty cycle ~= .90%
//5 cent: duty cycle ~= .45%

int main(){
	
	DDRC = 0xFF;
	PORTC = 0x00;
	
	EICRA = 0x00;
	EIMSK = 0x00;

	initInterrupt0();
	initInterrupt1();

	TIMSK0 = (1 << TOIE0);
	
	while(1){
		_delay_ms(60);
		
		cli(); // Turn off interrupts
		
		//TCCR0B = 0x00; // turn counter 0 off
		if(TCNT1 < 5*cent){
			PORTC |= (1 << PC0);
		} else {
			PORTC &= ~(1 << PC0);
		}

		TCNT1 = 0x00;
		TCCR1B = 0x00; // turn counter 0 off
		falling0 = 0;

		//TCCR0B = 0x00; // turn counter 0 off
		if((Time0_2 << 8 | TCNT0) < 5*cent){
			PORTC |= (1 << PC1);
		} else {
			PORTC &= ~(1 << PC1);
		}
		
		Time0_2 = 0x00;
		TCNT0 = 0x00;
		TCCR0B = 0x00; // turn counter 0 off
		falling1 = 0;

//		TCCR2B = 0x00; // turn counter 2 off
//		TCNT2 = 0x00;

		PORTC |= (1 << PC5);
		_delay_us(10);
		PORTC &= ~(1 << PC5);

		
		//TCCR0B |= (1 << CS00); // turn counter 0 on with no pre-scaler (1 count per us)
//		TCCR2B |= (1 << CS20); // turn counter 0 on with no pre-scaler (1 count per us)
		//waitPulse++;
		
		sei(); // Turn on interrupts
	}

	return 1;

}

void initInterrupt0(){ // Rising edge trigger on int0 (PD2)
	// int0 uses pin PD2
	EICRA |= (0 << ISC01) | (1 << ISC00);
	EIMSK |= (1 << INT0);	
	
	sei();
}

void initInterrupt1(){ // Rising edge trigger on int1 (PD3)
	// int1 uses pin PD3
	EICRA |= (0 << ISC11) | (1 << ISC10);
	EIMSK |= (1 << INT1);	
	
	sei();
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

ISR(INT1_vect){ // Toggle port C1 on rising edge of int1(PD3)
	cli();
	
	if(falling1 == 0){
		TCCR0B |= (1 << CS00); // turn counter 0 off
		falling1 = 1;
	} else {
		TCCR0B &= ~(1 << CS00);
	}
	
	sei();
}

ISR(TIMER0_OVF_vect){
	cli();
	
	Time0_2++;
	
	sei();
}
