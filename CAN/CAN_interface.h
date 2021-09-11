/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 29 August 2020                                                    */
/*********************************************************************************/

#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

typedef enum{
	CAN0 = 0,
	CAN1
}CAN_channel ;

typedef enum{
	NormalMode,
	LoopbackMode,
	SilentMode,
	LoopbackWithSilentMode
}CAN_Mode ;

typedef struct 
{
	u8 BaudRatePrescaler_BRP ; 
	u8 TimeSegmentBeforeSamplePoint_TSEG1 ; 
	u8 TimeSegmentAfterSamplePoint_TSEG2 ; 
	u8 SynchronizationJumpWidth_SJW ; 
}BitTiming_Parameter ; 
typedef enum
{
	/*	 status interrupt has the highest priority	*/
	Status_Interrupt = 0,
	Error_Interrupt,
	All_Interrupts
}Interrupt_Type ;

typedef enum
{
	Enable_FIFO,
	Disable_FIFO
}FIFO_Mode ;

typedef struct 
{
	// The CAN message identifier used for 11 or 29 bit identifiers.
	u32 copy_u32MsgID ;
	// The message identifier mask used when identifier filtering is enabled. 
	u32 copy_u32MsgIDMask ; 
	// This value holds 1 for Extended Frame and 0 for standard frame.
	u8 copy_u8ExtendedFrameFlag ;
	// filter on the extended ID bit : This value holds 1 for Filter Extended Frame and 0 no effect on the acceptance filtering 
	u8 copy_u8FilterExtendedIdentifierFlag ;
	//0 no effect of acceptance filtering on Msg direction, 1 acceptance filtering effected on Msg direction
	u8 copy_u8FilterMsgDirectionFlag ;
	// This value is the number of bytes of data in the message object.
	u32 copy_u32MsgLength ; 
	// This is a pointer to the message object's data.
	u8 *pointer_MsgData ; 
}CAN_MassegeObject ; 

		/*			PUBLIC FUNCTIONS  					*/	
void CAN_voidInit(CAN_channel channelNumber,CAN_Mode WorkingMode,BitTiming_Parameter *BitRateParameter);
void CAN_voidInterruptEnable(CAN_channel channelNumber , Interrupt_Type copy_IntType) ; 
void CAN_voidInterruptDisable(CAN_channel channelNumber , Interrupt_Type copy_IntType) ; 
u8 CAN_u8TransmitMessageObjectSync(CAN_channel channelNumber,u32 copy_u32ObjID , CAN_MassegeObject *psMsgObject , FIFO_Mode copy_FIFOStatues);
u8 CAN_u8TransmitMessageObjectAsync(CAN_channel channelNumber,u32 copy_u32ObjID , CAN_MassegeObject *psMsgObject , FIFO_Mode copy_FIFOStatues,void(*callBack)(void));
u8 CAN_u8RecieveMessageObjectAsync(CAN_channel channelNumber,u32 copy_u32ObjID , CAN_MassegeObject *psMsgObject , FIFO_Mode copy_FIFOStatues,void(*callBack)(void));
u8 CAN_u8RecieveMessageObjectSync(CAN_channel channelNumber,u32 copy_u32ObjID , CAN_MassegeObject *psMsgObject , FIFO_Mode copy_FIFOStatues);
#endif
