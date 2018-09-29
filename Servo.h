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


void Servo_init(void);
void Servo_turn180(void);
void Servo_turn90(void);
void Servo_turn00(void);
void Servo_turn60(void);
void Servo_turn30(void);
void Servo_turn45(void);
void Servo_turn135(void);
void Servo_turn120(void);
void Servo_turn150(void);


#endif /* SERVO_H_ */