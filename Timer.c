#include "Timer.h"
static uint_8 TimerOverFlow; // Eid
uint_8 IsMatched = 0;
ISR(TIMER2_OVF_vect)
{
	TimerOverFlow++;
}
ISR(TIMER1_COMPA_vect)
{ 
	IsMatched = 1;
}
void Timer_vdInit(uint_8 num , uint_8 mode, uint_8 value )
{
	if (num == 1)
	{
		if (mode == "Compare")
		{
			sei();
			TCCR1A |= (1<<COM1A1) | (1<<COM1A0);
			TCCR1B |= (1<<WGM12) | (1<<CS10) | (1<<CS12);
			TIMSK |= (1<<OCIE1A);
			TCNT1 = 0;
			OCR1A = value;
			/*
			-1 CTC Mode for OCR1A
			-2 1024 Pre-scaler 
			-3 SET OCR when output compare */
		}
		else if (mode == "Normal")
		{
			sei();
			TCCR1B |= (1<<CS10) | (1<<CS12);
			TIMSK |= (1<<TOIE1);
			TCNT1 = 0;
		}
		/* -1 Normal mode operation
		 * -2 1024 Pre-Scaler */ 
	} 
	else if (num == 2 ) 
	{
		if (mode == "Compare")
		{
			sei();
			TCCR2 |= (1<<WGM21)|(1<<COM21) | (1<<COM20) | (1<<CS22) | (1<<CS20);
			TCNT2 = 0;
			OCR2 = value;
			TIMSK |= 1<<OCIE2;
					
		}
		else if (mode == "Normal")
		{
			sei();
			TCCR2 |= (1<<COM21) | (1<<COM20) | (1<<CS22) | (1<<CS20);
			TCNT2 = 0;
			TIMSK|= 1<<TOIE2;
		}
		
	}
	
}
uint_32 Timer2_u32count(void)
{
	uint_32 Time = TCNT2 + (TimerOverFlow * 256);
	
	return (Time);
}
void Timer_vdOFF(uint_8 Timer_name)

{
	if (Timer_name=="Timer1")
	{
		TCCR1A = 0;
	}
	else if (Timer_name =="Timer2")
	{
		TCCR2 = 0;
	}
}
