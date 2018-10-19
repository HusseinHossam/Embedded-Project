/*
 * Algorithm Auto parking.c
 *
 * Created: 10/17/2018 5:24:38 PM
 * Author : abdallah muhammed
 */ 

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"
#include "Ultrasonic.h"
#include "Servo.h"
#include "Motors.h"
typedef struct Flags
{
	union
	{
		uint_8 Auto_Parking :1; // BIT FIELD <3 
		uint_8 IsFound:1;
		uint_8 IsReady:1;
		uint_8 IsParked:1;
		};	
}Flag;
typedef enum  
{
	Right  = 1, 
	Corner = 2,
	Back_Timer_1   = 3,
	Front_Timer_1  = 4,
	Front_Timer_2 = 5 
	}Ultra_Sonics;
	Ultra_Sonics Operating_US; 
	Ultra_Sonics Checking_US;	
								/* Operating works on Right and Corner And Back ultrasonic
								 Checking works only for Front to check there is accident in finding space or to align car at final 
																																	*/
	/* - 1 Front Ultrasonic on Timer 1 and Timer 2 [ When Servo OFF on Timer 2.. When Servo Activate On Timer 1 ]
		-2 Right Ultrasonic On Timer 1  [ Never working Front And Right Ultrasonic ] 
		-3 Corner Ultrasonic on Timer 3 
		-4 Motors on Timer 0 
		-5 Servo Motor on Timer 2 
		*/
#define Parllel_Length 10
#define Car_Width 10
#define Constant_Speed 20
#define Actual_Length 20
#define Minimum_Front 5
#define Minimum_Corner 5
#define Minimum_Back 5
#define Freqency_Cpu 16000000
#define Pre_Scaler 1024
void Determine_vdControl (void);
void Manual_vdControl (void);
void Check_vdParllelDistance (void);
void Searching_vdForArea (void);
void Allign_vdCar(void);
void Wifi_vdState(void);
void Getting_vdReady(void);
void RightBackward_vdParking(void);
void LeftBackward_vdParking(void);
void Forward_vdParking(void);
void Check_u8Front(Ultra_Sonics status);

int main(void)
{
    PWM_vdMotorInit();
}


uint_8 Check_u8Front( Ultra_Sonics status)
{
	Ultra_vdInit(status);
	if (Ultra_u8Distance(status) < Minimum_Front)
	{
		PWM_vdCar_Stop();
		Wifi_vdState(); // n2es w2ef fen [ mmumken el flag ] 
	}
}
void Determine_vdControl (void)
{
	if (Flag.Auto_Parking == 0)
	{
		Manual_vdControl();
	}
	else 
	{
		Check_vdParllelDistance();
	}
	
}
void Manual_vdControl (void)
{
	// Copy Paste 
}

void Check_vdParllelDistance (void)
{	
		Operating_US = Right;
		Checking_US = Front_Timer_2;
		Ultra_vdInit(Operating_US);
		if ( Ultra_u8Distance(Operating_US) > Parllel_Length )
		{
			Check_u8Front(Checking_US);
			Searching_vdForArea();
		}
		else
		{
			Check_u8Front(Checking_US);
			Allign_vdCar();
		}
	
}
void Allign_vdCar()
{
	Checking_US = Front_Timer_1;
	Operating_US = Right;
	Ultra_vdOFF(Operating_US);
	Operating_US = Corner;
	ULtra_vdInit(Operating_US); // bytl3 le odam bycheck eel corner
	Servo_vdInit();
	Servo_vdSetangle(120); // el reference 90 

	do
	{
		PWM_vdCar_Forward(30);
		_delay_ms(1000);
		Check_u8Front(Checking_US);
		
	}
	while( Ultra_u8Distance(Operating_US) < Parllel_Length);
	Servo_vdSetangle (90);
	PWM_vdCar_Forward(30);
	Check_u8Front(Checking_US);
	Searching_vdForArea();
}

void Searching_vdForArea(void)
{
	Checking_US = Front_Timer_2;
	Operating_US = Corner;
	Flag.IsFound=0;
	Servo_vdOFF();
	Ultra_vdOFF(Operating_US); // Timer 3 
	Operating_US = Right;
	Ultra_vdInit(Operating_US); //Timer 1 
	
	Ultra_vdInit(Checking_US); // da ele bytcheck 3ala case eid 
	PWM_vdCar_Forward(30);
while (Flag.IsFound == 0)	
{
	do
	{
			if (Ultra_u8Distance(Checking_US) < Minimum_Front)
			{
				PWM_vdCar_Stop();
				Wifi_vdState(); // nt2ked men return 
			}
			
		_delay_us(10);
	} while(Ultra_u8Distance(Operating_US) < (Car_Width + Parllel_Length));
	
	PWM_vdCar_Stop();
	_delay_us(10);
	Timer_vdInit(2,"Normal",0);
	PWM_vdCar_Forward(30);
	do 
	{
		
		if (Ultra_u8Distance(Checking_US) < Minimum_Front)
		{
			PWM_vdCar_Stop();
			Wifi_vdState();
		}
		
		_delay_us(10);
	} while (Ultra_u8Distance(Operating_US) > (Car_Width + Parllel_Length));
	
	Timer_vdOFF("Timer2");
	_delay_us(10);
	PWM_vdCar_Stop();
	
	if ((Timer2_u32count()*Constant_Speed) > Actual_Length) // 3yza tt7owel le cm 
	{
		Flag.IsFound = 1;
		PWM_vdCar_Stop();
		Getting_vdReady();	
	} 
	
}
}

void Getting_vdReady(void)
{
	Checking_US = Front_Timer_2;
	Operating_US  = Right;
	uint_8 Time = [ (float_32) Actual_Length/(4*Constant_Speed)];
	Ultra_vdOFF(Checking_US);
	Ultra_vdOFF(Operating_US);
	Timer_vdInit(1,"Compare",((Time*Freqency_Cpu)/Pre_Scaler));
	PWM_vdCar_Forward(30);
	while (Flag.IsReady == IsMatched) Check_u8Front(Checking_US);
	Timer_vdOFF("Timer1"); // da le timer 1 w timer 2 bs 
	PWM_vdCar_Stop();
	RightBackward_vdParking();
}
void RightBackward_vdParking(void)
{
	Checking_US = Front_Timer_2;
	Operating_US = Corner;
	Ultra_vdOFF(Checking_US);
	Ultra_vdInit(Operating_US);
	Servo_vdInit();
	Servo_vdSetangle (135); // Right w nt2ked ama eid ygrb el servo 
	PWM_vdCar_Reverse(15); // hessen by2ol fel rakna abt2 
	while (Ultra_u8Distance(Operating_US) > Minimum_Corner);
	PWM_vdCar_Stop();
	LeftBackward_vdParking();
} 
void LeftBackward_vdParking(void)
{
	Operating_US = Corner;
	Ultra_vdOFF(Operating_US);
	Operating_US = Back_Timer_1;
	Ultra_vdInit(Operating_US);
	Servo_vdSetangle (45); // eid brdo hyt2ked 
	PWM_vdCar_Reverse(15);
	while (Ultra_u8Distance(Operating_US) > Minimum_Back);
	PWM_vdCar_Stop();
	Forward_vdParking();
}
void Forward_vdParking(void);
{
	Operating_US = Back_Timer_1;
	Checking_US = Front_Timer_2;
	Flag.IsFound = 0;
	Ultra_vdOFF(Operating_US);
	Servo_vdSetangle (90);
	_delay_ms(10);
	Servo_vdOFF;
	Ultra_vdInit(Checking_US);
	_delay_ms(10);
	PWM_vdCar_Forward(10);
	while (Ultra_u8Distance(Checking_US) > Minimum_Front);
	PWM_vdCar_Stop();
	Flag.IsParked = 1;
	Wifi_vdState();
}

void Wifi_vdState();
{
	if (Flag.IsParked == 1)
	{
		Wifi_vdSendString ("Parked");
	}
	else if (Flag.IsFound == 0)
	{
		Wifi_vdSendString ("No Space");
	}
}
