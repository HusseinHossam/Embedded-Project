#include "USART.h"

//***********************************************************

void USART_vdInit(uint_16 Baud_rate)
{
	uint_8 USART_UBBR_VALUE = (F_CPU/(16*Baud_rate))-1;
	UBRRH = (uint_8) USART_UBBR_VALUE <<8 ;
	UBRRL = (uint_8) USART_UBBR_VALUE;
	SET_BIT(UCSRC,URSEL) | SET_BIT (UCSRC,UCSZ0) | SET_BIT(UCSRC,UCSZ1); 
	SET_BIT(UCSRB,TXEN) | SET_BIT(UCSRB,RXEN);
	
}

//***********************************************************

void USART_vdTransmit (uint_8 data)
{
 
	while ( BIT_IS_CLEAR(UCSRA,UDRE) );
	UDR  = data;
}
//**********************************************************
uint_8 USART_u8Recieve()
{
	while ( BIT_IS_CLEAR(UCSRA,RXC) );
	return UDR;
}



//***********************************************************
void USART_vdSendString(uint_8* Str)
{
	while (*Str != 0)
	{
		USART_vdTransmit(*Str);
		Str++;
	}
}

//***********************************************************


