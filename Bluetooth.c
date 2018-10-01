/*
 * USSARTTT.c
 *
 * Created: 8/15/2018 7:44:53 PM
 * Author : abdallah muhammed
 */ 

#include "USART.h"
#define  Baud_rate 9600
int main(void)
{
	USART_vdInit(Baud_rate); 
	SET_BIT (DDRB,0); 
	
    while (1) 
    {
		uint_8 Data_IN = USART_u8Recieve();
		
		if ( Data_IN == '1' )
		{
			SET_BIT(PORTB,0);
			USART_vdSendString("Edelo");
		}
		if(Data_IN == '2')
		{
			CLEAR_BIT(PORTB,0);
			USART_vdSendString("Edraab");
		}
		
	}
}
	
