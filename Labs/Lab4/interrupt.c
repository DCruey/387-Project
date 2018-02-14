/*
 *      Author: Charles Minchau (SmiteMeSmith)
 *      Program uses a ATMega328p MCU to query a HC-SR04 ultrasonic module. Then Calculates and displays the distance to a object in cm on the NewHaven display.
 *
 *      The ultrasonic module is triggered every 60 ms by setting pin PC4 (the trigger) high for 10 us. A change in state on pin PC5 (the echo)
 *      causes a interrupt. The interrupt checks if PC5 is high. If it is a timer is started that increments every micro second. Once PC5 triggers a
 *      interrupt again and is low the result is calculated and displayed in centimeters on the NewHaven display. Distance in cm is calculated
 *      by the amount of microseconds PC5 (the echo) is active high divided by 58.
 *
 *      Pin placement of ATMega328p:
 *      Port D[7-0]			NewHavenDisplay DB[7-0]
 *      Pin PC0				NewHavenDisplay RW
 *      Pin PC1				NewHavenDisplay RS
 *      Pin PC2				NewHavenDisplay E
 *      Pin PC3				Debugging LED Active High
 *      Pin PC4				HC-SR04 Trig
 *      Pin PC5				HC-SR04 Echo
 */
#define F_CPU 1000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/*******************************************INITALIZE PORTS, TIMER, AND INTURRUPTS*******************************************/
void init() {
	DDRD = 0xFF;							// Port D all output. Display: DB0 - DB7 as PD0 - PD7
	DDRC = 0xFF;							// Port C all output. PC0: RW		PC1: RS		PC2: E
	DDRC &= ~(1<<DDC5);						// Set Pin C5 as input to read Echo
	PORTC |= (1<<PC5);					// Enable pull up on C5
	PORTC &= ~(1<<PC4);						// Init C4 as low (trigger)

	PRR &= ~(1<<PRTIM1);					// To activate timer1 module
	TCNT1 = 0;								// Initial timer value
	TCCR1B |= (1<<CS10);					// Timer without prescaller. Since default clock for atmega328p is 1Mhz period is 1uS
	TCCR1B |= (1<<ICES1);					// First capture on rising edge

//	PCICR = (1<<PCIE1);						// Enable PCINT[14:8] we use pin C5 which is PCINT13
//	PCMSK1 = (1<<PCINT13);					// Enable C5 interrupt
	EICRA = 0x0F;
	EIMSK = 0x03;	
	sei();									// Enable Global Interrupts
}
/*******************************************MAIN PROGRAM*******************************************/
int main() {
	init();
//	PORTC |= (1<<PC3);
	while (1) {
		_delay_ms(60); 							// To allow sufficient time between queries (60ms min)

		PORTC |= (1<<PC4);						// Set trigger high
		_delay_us(10);							// for 10uS
		PORTC &= ~(1<<PC4);						// to trigger the ultrasonic module
	}
}
/*******************************************INTURRUPT PCINT1 FOR PIN C5*******************************************/
ISR(PCINT1_vect) {
/*	if (bit_is_set(PINC,PC5)) {					// Checks if echo is high
		TCNT1 = 0;								// Reset Timer
		PORTC |= (1<<PC3);
	} else {
	//	uint16_t numuS = TCNT1;					// Save Timer value
		uint8_t oldSREG = SREG;
		cli();									// Disable Global interrupts

		SREG = oldSREG;							// Enable interrupts
		PORTC &= ~(1<<PC3);						// Toggle debugging LED
	}
*/
PORTC |= (1<<PC3);
}
