#ifndef USART_H_ 
#define USART_H_ 


#include "DIO.h"
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
void USART_vdInit(uint_16 Baud_rate);
void USART_vdTransmit (uint_8 data);
uint_8 USART_u8Recieve();
void USART_vdSendString(uint_8* Str);

#endif
