/*
 * File Name : motor.c
 * Description : Motor driver 
 *  Created on: 29/9/2018
 *      Author: Hussein Hossam
 */
#include "motor.h"

void PWM_vdMotorInit() // initialization PWM function
{
	/*	PWM configuration
	*	FAST PWM 
	*/
	SET_BIT(TCCR0,WGM01); 
	SET_BIT(TCCR0,WGM00);
	
	
	// Non- inverting 
	SET_BIT(TCCR0,COM01);
		
	// Motor Prescaling 
	SET_BIT(TCCR0,CS02);
	
	SET_BIT(DDRB,PB4); // PB4 : PWM enable pin of H-bridge 
	 
	OCR0 = 0; // Output Compare Register 
	
	//Left Motor selections
	SET_BIT(DDRB,PB0);
	SET_BIT(DDRB,PB1);
	
	//Right Motor selections
	SET_BIT(DDRB,PB2);
	SET_BIT(DDRB,PB3);
}
