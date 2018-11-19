#include "Ultrasonics.h"
uint_8 Timer1Overflow = 0;
uint_8 Timer2_Overflow = 0;
uint_8 Timer3Overflow = 0
uint_32 Timer2_Counts = 0; // in ISR and Function 
--------------------------------------------------------------------------------
void ICU_Timer1_Ultrasonic_vdInit (void)
{
	Ultrasonic_DDR |= ( 1 << ICU_Timer1_Ultrasonic_Triggerpin );
}
void ICU_Timer1_Ultrasonic_vdTriggerPulse(void)
{
	Ultrasonic_PTR |= (1 << ICU_Timer1_Ultrasonic_Triggerpin);
	_delay_us(35);
	Ultrasonic_PTR &= (~(1 << ICU_Timer1_Ultrasonic_Triggerpin));	
}
-------------------------------------------------------------------------
void Timer2_Ultrasonic_vdInit (void)
{
	Ultrasonic_DDR |= ( 1 << Timer2_Ultrasonic_Triggerpin );
}

void Timer2_Ultrasonic_vdTriggerpulse(void)
{
	Ultrasonic_PTR |= ( 1 << Timer2_Ultrasonic_Triggerpin );
	_delay_ms(35);
	Ultrasonic_PTR &=~ ( 1 << Timer2_Ultrasonic_Triggerpin );
}
---------------------------------------------------------------------------
void ICU_Timer3_Ultrasonic_vdInit (void)
{
	Ultrasonic_DDR |= ( 1 << ICU_Timer3_Ultrasonic_Triggerpin );
}
void ICU_Timer1_Ultrasonic_vdTriggerPulse(void)
{
	Ultrasonic_PTR |= (1 << ICU_Timer3_Ultrasonic_Triggerpin);
	_delay_us(35);
	Ultrasonic_PTR &= (~(1 << ICU_Timer3_Ultrasonic_Triggerpin));	
}
---------------------------------------------------------------------------
void Ultra_vdInit( Ultra_Sonics name)
{
	switch (name)
	case 1 :  { 
				ICU_Timer1_vdInit ();
				ICU_Timer1_Ultrasonic_vdInit();
			  }
	break;
	case 2 :  { 
				ICU_Timer3_vdInit ();
				ICU_Timer3_Ultrasonic_vdInit();
			  }
	break;
	case 3 :  {
				ICU_Timer1_vdInit ();
				ICU_Timer1_Ultrasonic_vdInit();
			  }
	break;
	case 4 :  {
				ICU_Timer1_vdInit ();
				ICU_Timer1_Ultrasonic_vdInit();
			  }
	break;
	case 5 :  {
				Timer2_Ultrasonic_vdInit();
				INT0_vdInit ();
			  }
	break;
				
}
--------------------------------------------------
// Calculating distance 
float_32 ICU_Timer1_f32Ultrasonic_vdDisplay(void)
{
	float_32 Distance = 0;
	char ICU_Ultrasonic_Distance[10];
	uint_32 ICU_Counts = 0;
	
	/* Give 10us trigger pulse on trig. pin to HC-SR04 */
	
	ICU_Timer1_Ultrasonic_vdTriggerPulse();
	
	ICU_Timer1_vdInit_Risingedge();
	
	/*Calculate width of Echo by Input Capture (ICP) */
	
	ICU_Timer1_vdWaitForRisingedge();
	ICU_Timer1_vdInit_Fallingedge();
	Timer1Overflow = 0;/* Clear Timer overflow count because useless overflow happened*/
	ICU_Timer1_vdWaitForFallingedge();
	ICU_Counts = ICR1 + (65535 * Timer1Overflow);	/* Take count */
	
	/*Calculate the distance with the ICU counts */
	
	Distance = ICU_Counts / Correction_Factor;
	dtostrf(Distance, 2, 2, ICU_Ultrasonic_Distance);/* distance to string */
	LCD_vdDisplay(1, 1, ICU_Ultrasonic_Distance);
	return Distance ; 
}

ISR(TIMER1_OVF_vect)
{
	Timer1Overflow++;	/* Increment Timer Overflow count */
}
----------------------------------------------------------------
float_32 Timer2_f32Ultrasonic_f32Display(void)
{
	float_32 Timer2_Distance = 0;
	char Timer2_Distance_Str[16];
	Timer2_Ultrasonic_vdTriggerpulse();
	Timer2_Distance = Timer2_Counts/466.47;
	dtostrf(Timer2_Distance,2,2,Timer2_Distance_Str);
	LCD_vdDisplay(2,1,Timer2_Distance_Str);
	return Timer2_Distance;
}
ISR(INT0_vect)
{
	static uint_8 i = 0;
	if(i == 1)
	{
		Timer2_vdStop ();
		Timer2_Counts = TCNT2 + (Timer2_Overflow * 256);
		TCNT1 = 0;
		i = 0;
	}

	if(i==0)
	{
		Timer2_vdInit ();
		i = 1;
	}
}
ISR(TIMER2_OVF_vect)
{
	Timer2_Overflow++;	/* Increment Timer Overflow count */
}
----------------------------------------------------------------
float_32 ICU_Timer3_f32Ultrasonic_vdDisplay (void)
{
	float_32 Distance = 0;
	char ICU_Ultrasonic_Distance[10];
	uint_32 ICU_Counts = 0;
	
	/* Give 10us trigger pulse on trig. pin to HC-SR04 */
	
	ICU_Timer3_Ultrasonic_vdTriggerPulse();
	
	ICU_Timer3_vdInit_Risingedge();
	
	/*Calculate width of Echo by Input Capture (ICP) */
	
	ICU_Timer3_vdWaitForRisingedge();
	ICU_Timer3_vdInit_Fallingedge();
	Timer3Overflow = 0;/* Clear Timer overflow count because useless overflow happened*/
	ICU_Timer3_vdWaitForFallingedge();
	ICU_Counts = ICR3 + (65535 * Timer3Overflow);	/* Take count */
	
	/*Calculate the distance with the ICU counts */
	
	Distance = ICU_Counts / Correction_Factor;
	dtostrf(Distance, 2, 2, ICU_Ultrasonic_Distance);/* distance to string */
	LCD_vdDisplay(1, 1, ICU_Ultrasonic_Distance);
	return Distance ; 
}

ISR(TIMER3_OVF_vect)
{
	Timer3Overflow++;	/* Increment Timer Overflow count */
}
-----------------------------------------------------------------
float_32 Ultra_f32Distance ( Ultra_Sonics name )
{
	switch ( name )
{
	case 1 : {  float_32 Distance = 0;
				Distance = ICU_Timer1_f32Ultrasonic_vdDisplay();
				return Distance; 
			 }
	break;
	case 2 : { 
				float_32 Distance = 0;
				Distance = ICU_Timer3_f32Ultrasonic_vdDisplay();
				return Distance;
			 }
	break; 
	
	case 3 : {  float_32 Distance = 0;
				Distance = ICU_Timer1_f32Ultrasonic_vdDisplay();
				return Distance;
			 }
	break; 
	case 4 : { 	float_32 Distance = 0;
				Distance = ICU_Timer1_f32Ultrasonic_vdDisplay();
				return Distance;
			 }
	break;
	case 5 : { 	float_32 Distance = 0;
				Distance = Timer2_Ultrasonic_f32Display();
				return Distance;
			 }
	break; 
}			
}
------------------------------------------------------------------
void Ultra_vdOFF ( Ultra_Sonics name )
{
	switch (name)
	{
		case 1 : { 
					ICU_Timer1_vdStop();
				 }
		break;
		case 2 : {
					ICU_Timer3_vdStop();
				 }
		break;
		case 3 : {
					ICU_Timer1_vdStop();
				 }
		break;
		case 4 : {
					ICU_Timer1_vdStop();
				 }
		break;
		case 5 : {
					Timer2_vdStop();
				 }
		break;
	}
}
		
