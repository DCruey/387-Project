#include "PWM.h"

void initPWM(){
	TCCR0A |= 0xFF; //set to fast PWM (timer register)
    TCCR0B |= (1 << CS00);
}

void setPWMA(uint8_t duty_cycle){ // Number from 1- 255
	OCCRA = duty_cycle;
}

void setPWMA(uint8_t duty_cycle){ // Number from 1- 255
	OCCRB = duty_cycle;
}