#include "USART.h"

//***********************************************************

void USART_vdInit(uint_32 Baud_rate)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);					/* Enable USART transmitter and receiver */
	UCSRC |= (1 << URSEL)| (1 << UCSZ0) | (1 << UCSZ1);	/* Write USCRC for 8 bit data and 1 stop bit */
	uint_8 USART_UBBR_VALUE = (F_CPU/(16*Baud_rate))-1;
	UBRRH = (uint_8)  USART_UBBR_VALUE >> 8 ;
	UBRRL = (uint_8)  USART_UBBR_VALUE;
	
	
}

//***********************************************************

void USART_vdTransmit (uint_8 data)
{
	while (!(UCSRA & (1<<UDRE)));					/* Wait until data transmit and buffer get empty */
	UDR = data;
}
//**********************************************************
uint_8 USART_u8Recieve()
{	
	while (!(UCSRA & (1 << RXC)));					/* Wait until new data receive */
	return(UDR);
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


