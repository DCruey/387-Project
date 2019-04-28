//Created by Andrew Cruey - Binghamton University//

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "motor.h"

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

int main(){

//PIN declarations for in/out including debugging leds
	DDRC = 0xFF;
	DDRB |= (1 << PB7);
	DDRB &= ~(1 << PB6);
	DDRD &= ~(1 << PD7);
	DDRD |= (1 << PD0);
	PIND |= (1<<7);
	PORTC = 0x00;

	EICRA = 0x00;
	EIMSK = 0x00;

	initInterrupt0();
	initInterrupt1();

//ultrasonic flags
	uint8_t ultra_front = 0;
	uint8_t ultra_right = 0;
	uint8_t ultra_left = 0;
	uint8_t randBit;

	TIMSK0 = (1 << TOIE0);


	uint8_t startFlag = (PIND & 0x80); //was 0x80

	while(1){
//IR input start/stop code
			while (!startFlag){
				startFlag = (PIND & 0x80);
				rightmotor_brake();
				leftmotor_brake();
			}
			startFlag = (PIND & 0x80);

		_delay_ms(60);

		cli(); // Turn off interrupts

//asigning flags when ultrasnoics are triggered
//had to use three different methods to use three ultrasoncis due to lack of counters on the 328
		if(TCNT1 < 20*cent){
			ultra_front = 1;
		} else {
			ultra_front = 0;
		}
		if((Time0_2 << 8 | TCNT0) < 6*cent){
			ultra_right = 1;
		} else {
			ultra_right = 0;
		}
		if(PINB>>6 == 1){
			ultra_left = 1;
		} else {
			ultra_left = 0;
		}


//using debugging leds
//leds trigger on breadboard when corresponding ultrasonic is lit
		if(ultra_front == 1){
			PORTC |= (1 << PC0);
		} else {
			PORTC &= ~(1 << PC0);
		}

		if(ultra_right == 1){
			PORTC |= (1 << PC1);
		} else {
			PORTC &= ~(1 << PC1);
		}

		if(ultra_left == 1){
			PORTB |= (1 << PB7);
		} else {
			PORTB &= ~(1 << PB7);
		}
//RIGHT Correction
//slightly adjusts motors to maintain straight movement and avoid maze walls
		if(ultra_left == 1){
			leftmotor_forward();
			_delay_ms(5);
			rightmotor_reverse();
			_delay_ms(100);

			leftmotor_coast();
			_delay_ms(5);
			rightmotor_coast();
			_delay_ms(145);
//STRAIGHT
		} else if(ultra_front == 0 && ultra_right == 0 && ultra_left == 0){
			leftmotor_forward();
			rightmotor_forward();

//LEFT Correction
//slightly adjusts motors to maintain straight movement and avoid maze walls
		} else if(ultra_right == 1){
			leftmotor_reverse();
			_delay_ms(5);
			rightmotor_forward();
			_delay_ms(145);

			leftmotor_coast();
			_delay_ms(5);
			rightmotor_coast();
			_delay_ms(145);

//LEFT or RIGHT turn
//makes a random turn to help traverse the maze and detect all mines
		} else if(ultra_front == 1){
			randBit = rand() % 2;
			if (randBit == 0) {
				leftmotor_reverse();
				_delay_ms(1500);
			} else {
				rightmotor_reverse();
				_delay_ms(1500);
			}


//BACK if caught anywhere else
		} else {
			leftmotor_reverse();
			_delay_ms(145);
			rightmotor_reverse();
			_delay_ms(200);

			leftmotor_coast();
			_delay_ms(145);
			rightmotor_coast();
			_delay_ms(200);
		}


//counters for ultrasonics
		TCNT1 = 0x00;
		TCCR1B = 0x00; // turn counter 0 off
		falling0 = 0;

		Time0_2 = 0x00;
		TCNT0 = 0x00;
		TCCR0B = 0x00; // turn counter 0 off
		falling1 = 0;

		PORTC |= (1 << PC5);
		_delay_us(10);
		PORTC &= ~(1 << PC5);

		sei(); // Turn on interrupts
	}

	return 1;

}


//ultrasonic interrupts
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
