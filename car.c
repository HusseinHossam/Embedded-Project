/*
 * car.c
 *
 * Created: 9/29/2018 4:09:59 PM
 *  Author: Hussein Hossam
 */ 
#include "car.h"
void PWM_vdCar_Forward( uint_8 Duty_Cycle ) // Moving Car Forward
{
	
	TCNT0 = 0; // Timer 0 = 0
	SET_BIT(PORTB,PB0);
	CLEAR_BIT(PORTB,PB1);
	SET_BIT(PORTB,PB2);
	CLEAR_BIT(PORTB,PB3);
	OCR0 = ((Duty_Cycle*256/100)); // Output Compare equation depending on Duty_Cycle
	

}
void PWM_vdCar_Reverse( uint_8  Duty_Cycle ) // Moving Car Reverse
{

	TCNT0 = 0; // Timer 0 = 0
	SET_BIT(PORTB,PB1);
	CLEAR_BIT(PORTB,PB0);
	SET_BIT(PORTB,PB3);
	CLEAR_BIT(PORTB,PB2);
	OCR0 = ((Duty_Cycle*256/100)); // Output Compare equation depending on Duty_Cycle
	
}
void PWM_vdCar_Stop() // Stop Car
{
	CLEAR_BIT(PORTB,PB0);
	CLEAR_BIT(PORTB,PB1);
	CLEAR_BIT(PORTB,PB2);
	CLEAR_BIT(PORTB,PB3);
}
