#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "ExtInterrupts.h"

#define pwm_coma1 7
#define pwm_coma0 6
#define pwm_comb1 5
#define pwm_comb0 4

#define pwm_wgm0 0
#define pwm_wgm1 1
#define pwm_wgm2 3

#define pwm_cs0 0
#define pwm_cs1 1
#define pwm_cs2 2

initExtInterrupt0();
checkDistance0();

int main (){
    
    DDRD = 0xFF;
    TCCR0A |= 0xFF; //set to fast PWM (timer register)
    TCCR0B &= 0x00;;
    TCCR0B |= (1 << pwm_cs0);
    
    while (1){
//      TOP can be assigned to 0xFF(MAX) or the value in OCR0A
        
        OCR0A = 0x0F; //50% cycle (output compare register)
        OCR0B = 100;//Insert your code here
        
    }
    
    return 0;
    
}
