/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 12 September 2020         
/* Descroption: Rx Example				                                          */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "CAN_interface.h"

/* 
	A counter that keeps track of the number of times the RX interrupt has
	occurred, which should match the number of RX messages that were sent.
*/
volatile u32 Global_ui32MsgCount = 0;

void CAN_IntRxHandler(void);
int main(void)
{
	/*	  peripheral clock must be enabled using the RCGC0 register 	*/
	/*	  the clock to the appropriate GPIO module must be enabled via the RCGC2	*/
	/*	  Set the GPIO AFSEL bits for the appropriate pins	*/
	/*	  Set the GPIO AFSEL bits for the appropriate pins	*/
	/*	Make Msg Object	*/
	CAN_MassegeObject CAN_Msg ; 
	u8 *MsgData ; 
	u32 u32MsgData ; 
	MsgData = (u8 *)&u32MsgData;
	u8 Error = 1 ; 
	/* Initialize the message object that will be used for sending CAN	*/
	/*	In order to receive any CAN ID, the ID and mask must both
		be set to 0, and the ID filter enabled.	*/
	CAN_Msg.copy_u32MsgID							=	0  ;
	CAN_Msg.copy_u32MsgIDMask						=	0   ;
	CAN_Msg.copy_u8ExtendedFrameFlag				=	0   ;
	CAN_Msg.copy_u8FilterExtendedIdentifierFlag		=	0   ;
	CAN_Msg.copy_u8FilterMsgDirectionFlag			=	0   ;
	CAN_Msg.copy_u32MsgLength						=	8;
	CAN_Msg.pointer_MsgData							=	MsgData ;
	/*	Bit Timing Parameters For Bit Rate = 1000 */
	BitTiming_Parameter CAN_TimingParmeters ; 
	CAN_TimingParmeters.BaudRatePrescaler_BRP	= 1 ; 
	CAN_TimingParmeters.TimeSegmentBeforeSamplePoint_TSEG1	=		13 ; 
	CAN_TimingParmeters.TimeSegmentAfterSamplePoint_TSEG2	=		2 ;
	CAN_TimingParmeters.SynchronizationJumpWidth_SJW		=	1	;
	/*	  Init CAN Module	*/
	CAN_voidInit(CAN0,NormalMode,&CAN_TimingParmeters);
	/*	Enable Statues And Error Interrupt	*/
	CAN_voidInterruptEnable(CAN0,All_Interrupts);
	/* Enable the CAN interrupt on the processor (NVIC).	*/

	
	while(1)
	{
		/*	CAN will receive any message on the bus, and an interrupt will occur.
			Use message object 1 for receiving messages (this is not the same as
			the CAN ID which can be any value in this example it will not effect in object number).	*/
		Error = CAN_u8RecieveMessageObjectAsync(CAN0,1,&CAN_Msg,Enable_FIFO,CAN_IntRxHandler);
		if(Error != 1)
		{
			Error = CAN_u8RecieveMessageObjectAsync(CAN0,1,&CAN_Msg,Enable_FIFO,CAN_IntRxHandler);
		}
		else
		{
			/*	Get Next Byte To Transmit	*/
		    u32MsgData++;
		}

	}
	//return 0; 
}
void CAN_IntRxHandler(void)
{
	Global_ui32MsgCount++ ;

}
