/*
 * Timer0.c
 *
 * Created: 9/29/2018 12:31:49 PM
 *  Author: Amr Eid
 */ 

#include "Timer0.h"

void timer0_PWM_init(void)
{
	SET_BIT(timer0_PWM_DDR,timer0_PWM_pin);   //oc0 pin is output
	
	/*non inverting modepwm (COM01=1 & COM00=0) 
	  set phase correct pwm mode for timer0 (WGM00=1 & COM01=0)
	   set prescaler = 256 for 8MH CPU frequency(CS02=1 & COM01=0 & CS00=0)*/
	TCCR0=(1<<COM01)|(1<<WGM00)|(1<<CS02);
	
	TCNT0=0;
	OCR0=0;	
}