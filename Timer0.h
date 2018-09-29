/*
 * Timer0.h
 *
 * Created: 9/29/2018 12:31:35 PM
 *  Author: Amr Eid
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

#define timer0_PWM_90()	TCNT0=0;\
						OCR0=DUTY_CYCLE_90
						
#define timer0_PWM_180()TCNT0=0;\
						OCR0=DUTY_CYCLE_180

#define timer0_PWM_00()	TCNT0=0;\
						OCR0=DUTY_CYCLE_00
						
#define timer0_PWM_60()	TCNT0=0;\
						OCR0=DUTY_CYCLE_60
						
#define timer0_PWM_30()	TCNT0=0;\
						OCR0=DUTY_CYCLE_30
						
#define timer0_PWM_45()	TCNT0=0;\
						OCR0=DUTY_CYCLE_45
						
#define timer0_PWM_135()	TCNT0=0;\
						OCR0=DUTY_CYCLE_135

#define timer0_PWM_120()	TCNT0=0;\
						OCR0=DUTY_CYCLE_120

#define timer0_PWM_150()	TCNT0=0;\
							OCR0=DUTY_CYCLE_150


#define DUTY_CYCLE_90 23 //86 degree  
#define DUTY_CYCLE_180	32//
#define DUTY_CYCLE_00	15 // 5 degree=16
#define DUTY_CYCLE_30	18// 27.5 degree
#define DUTY_CYCLE_60	21//62 degree
#define DUTY_CYCLE_45	20//50 degree
#define DUTY_CYCLE_150	29//154 degree
#define DUTY_CYCLE_135	27//120 degree
#define DUTY_CYCLE_120	26//50 degree

#define timer0_PWM_DDR DDRB
#define timer0_PWM_pin  3

void timer0_PWM_init(void);



#endif /* TIMER0_H_ */