#include"Timer_Init.h"

void ICU_Timer1_vdInit (void)
{
	sei();			/* Enable global interrupt */
	TIMSK = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A = 0;		/* Set all bit to zero Normal operation */
}

void ICU_Timer1_vdInit_Risingedge(void)
{
	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/
	TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
}


void ICU_Timer1_vdInit_Fallingedge(void)
{
	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
	TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
}

void ICU_Timer1_vdWaitForRisingedge(void)
{
	while ((TIFR & (1 << ICF1)) == 0);/* Wait for rising edge */
}

void ICU_Timer1_vdWaitForFallingedge(void)
{
	while ((TIFR & (1 << ICF1)) == 0);/* Wait for falling edge */
}

void ICU_Timer1_vdStop (void)
{
	TCCR1B = 0x00;
}
-----------------------------------------------------------------------------------
void ICU_Timer3_vdInit (void)
{
	sei();			/* Enable global interrupt */
	ETIMKS = (1 << TOIE3);	/* Enable Timer3 overflow interrupts */
	TCCR3A = 0;		/* Set all bit to zero Normal operation */
}

void ICU_Timer3_vdInit_Risingedge(void)
{
	TCNT3 = 0;	/* Clear Timer counter */
	TCCR3B = 0x41;	/* Capture on rising edge, No prescaler*/
	ETIFR = 1<<ICF3;	/* Clear ICP flag (Input Capture flag) */
	ETIFR = 1<<TOV3;	/* Clear Timer Overflow flag */
}

void ICU_Timer3_vdInit_Fallingedge(void)
{
	TCNT3 = 0;	/* Clear Timer counter */
	TCCR3B = 0x01;	/* Capture on falling edge, No prescaler */
	ETIFR = 1<<ICF3;	/* Clear ICP flag (Input Capture flag) */
	ETIFR = 1<<TOV3;	/* Clear Timer Overflow flag */
}

void ICU_Timer3_vdWaitForRisingedge(void)
{
	while ((ETIFR & (1 << ICF3)) == 0);/* Wait for rising edge */
}

void ICU_Timer3_vdWaitForFallingedge(void)
{
	while ((ETIFR & (1 << ICF3)) == 0);/* Wait for falling edge */
}

void ICU_Timer3_vdStop (void)
{
	TCCR3B = 0x00;
}

---------------------------------------------------
void INT0_vdInit (void)
{
	GICR |= 1<<INT0;
	MCUCR |= 1<<ISC00;
	sei();
}
void Timer2_vdInit (void)
{
	TCCR2 |= 1<<CS20;
	TIMSK |= 1<<TOIE2;
	sei();
	
}

void Timer2_vdStop (void)
{
	TCCR2 = 0;
	
}

------------------------------------------------------
