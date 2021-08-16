/**********************************************************************/
/* Author	:	Mohamed Abd El-Naby									  */
/* Date		:	15 Aug 2021											*/
/* Version	:	V01													*/
/********************************************************************/
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_
#define FRAME_LENGTH_5_BIT	0
#define FRAME_LENGTH_6_BIT	2
#define FRAME_LENGTH_7_BIT	4
#define FRAME_LENGTH_8_BIT	6


typedef enum {
	ENABLE_INTRUPRTS,
	DISAPLE_INTRUPRTS
}UART_INTERRUPT;

typedef enum{
	UART1 = 0,
	UART2,
	UART3,
	UART4,
	UART5,
	UART6,
	UART7
}UART_CHANNEL;

typedef enum 
{
	EVEN_PARITY,
	ODD_PARITY ,
	DISABLE_PARITY
}UART_PARITY ;
typedef enum
{
	ONE_STOP_BIT,
	TWO_STOP_BIT
}UART_STOPBIT;
typedef enum
{
	ENABLE_FIFO,
	DISABLE_FIFO
}UART_FIFO;

#define DISABLE 0
#define ENABLE 1


void UART_voidInit(UART_CHANNEL channel,u16 copy_u16BaudRate,UART_PARITY Parity,UART_STOPBIT stopBitType,UART_FIFO FIFO_mode, u8 copy_u8FrameLength);
void UART_voidControl(UART_CHANNEL channel,u8 copy_u8State);
u8 UARTx_charReceiverSynch(UART_CHANNEL channel);
//
void UARTx_charReceiverAsynch(UART_CHANNEL channel,void(*callBack)(u8));
void UARTx_voidTransmitterSynch(UART_CHANNEL channel,char TransmittedData);
void UARTx_voidTransmitterAsynch(UART_CHANNEL channel,char TransmittedData,void(*callBack)(void));

#endif