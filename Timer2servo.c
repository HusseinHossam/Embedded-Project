/*
 * Timer0.c
 *
 * Created: 9/29/2018 12:31:49 PM
 *  Author: Amr Eid
 */ 

#include "Timer2servo.h"

void timer2_PWM_init(void)
{
	SET_BIT(timer2_PWM_DDR,timer2_PWM_pin);   //oc2 pin is output
	
	/*non inverting mode pwm (COM21=1 & COM20=0) 
	  set fast pwm mode for timer2 (WGM20=1 & COM21=1)
	   set prescaler = 1024 for 16MH CPU frequency(CS22=1 & COM21=1 & CS20=1)*/
	TCCR2=(1<<COM21)|(1<<WGM20)|(1<<WGM21)|(1<<CS20)|(1<<CS21)|(1<<CS22);
	TCNT2=0;
	OCR2=0;	
}

void Timer2_set_dutycycle(float32 duty_cycle)
{
	TCNT2=0;
	OCR2=(256.0/100.0)*duty_cycle;
}

void Timer2_off(void)
{
	TCCR2=00;
} 