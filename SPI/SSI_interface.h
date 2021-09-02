/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 2 September 2020                                                   */
/*********************************************************************************/

#ifndef SSI_INTERFACE_H
#define SSI_INTERFACE_H
	
	
typedef enum{
	SSI0 = 0,
	SSI1,
	SSI2,
	SSI3
}SSI_Channel ;

typedef enum{
	Slave=0,
	Master,
}SSI_Mode ;
typedef enum{
	SysCLK=0,
	PIOSC
}SSI_CLK_Mode ;
typedef enum
{
	SPI=0,
	TI_SSF,
	MICROWIRE
}SSI_Protocol_Mode;
typedef enum
{
	ENABLE,
	DISABLE
}Interrupt_State ;
typedef enum
{
	Receive_Overrun_Interrupt =0 ,
	Receive_TimeOut_Interrupt,
	Receive_FIFO_Interrupt,
	Transmit_FIFO_Interrupt,
	All_Interrupts
}Interrupt_Type;	

		/*			PUBLIC FUNCTIONS  					*/	
void SSI_voidInit(SSI_Channel copy_SSIChennal,SSI_Mode copy_workingMode,SSI_CLK_Mode copy_CLKSelection,u8 copy_u8BaudRate,SSI_Protocol_Mode copy_protocolMode,u8 copy_u8DataSize);
		
void SSI_voidChangeBuadRate(SSI_Channel copy_SSIChennal,u8 copy_u8BaudRate);
void SSI_voidChangeDataSize(SSI_Channel copy_SSIChennal,u8 copy_u8DataSize);
void SSI_voidChangeProtocol(SSI_Channel copy_SSIChennal,SSI_Protocol_Mode copy_protocolMode);
void SSI_voidChangeSSIMode(SSI_Channel copy_SSIChennal,SSI_Mode copy_workingMode);
void SSI_voidDisable(SSI_Channel copy_SSIChennal);
void SSI_voidEnable(SSI_Channel copy_SSIChennal);
void SSI_voidEnableInt(SSI_Channel copy_SSIChennal ,Interrupt_Type copy_IntType);
void SSI_voidTransmitSynch(SSI_Channel copy_SSIChennal ,u16 copy_u16DataBeTransmited);
void SSI_voidTransmitAsynch(SSI_Channel copy_SSIChennal ,u16 copy_u16DataBeTransmited,void(*callBack)(u8));
u16 SSI_voidRecieveSynch(SSI_Channel copy_SSIChennal);
void SSI_voidDisableInt(SSI_Channel copy_SSIChennal ,Interrupt_Type copy_IntType);



#endif
