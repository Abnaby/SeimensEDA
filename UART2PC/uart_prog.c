/**********************************************************************/
/* Author	:	Mohamed Abd El-Naby									  */
/* Date		:	15 Aug 2021											*/
/* Version	:	V01													*/
/********************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "uart_interface.h"
#include "uart_private.h"
#include "uart_config.h"

#define WAIT_TO_TRANSMIT   (GET_BIT(UART0FR,5) == 0)
#define WAIT_TO_RECEIVE    (GET_BIT(UART0FR,4) == 0)
static void (*Callback_RX_UART0) (u8) = NULL ;
static void (*Callback_TX_UART0) (void) = NULL ;
static volatile u8 Global_u8Data ; 




void UART_voidInit(UART_CHANNEL channel,u16 copy_u16BaudRate,UART_PARITY Parity,UART_STOPBIT stopBitType,UART_FIFO FIFO_mode, u8 copy_u8FrameLength)
{
	float global_floatBaudDivisor  ;
	u16 global_u16IntBaudDivisor  ;
	if(channel == UART1)
	{
		// Enable the UART module 
		SET_BIT(UARTx_RCGCUART, UART1) ;
		// Enable the clock to the appropriate GPIO 
			//	FOR UART1 PA0 RX , PA1 TX
		SET_BIT(UARTx_RCGCGPIO,PORTA);
		/* UART0 TX0 and RX0 use PA0 and PA1. Set them up. */
		// Make PA0 and PA1 as digital 
		SET_BIT(GPIOADEN,0); 
		SET_BIT(GPIOADEN,1);  
		// Use PA0,PA1 alternate function
		SET_BIT(GPIOAFSEL,0);
		SET_BIT(GPIOAFSEL,1);
		// configure PA0 and PA1 for UART 
		SET_BIT(GPIOPCTL,0);
		SET_BIT(GPIOPCTL,4);
		/* Baud Rate Configuration. */
		global_floatBaudDivisor = ((F_CPU*1.0)/(copy_u16BaudRate*1.0))*16.0 ;
		global_u16IntBaudDivisor = (u16)global_floatBaudDivisor ;
		UART0IBRD = global_u16IntBaudDivisor ; 
		global_u16IntBaudDivisor =((global_floatBaudDivisor-global_u16IntBaudDivisor)*64)+0.5;
		UART0FBRD = global_u16IntBaudDivisor ; 
		/*	ENABLE UART0,TX and RX0	*/
		SET_BIT(UART0CTL,0); //Enable Clear To Send
		SET_BIT(UART0CTL,8);
		SET_BIT(UART0CTL,9);
		/*	Parity	*/
		switch(Parity)
		{
			case EVEN_PARITY : 
				SET_BIT(UART0LCRH,1);
				SET_BIT(UART0LCRH,2);
			break ;
			case ODD_PARITY: 
				SET_BIT(UART0LCRH,1);
				CLR_BIT(UART0LCRH,2);
			break ;
			case DISABLE_PARITY: 
				CLR_BIT(UART0LCRH,1);
			break ;
			default:
			break;
		}
		/*	STOP BIT	*/
		switch(stopBitType) 
		{
			case ONE_STOP_BIT : 
			CLR_BIT(UART0LCRH,3);	
			break ;
			case TWO_STOP_BIT : 
			SET_BIT(UART0LCRH,3);
			break ;
			default:
			break;
		}
		/*	FIFO_mode	*/
		switch(FIFO_mode)
		{
			case ENABLE_FIFO : SET_BIT(UART0LCRH,4); break;
			case DISABLE_FIFO: CLR_BIT(UART0LCRH,4);break;
			default:
			break;
		}
		/*	Frame Length	*/
		switch(copy_u8FrameLength)
		{
			case FRAME_LENGTH_5_BIT : 
				CLR_BIT(UART0LCRH,5);
				CLR_BIT(UART0LCRH,6);
			break ; 
			case FRAME_LENGTH_6_BIT :
				SET_BIT(UART0LCRH,5);
				CLR_BIT(UART0LCRH,6);
			break ; 
			case FRAME_LENGTH_7_BIT :
				CLR_BIT(UART0LCRH,5);
				SET_BIT(UART0LCRH,6);
			break ; 
			case FRAME_LENGTH_8_BIT :
				SET_BIT(UART0LCRH,5);
				SET_BIT(UART0LCRH,6);
			break ; 
			default:
			break;

		}
		 
	}
	else if (channel == UART2)
	{
		
	}
	else if (channel == UART3){}
	else if (channel == UART4){}
	else if (channel == UART5){}
	else if (channel == UART6){}
	else if (channel == UART7){}
	else
	{
		//<!TODO ERROR> Wrong Channel Selection
	}
	
	
	
	
	
	
}
void UART_voidControl(UART_CHANNEL channel,u8 copy_u8State)
{
	switch (channel)
	{
		case UART1 : 
			switch(copy_u8State)
			{
				case ENABLE : SET_BIT(UART0CTL,0); break ;
				case DISABLE :CLR_BIT(UART0CTL,0); break ;
				default : break ;
			}
		break ;
		case UART2 : break ;
		case UART3 : break ;
		case UART4 : break ;
		case UART5 : break ;
		case UART6 : break ;
		case UART7 : break ;
		default	: break; 
	}
}

u8 UARTx_charReceiverSynch(UART_CHANNEL channel)
{
	u8 data = 0;
	switch (channel)
	{
		case UART1 : 
			/* wait until Rx buffer is not empty	 */
			while(WAIT_TO_RECEIVE);
			data = UART0DR ;
			data = 	data & 0xFF;
		break ;
		case UART2 : break ;
		case UART3 : break ;
		case UART4 : break ;
		case UART5 : break ;
		case UART6 : break ;
		case UART7 : break ;
	}

	return data ; 
}
void UARTx_charReceiverAsynch(UART_CHANNEL channel,void(*callBack)(u8))
{
	
	// Store the call back function address.
	Callback_RX_UART0 = callBack    ; 
	// Enable receiver interrupt.
	SET_BIT(UART0IM,4); 
}

void UARTx_voidTransmitterSynch(UART_CHANNEL channel,char TransmittedData)
{
	/* wait until Rx buffer is not full	 */
	while(WAIT_TO_TRANSMIT);
	UART0DR = TransmittedData ; 
}
void UARTx_voidTransmitterAsynch(UART_CHANNEL channel,char TransmittedData,void(*callBack)(void))
{
	// Store the call back function address.
	Callback_TX_UART0 = callBack ; 
	// Enable receiver interrupt.
	SET_BIT(UART0IM,5); 
	Global_u8Data = TransmittedData ;
}

void __vector_5(void)
{	
	//know whats making interrupt 
	if((GET_BIT(UART0RIS,4))) // INTRRUPT FROM RECIVING 
	{
		//Writing a 1 to this bit clears the RXRIS bit in the UARTRIS register 
		SET_BIT(UART0ICR,4);
		Callback_RX_UART0((0xFF)& UART0DR);
		
	}
	else if((GET_BIT(UART0RIS,5)))// INTRRUPT FROM TRANSIMTTED 
	{
		//Writing a 1 to this bit clears the RXRIS bit in the UARTRIS register 
		SET_BIT(UART0ICR,5);
		UART0DR = Global_u8Data ; 
		Callback_TX_UART0();
		
	}
	
	

	
	
	
}
