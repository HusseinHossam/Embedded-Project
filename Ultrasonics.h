#include"Timer_init.h"
#define ICU_Timer1_Ultrasonic_Triggerpin	   PA0	   /*         Trigger pin           */
#define Correction_Factor 466.47               /* The speed of sound * Clk Freq */
#define Ultrasonic_DDR         DDRA
#define Ultrasonic_PTR         PORTA
#define Timer2_Ultrasonic_Triggerpin 		   PA1
#define ICU_Timer3_Ultrasonic_Triggerpin	   PA2

typedef enum  
{
	Right  = 1, 
	Corner = 2,
	Back_Timer_1   = 3,
	Front_Timer_1  = 4,
	Front_Timer_2 = 5 
}   Ultra_Sonics;
	Ultra_Sonics Operating_US; 
	Ultra_Sonics Checking_US;

void ICU_Timer1_Ultrasonic_vdInit (void); // make DDR output 
void ICU_Timer1_Ultrasonic_vdTriggerPulse(void) // send Trigger pulse 

void Timer2_Ultrasonic_vdInit (void);
void Timer2_Ultrasonic_vdTriggerpulse (void);

void ICU_Timer3_Ultrasonic_vdInit (void); 
void ICU_Timer3_Ultrasonic_vdTriggerPulse(void)

void Ultra_vdInit( Ultra_Sonics name);

float_32 ICU_Timer1_f32Ultrasonic_vdDisplay(void);
float_32 Timer2_f32Ultrasonic_f32Display(void);
float_32 ICU_Timer3_f32Ultrasonic_vdDisplay (void);
