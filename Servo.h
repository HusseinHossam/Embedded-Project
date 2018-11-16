/*
 * Servo.h
 *
 * Created: 9/27/2018 1:47:06 AM
 *  Author: Amr Eid
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

void Servo_vdInit(void);
void Servo_vdSetangle (uint8 angle);
void Servo_vdOFF (void);



#endif /* SERVO_H_ */