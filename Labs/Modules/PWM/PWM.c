#include "PWM.h"

#define FULL 255	

void initPWM(){
	TCCR0A |= 0xFF; //set to fast PWM (timer register)
    TCCR0B |= (1 << CS00);
}

void setPWMA(uint8_t pmw_divide){
	OCCRA = FULL / pwm_divide;
}

void setPWMA(uint8_t pmw_divide){
	OCCRB = FULL / pwm_divide;
}