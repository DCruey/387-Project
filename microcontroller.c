#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main() {


    DDRD = 0xFF;
    PORTD = 0x00;

    uint8_t timerOver = 0;
    //DDRD = 0xFF;
    TCNT0 = 0x00;
    TCCR0B = (1<<CS00) | (1<<CS02);

    DDRC = 0xFF;
    PORTC = 0x00;
    DDRB = 0x00;
    PORTB = 0xFF;
    uint8_t inc2 = 0;
    uint8_t prevSw = 0x00;
    

 /*
  DDRC = (1 << PC5 | 1 << PC4 | 1 << PC3);


  PORTC |= 1 << PC5;

 
  PORTC &= ~(1 << PC4);
*/
 
  while(1) {





    while ((TIFR0 & 0x01) == 0);
	 TCNT0 = 0x00;
	 TIFR0 =0x01; //clear timer1 overflow flag		              
	 timerOver++;		 
	 if (timerOver>=10)
	 {
		// PORTD ^= (0x01 << LED);
         PORTD = PORTD + 1;			 
		 timerOver=0;
	 } 		 
    
    //PORTD = PORTD + mask;
   // _delay_ms(1000);

    if(PORTD == 0x0F) {
        PORTD = 0x00;

    }






/*

    if(!(PINB & (1<<PB0)) )
    {
        inc2 = inc2 + 1;
    } else {
        // PORTC = PORTC;
    }

    PORTC = inc2;

    if((PORTC )> 0xF0){
        PORTC = 0;
    }
*/




   if(prevSw && !(PINB & (1 << PB0)))
   {
          inc2 = inc2 + 1;
   }
   
   PORTC = inc2;
   prevSw = (PINB & (1 << PB0));

  }
  return 1;


}
