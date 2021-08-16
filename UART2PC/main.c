/*
 * GccApplication2.cpp
 *
 * Created: 8/16/2021 2:28:52 PM
 * Author : Abnaby
 */ 
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "uart_interface.h"
#include "NVIC_interface.h"
void whenRecieve(u8);

int main(void)
{

	/* I can't Extract UART IRQ in NVIC */
	NVIC_voidEnableInterrupt(21);
	/*	Initialize UART1 with BuadRate 9600 , one stop bit, NO-FIFO and 8-bit frame length		*/
	UART_voidInit(UART1 , 9600 , 2, TWO_STOP_BIT, DISABLE_FIFO,  8);
	/*	ENABLE UART1	*/
	UART_voidControl(UART1,DISABLE) ;
	UARTx_charReceiverAsynch(UART1,whenRecieve);
	while (1)
	{
		
	}
}
void whenRecieve(u8 data)
{
	if(data >= 'a' && data <= 'z')
	{
		 data = data - ('a' - 'A');
		 UARTx_voidTransmitterSynch(UART1,data);
	}
	else
	{
		
		data = data+1 ;
		UARTx_voidTransmitterSynch(UART1,data);
	}
}



