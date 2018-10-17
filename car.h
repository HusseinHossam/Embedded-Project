/*
 * car.h
 *
 * Created: 9/29/2018 4:14:28 PM
 *  Author: Hussein Hossam
 */ 


#ifndef CAR_H_
#define CAR_H_
#include "motor.h"
void PWM_vdCar_Forward( uint_8 Duty_Cycle );
void PWM_vdCar_Reverse( uint_8  Duty_Cycle );
void PWM_vdCar_Stop();


#endif /* CAR_H_ */
