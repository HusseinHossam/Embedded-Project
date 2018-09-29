/*
 * Servo.c
 *
 * Created: 9/27/2018 1:45:15 AM
 *  Author: Amr Eid
 */ 

#include "Servo.h"
#include "Timer0.h"

void Servo_init(void)
{
	timer0_PWM_init();
}


void Servo_turn90(void)
{
	timer0_PWM_90();
}

void Servo_turn180(void)
{
	timer0_PWM_180();
}

void Servo_turn00(void)
{
	timer0_PWM_00();
}

void Servo_turn60(void)
{
	timer0_PWM_60();
}

void Servo_turn30(void)
{
	timer0_PWM_30();
}

void Servo_turn45(void)
{
	timer0_PWM_45();
}

void Servo_turn150(void)
{
	timer0_PWM_150();
}

void Servo_turn120(void)
{
	timer0_PWM_120();
}

void Servo_turn135(void)
{
	timer0_PWM_135();
}