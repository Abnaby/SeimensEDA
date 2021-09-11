/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 11 September 2020                                                   */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "CAN_interface.h"
#include "CAN_private.h"
#include "CAN_config.h"
static u8 global_u8TX_RX_State ; 
static void (*Callback_TX_CAN0) (void) = NULL ;
static void (*Callback_TX_CAN1) (void) = NULL ;
static void (*Callback_RX_CAN0) (void) = NULL ;
static void (*Callback_RX_CAN1) (void) = NULL ;
#define CONFIG_MODE_ENABLE(CAN_CHENNAL) 					SET_BIT(CAN_CHENNAL , CAN_CTL_INIT)
#define CONFIG_MODE_DISABLE(CAN_CHENNAL)					CLR_BIT(CAN_CHENNAL , CAN_CTL_INIT)
#define ENABLE_GLOBAL_INT(CAN_CHENNAL_CTL_REG)				SET_BIT(CAN_CHENNAL_CTL_REG,CAN_CTL_IE) 
#define DISABLE_GLOBAL_INT(CAN_CHENNAL_CTL_REG)				CLR_BIT(CAN_CHENNAL_CTL_REG,CAN_CTL_IE)

void CAN_voidInit(CAN_channel channelNumber,CAN_Mode WorkingMode,BitTiming_Parameter *BitRateParameter)
{
    switch(channelNumber)
    {
    case CAN0 :
		/* Enter Configuration Mode	*/	
		CONFIG_MODE_ENABLE(CAN0_Chennal -> CANCTL);
		/*	Makesure Bus Now is unbusy no message to/from bus 	*/
		WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;
		/*	Enter  Mode*/
		SET_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_TEST ) ;
		switch(WorkingMode)
		{
			case NormalMode : 
				/*	 Normal Mode Selection As Basic Mode 	*/
				CLR_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_TEST ) ;
				SET_BIT(CAN0_Chennal -> CANTST , CAN_TST_BASIC) ;

				break ;
			case LoopbackMode : 
				/*	LoopbackMode Enable	*/
				SET_BIT(CAN0_Chennal -> CANTST , CAN_TST_LBACK ) ;
				break ;
			case SilentMode : 
				/*	in silent mode, the CAN controller does not transmit data but instead monitors the bus	*/
				/*	SilentMode Enable	*/
				SET_BIT( CAN0_Chennal -> CANTST , CAN_TST_SILENT);
				break ;
			case LoopbackWithSilentMode : 
				/*	LoopbackMode Enable	*/
				SET_BIT(CAN0_Chennal -> CANTST , CAN_TST_LBACK ) ;
				/*	SilentMode Enable	*/
				SET_BIT( CAN0_Chennal -> CANTST , CAN_TST_SILENT);
			break ;
		}
		/*	Setting the CCE bit to edit CANBIT Register	*/
		SET_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_CCE) ; 
		/*		SET BIT PARAMETERS		*/
		if(TSEG2_RANGE_CHECK((BitRateParameter -> TimeSegmentAfterSamplePoint_TSEG2 )))
		{CAN0_Chennal-> CANBIT = ((BitRateParameter -> TimeSegmentAfterSamplePoint_TSEG2 ) << CAN_BIT_TSEG2_M );}
		else { /* <!TODO ERRO> Out of Range */  }
		if(TSEG1_RANGE_CHECK((BitRateParameter -> TimeSegmentBeforeSamplePoint_TSEG1)))
		{CAN0_Chennal-> CANBIT = ((BitRateParameter -> TimeSegmentBeforeSamplePoint_TSEG1 ) << CAN_BIT_TSEG1_M);}
        else { /* <!TODO ERRO> Out of Range */  }
		if(SJW_RANGE_CHECK(BitRateParameter -> SynchronizationJumpWidth_SJW))
		{CAN0_Chennal-> CANBIT = ((BitRateParameter -> SynchronizationJumpWidth_SJW ) << CAN_BIT_SJW_M );}
        else { /* <!TODO ERRO> Out of Range */  }
		if(BRP_RANGE_CHECK(BitRateParameter -> BaudRatePrescaler_BRP))
		{CAN0_Chennal-> CANBIT = ((BitRateParameter -> BaudRatePrescaler_BRP ) << CAN_BIT_BRP_M ) ;}
        else { /* <!TODO ERRO> Out of Range */  }
		/*	Disable All Interrupts	*/
		CLR_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_IE ) ;
		CLR_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_SIE ) ;
		CLR_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_EIE ) ;
		/* Exit Configuration Mode	*/
		CONFIG_MODE_DISABLE(CAN0_Chennal -> CANCTL) ;
		break ;
    case CAN1 : 
		/* Enter Configuration Mode	*/	
        CONFIG_MODE_ENABLE(CAN1_Chennal -> CANCTL);
		/*	Makesure Bus Now is unbusy no message to/from bus 	*/
		WAIT_BUS_BE_UNBUSY(CAN1_Chennal -> CANIF1CRQ)	;
        /*  Enter TEST Mode*/
        SET_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_TEST ) ;
        switch(WorkingMode)
        {
            case NormalMode :
                /*   Normal Mode Selection As Basic Mode    */
                CLR_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_TEST ) ;
                SET_BIT(CAN1_Chennal -> CANTST , CAN_TST_BASIC) ;

                break ;
            case LoopbackMode :
                /*  LoopbackMode Enable */
                SET_BIT(CAN1_Chennal -> CANTST , CAN_TST_LBACK ) ;
                break ;
            case SilentMode :
                /*  in silent mode, the CAN controller does not transmit data but instead monitors the bus  */
                /*  SilentMode Enable   */
                SET_BIT( CAN1_Chennal -> CANTST , CAN_TST_SILENT);
                break ;
            case LoopbackWithSilentMode :
                /*  LoopbackMode Enable */
                SET_BIT(CAN1_Chennal -> CANTST , CAN_TST_LBACK ) ;
                /*  SilentMode Enable   */
                SET_BIT( CAN1_Chennal -> CANTST , CAN_TST_SILENT);
            break ;
        }
        /*  Setting the CCE bit to edit CANBIT Register */
        SET_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_CCE) ;
        /*      SET BIT PARAMETERS      */
        if(TSEG2_RANGE_CHECK((BitRateParameter -> TimeSegmentAfterSamplePoint_TSEG2 )))
        {CAN1_Chennal-> CANBIT = ((BitRateParameter -> TimeSegmentAfterSamplePoint_TSEG2 ) << CAN_BIT_TSEG2_M );}
        else { /* <!TODO ERRO> Out of Range */  }
        if(TSEG1_RANGE_CHECK((BitRateParameter -> TimeSegmentBeforeSamplePoint_TSEG1)))
        {CAN1_Chennal-> CANBIT = ((BitRateParameter -> TimeSegmentBeforeSamplePoint_TSEG1 ) << CAN_BIT_TSEG1_M);}
        else { /* <!TODO ERRO> Out of Range */  }
        if(SJW_RANGE_CHECK(BitRateParameter -> SynchronizationJumpWidth_SJW))
        {CAN1_Chennal-> CANBIT = ((BitRateParameter -> SynchronizationJumpWidth_SJW ) << CAN_BIT_SJW_M );}
        else { /* <!TODO ERRO> Out of Range */  }
        if(BRP_RANGE_CHECK(BitRateParameter -> BaudRatePrescaler_BRP))
        {CAN1_Chennal-> CANBIT = ((BitRateParameter -> BaudRatePrescaler_BRP ) << CAN_BIT_BRP_M ) ;}
        else { /* <!TODO ERRO> Out of Range */  }
        /*  Disable All Interrupts  */
        CLR_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_IE ) ;
        CLR_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_SIE ) ;
        CLR_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_EIE ) ;
        /* Exit Configuration Mode  */
        CONFIG_MODE_DISABLE(CAN1_Chennal -> CANCTL) ;
		break ;
    }
}
void CAN_voidInterruptEnable(CAN_channel channelNumber , Interrupt_Type copy_IntType)
{
	switch(channelNumber)
	{
		case CAN0 : 
			/* Enter Configuration Mode	*/	
			CONFIG_MODE_ENABLE(CAN0_Chennal -> CANCTL);
			/*	Makesure Bus Now is unbusy no message to/from bus 	*/
			WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;
			/*	Enable Global Interrupt 	*/
			ENABLE_GLOBAL_INT(CAN0_Chennal -> CANCTL);
			switch(copy_IntType)
			{
				case Status_Interrupt : SET_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_SIE); break ; 
				case Error_Interrupt : SET_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_EIE); break ;
				case All_Interrupts : 
					SET_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_SIE);
					SET_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_EIE);
					break ;
			}
			/* Exit Configuration Mode  */
			CONFIG_MODE_DISABLE(CAN0_Chennal -> CANCTL) ;
			break ; 
		case CAN1 : 
			/* Enter Configuration Mode	*/	
			CONFIG_MODE_ENABLE(CAN1_Chennal -> CANCTL);
			/*	Makesure Bus Now is unbusy no message to/from bus 	*/
			WAIT_BUS_BE_UNBUSY(CAN1_Chennal -> CANIF1CRQ)	;
			/*	Enable Global Interrupt 	*/
			ENABLE_GLOBAL_INT(CAN1_Chennal -> CANCTL);
			switch(copy_IntType)
			{
				case Status_Interrupt : SET_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_SIE); break ; 
				case Error_Interrupt : SET_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_EIE); break ;
				case All_Interrupts : 
					SET_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_SIE);
					SET_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_EIE);
					break ;
			}
			/* Exit Configuration Mode  */
			CONFIG_MODE_DISABLE(CAN1_Chennal -> CANCTL) ;
			break ; 
	}
}
void CAN_voidInterruptDisable(CAN_channel channelNumber , Interrupt_Type copy_IntType)
{
	switch(channelNumber)
	{
		case CAN0 : 
			/* Enter Configuration Mode	*/	
			CONFIG_MODE_ENABLE(CAN0_Chennal -> CANCTL);
			/*	Makesure Bus Now is unbusy no message to/from bus 	*/
			WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;
			/*	Disable Global Interrupt 	*/
			
			switch(copy_IntType)
			{
				case Status_Interrupt : CLR_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_SIE); break ; 
				case Error_Interrupt : CLR_BIT(CAN0_Chennal -> CANCTL , CAN_CTL_EIE); break ;
				case All_Interrupts : 
					DISABLE_GLOBAL_INT(CAN0_Chennal -> CANCTL);
					break ;
			}
			/* Exit Configuration Mode  */
			CONFIG_MODE_DISABLE(CAN0_Chennal -> CANCTL) ;
			break ; 
		case CAN1 : 
			/* Enter Configuration Mode	*/	
			CONFIG_MODE_ENABLE(CAN1_Chennal -> CANCTL);
			/*	Makesure Bus Now is unbusy no message to/from bus 	*/
			WAIT_BUS_BE_UNBUSY(CAN1_Chennal -> CANIF1CRQ)	;

			switch(copy_IntType)
			{
				case Status_Interrupt : CLR_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_SIE); break ; 
				case Error_Interrupt : CLE_BIT(CAN1_Chennal -> CANCTL , CAN_CTL_EIE); break ;
				case All_Interrupts : 
					/*	Disable Global Interrupt 	*/
					DISABLE_GLOBAL_INT(CAN1_Chennal -> CANCTL);
					break ;
			}
			/* Exit Configuration Mode  */
			CONFIG_MODE_DISABLE(CAN1_Chennal -> CANCTL) ;
			break ; 
	}
}
u8 CAN_u8TransmitMessageObjectSync(CAN_channel channelNumber,u32 copy_u32ObjID , CAN_MassegeObject *psMsgObject , FIFO_Mode copy_FIFOStatues)
{
	u8 local_u8ErrorState = 1 ;
    u16 local_u16CMSK = 0 ;
	u16 local_u16ArbReg1 = 0 , local_u16ArbReg2 = 0, local_u16MCTL = 0,local_u16MskReg1 = 0,local_u16MskReg2 = 0;
	/*	GET REG VALUES FOR THIS CONFIGURATION	*/
	local_u8ErrorState = CAN_u8MessageObjectConfig(TX,&psMsgObject ,copy_FIFOStatues , local_u16CMSK , local_u16ArbReg1,local_u16ArbReg2,local_u16MCTL,local_u16MskReg1,local_u16MskReg2,copy_u32ObjID) ;
	if(local_u8ErrorState == 0 ) {return 0 ;} 

	switch(channelNumber)
	{
		case CAN0 : 
			/*	Makesure Bus Now is unbusy no message to/from bus 	*/
			WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;
			CAN_voidWriteDataHandling(psMsgObject -> pointer_MsgData,CAN0_Chennal->CANIF1DA1 , psMsgObject -> copy_u32MsgLength ) ;  
			  // Update Registers 
			  CAN0_Chennal -> CANIF1CMSK = local_u16CMSK ; 
			  CAN0_Chennal -> CANIF1MSK1 = local_u16MskReg1 ; 
			  CAN0_Chennal -> CANIF1MSK2 = local_u16MskReg2 ; 
			  CAN0_Chennal -> CANIF1ARB1 = local_u16ArbReg1 ; 
			  CAN0_Chennal -> CANIF1ARB2 = local_u16ArbReg2 ; 
			  CAN0_Chennal -> CANIF1MCTL = local_u16MCTL ; 	
			/*	Finally Set MSG Object Selects one of the 32 message objects in the message RAM for data
transfer. The message objects are numbered from 1 to 32	*/
			  CAN0_Chennal -> CANIF1CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ; 
			  /*	Wait Until Transmit	*/
			  WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;
			break ; 
		case CAN1 : 
			/*	Makesure Bus Now is unbusy no message to/from bus 	*/
			WAIT_BUS_BE_UNBUSY(CAN1_Chennal -> CANIF1CRQ)	;
			CAN_voidWriteDataHandling(psMsgObject -> pointer_MsgData,CAN1_Chennal->CANIF1DA1 , psMsgObject -> copy_u32MsgLength ) ;  
			  // Update Registers 
			  CAN1_Chennal -> CANIF1CMSK = local_u16CMSK ; 
			  CAN1_Chennal -> CANIF1MSK1 = local_u16MskReg1 ; 
			  CAN1_Chennal -> CANIF1MSK2 = local_u16MskReg2 ; 
			  CAN1_Chennal -> CANIF1ARB1 = local_u16ArbReg1 ; 
			  CAN1_Chennal -> CANIF1ARB2 = local_u16ArbReg2 ; 
			  CAN1_Chennal -> CANIF1MCTL = local_u16MCTL ; 	
			/*	Finally Set MSG Object Selects one of the 32 message objects in the message RAM for data
transfer. The message objects are numbered from 1 to 32	*/
			  CAN1_Chennal -> CANIF1CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ; 
			  /*	Wait Until Transmit	*/
			  WAIT_BUS_BE_UNBUSY(CAN1_Chennal -> CANIF1CRQ)	;		
		
			break ;
	}
	return local_u8ErrorState ;
}

u8 CAN_u8TransmitMessageObjectAsync(CAN_channel channelNumber,u32 copy_u32ObjID , CAN_MassegeObject *psMsgObject , FIFO_Mode copy_FIFOStatues,void(*callBack)(void))
{
	
	u8 local_u8ErrorState = 1 ;
    u16 local_u16CMSK = 0 ;
	u16 local_u16ArbReg1 = 0 , local_u16ArbReg2 = 0, local_u16MCTL = 0,local_u16MskReg1 = 0,local_u16MskReg2 = 0;
	/*	GET REG VALUES FOR THIS CONFIGURATION	*/
	local_u8ErrorState = CAN_u8TransmitMessageObjectConfig(&psMsgObject ,copy_FIFOStatues , local_u16CMSK , local_u16ArbReg1,local_u16ArbReg2,local_u16MCTL,local_u16MskReg1,local_u16MskReg2,copy_u32ObjID) ;
	/*	SET Async Fn	*/
	CAN_voidMessageAsyncObjectConfig(1 ,&local_u16MCTL ) ; 
	/*	Check ERROR	*/
	if(local_u8ErrorState == 0 ) {return 0 ;} 

	switch(channelNumber)
	{
		case CAN0 : 
			/*	Set Callback Function	*/
			Callback_TX_CAN0 = callBack ; 
			/*	Makesure Bus Now is unbusy no message to/from bus 	*/
			WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;
			CAN_voidWriteDataHandling(psMsgObject -> pointer_MsgData,CAN0_Chennal->CANIF1DA1 , psMsgObject -> copy_u32MsgLength ) ;  
			  // Update Registers 
			  CAN0_Chennal -> CANIF1CMSK = local_u16CMSK ; 
			  CAN0_Chennal -> CANIF1MSK1 = local_u16MskReg1 ; 
			  CAN0_Chennal -> CANIF1MSK2 = local_u16MskReg2 ; 
			  CAN0_Chennal -> CANIF1ARB1 = local_u16ArbReg1 ; 
			  CAN0_Chennal -> CANIF1ARB2 = local_u16ArbReg2 ; 
			  CAN0_Chennal -> CANIF1MCTL = local_u16MCTL ; 	
			/*	Finally Set MSG Object Selects one of the 32 message objects in the message RAM for data
transfer. The message objects are numbered from 1 to 32	*/
			  CAN0_Chennal -> CANIF1CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ; 

			break ; 
		case CAN1 : 
			/*	Set Callback Function	*/
			Callback_TX_CAN1 = callBack ; 
			/*	Makesure Bus Now is unbusy no message to/from bus 	*/
			WAIT_BUS_BE_UNBUSY(CAN1_Chennal -> CANIF1CRQ)	;
			CAN_voidWriteDataHandling(psMsgObject -> pointer_MsgData,CAN1_Chennal->CANIF1DA1 , psMsgObject -> copy_u32MsgLength ) ;  
			  // Update Registers 
			  CAN1_Chennal -> CANIF1CMSK = local_u16CMSK ; 
			  CAN1_Chennal -> CANIF1MSK1 = local_u16MskReg1 ; 
			  CAN1_Chennal -> CANIF1MSK2 = local_u16MskReg2 ; 
			  CAN1_Chennal -> CANIF1ARB1 = local_u16ArbReg1 ; 
			  CAN1_Chennal -> CANIF1ARB2 = local_u16ArbReg2 ; 
			  CAN1_Chennal -> CANIF1MCTL = local_u16MCTL ; 	
			/*	Finally Set MSG Object Selects one of the 32 message objects in the message RAM for data
transfer. The message objects are numbered from 1 to 32	*/
			  CAN1_Chennal -> CANIF1CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ; 
		
		
			break ;
	}
	return local_u8ErrorState ;
}
static u8 CAN_u8MessageObjectConfig(u8 TX_RX_RM , CAN_MassegeObject *psMsgObject ,FIFO_Mode copy_FIFOStatues , u16 *local_u16CMSK ,u16 *copy_u16ArbReg1 , u16 *copy_u16ArbReg2, u16 *copy_u16MCTL,u16 *copy_u16MskReg1, u16 *copy_u16MskReg2 , u32 copy_u32ObjID )
{
	u8 local_u8ErrorState = 1 ;

	/*	Check ID Object Range	*/
	if(copy_u32ObjID >= ID_OBJ_MIN && copy_u32ObjID <= ID_OBJ_MAX)
	{ local_u8ErrorState = 0 ; return local_u8ErrorState ; }
	/*	Transfer the data in the CANIFn registers to the CAN message object specified by the MNUM field in the CAN Command Request (CANIFnCRQ). */
	SET_BIT(*local_u16CMSK , CAN_IF1CMSK_WRNRD ) ;
	/*	transfer data bytes 0-3 in message object to CANIFnDA1 and CANIFnDA2.	*/
	SET_BIT(*local_u16CMSK , CAN_IF1CMSK_DATAA ) ;
	/*	transfer data bytes 4-7 in message object to CANIFnDA1 and CANIFnDA2.	*/
	SET_BIT(*local_u16CMSK, CAN_IF1CMSK_DATAB ) ;
	/*	transfer the control bits into the interface registers 	*/
	SET_BIT(*local_u16CMSK, CAN_IF1CMSK_CONTROL ) ;

	/*	Check Extended Frame	*/
	if((psMsgObject->copy_u32MsgID > CAN_MAX_11BIT_MSG_ID) || (psMsgObject-> copy_u8ExtendedFrameFlag == 1))
	{

		// Set the 29 bits of Identifier mask that were requested.
		*copy_u16MskReg1 = psMsgObject->copy_u32MsgID & CAN_IF1MSK1_IDMSK_M ;
		*copy_u16MskReg2 = (psMsgObject->copy_u32MsgID >> 16) & CAN_IF1MSK2_IDMSK_M ;
		
		// Set the 29 bits of Identifier mask that were requested.
		*copy_u16ArbReg1 = psMsgObject->copy_u32MsgID & CAN_IF1ARB1_ID_M ;
		*copy_u16ArbReg2 = (psMsgObject->copy_u32MsgID >> 16) & CAN_IF1ARB2_ID_M ;
		
		// Mark the message as valid and set the extended ID bit.
		SET_BIT(*copy_u16ArbReg2 , CAN_IF1ARB2_XTD ) ;
	}
	else 
	{

		// Lower 16 bit are unused so set them to zero.
		*copy_u16MskReg1 = 0 ;
		*copy_u16ArbReg1 = 0 ;
		*copy_u16MskReg2 = (psMsgObject->copy_u32MsgID << 2) &(CAN_IF1MSK2_IDMSK_M ) ; // I don't care about last two lSB
		*copy_u16ArbReg2 = (psMsgObject->copy_u32MsgID << 2) &(CAN_IF1ARB2_XTD ) ; // I don't care about last two lSB
	}
	switch (TX_RX_RM)
	{
		case TX :
			/*	Set the TXRQST bit	*/
			SET_BIT(*copy_u16MCTL , CAN_IF1MCTL_TXRQST) ;
			/*	Set Transmit Direction	*/
			SET_BIT(*copy_u16ArbReg2 , CAN_IF1ARB2_DIR ) ;
			break ; 
		case RX : 
			*copy_u16ArbReg2 = 0 ; 
			break ; 
		case TX_REMOTE : 
			/*	Set the TXRQST bit	*/
			SET_BIT(*copy_u16MCTL , CAN_IF1MCTL_TXRQST) ;
			/*	Waiting Data So I'm Reciever */
			CLR_BIT(*copy_u16ArbReg2 , CAN_IF1ARB2_DIR ) ;
			break ; 
		case RX_REMOTE : 
			/*	CLR the TXRQST bit	*/
			CLR_BIT(*copy_u16MCTL , CAN_IF1MCTL_TXRQST) ;
			/* So I'm Transmitter */
			SET_BIT(*copy_u16ArbReg2 , CAN_IF1ARB2_DIR ) ;		
			break ; 
	}

	// Set Extended Filter
	if (psMsgObject -> copy_u8FilterExtendedIdentifierFlag == 1 )
	{
		SET_BIT(*copy_u16MskReg2,CAN_IF1MSK2_MXTD ) ;
		// Set the UMASK bit to enable using the mask register.
		SET_BIT(*copy_u16MCTL ,CAN_IF1MCTL_UMASK) ;
		//Set the MASK bit so that this gets transferred to the Message Object.
		SET_BIT(*local_u16CMSK , CAN_IF1CMSK_MASK ) ;
	}
	// filter on the message direction field.
	if ( psMsgObject -> copy_u8FilterMsgDirectionFlag == 1)
	{
		SET_BIT(*copy_u16MskReg2,CAN_IF1MSK2_MDIR ) ;
		// Set the UMASK bit to enable using the mask register.
		SET_BIT(*copy_u16MCTL ,CAN_IF1MCTL_UMASK) ;
		//Set the MASK bit so that this gets transferred to the Message Object.
		SET_BIT(*local_u16CMSK , CAN_IF1CMSK_MASK ) ;
		
	}
	// Transfer ID + DIR + XTD + MSGVAL of the message object into the Interface registers(Message object).
	SET_BIT(*local_u16CMSK , CAN_IF1CMSK_ARB ) ;
	
	/* 	SET DLC	*/
	if(CHECK_DLC_IN_RANGE(psMsgObject-> copy_u32MsgLength))
	{
		*copy_u16MCTL |= ((psMsgObject-> copy_u32MsgLength)& CAN_IF1MCTL_DLC_M) ;
	}
	else 
	{
		//<!TODO ERROR>
		 local_u8ErrorState = 0 ; return local_u8ErrorState ; 
	}
	/*	FIFO MODE	*/
	switch(copy_FIFOStatues)
	{
		case Enable_FIFO: 
			CLR_BIT(*local_u16CMSK ,CAN_IF1MCTL_EOB ) ;
			break ; 
		case Disable_FIFO: SET_BIT(*local_u16CMSK ,CAN_IF1MCTL_EOB ) ; break ;
	}
	return local_u8ErrorState ; 
}
u8 CAN_u8RecieveMessageObjectSync(CAN_channel channelNumber,u32 copy_u32ObjID , CAN_MassegeObject *psMsgObject , FIFO_Mode copy_FIFOStatues)
{
	/*	Passing Parameters	*/
	u8 local_u8ErrorState = 1 ;
    u16 local_u16CMSK = 0 ;
	u16 local_u16ArbReg1 = 0 , local_u16ArbReg2 = 0, local_u16MCTL = 0,local_u16MskReg1 = 0,local_u16MskReg2 = 0;
	/*	Initalize Msg Object */
	local_u8ErrorState = CAN_u8MessageObjectConfig(RX ,&psMsgObject,copy_FIFOStatues , &local_u16CMSK ,&local_u16ArbReg1 , &local_u16ArbReg2 ,&local_u16MCTL ,&local_u16MskReg1, &local_u16MskReg2 ,copy_u32ObjID );
	if(local_u8ErrorState == 0 ) {return 0 ;} 
	switch(channelNumber)
	{
		case CAN0 : 
			// Update F1 Registers 
			CAN0_Chennal -> CANIF1CMSK = local_u16CMSK ; 
			CAN0_Chennal -> CANIF1MSK1 = local_u16MskReg1 ; 
			CAN0_Chennal -> CANIF1MSK2 = local_u16MskReg2 ; 
			CAN0_Chennal -> CANIF1ARB1 = local_u16ArbReg1 ; 
			CAN0_Chennal -> CANIF1ARB2 = local_u16ArbReg2 ; 
			CAN0_Chennal -> CANIF1MCTL = local_u16MCTL ; 	
		    CAN0_Chennal -> CANIF1CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ;
			CAN_u8RecieveMessageObjectConfig(CAN0,&psMsgObject ,copy_u32ObjID);
			/*	Makesure Bus Now is unbusy no message to/from bus 	*/
			WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;
			break ; 
		case CAN1 : 
			// Update F1 Registers 
			CAN1_Chennal -> CANIF1CMSK = local_u16CMSK ; 
			CAN1_Chennal -> CANIF1MSK1 = local_u16MskReg1 ; 
			CAN1_Chennal -> CANIF1MSK2 = local_u16MskReg2 ; 
			CAN1_Chennal -> CANIF1ARB1 = local_u16ArbReg1 ; 
			CAN1_Chennal -> CANIF1ARB2 = local_u16ArbReg2 ; 
			CAN1_Chennal -> CANIF1MCTL = local_u16MCTL ; 	
		    CAN1_Chennal -> CANIF1CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ;
			CAN_u8RecieveMessageObjectConfig(CAN1,&psMsgObject ,copy_u32ObjID);
			/*	Makesure Bus Now is unbusy no message to/from bus 	*/
			WAIT_BUS_BE_UNBUSY(CAN1_Chennal -> CANIF1CRQ)	;
			break ; 
	}
	return local_u8ErrorState ;
}
u8 CAN_u8RecieveMessageObjectAsync(CAN_channel channelNumber,u32 copy_u32ObjID , CAN_MassegeObject *psMsgObject , FIFO_Mode copy_FIFOStatues,void(*callBack)(void))
{
	/*	Passing Parameters	*/
	u8 local_u8ErrorState = 1 ;
    u16 local_u16CMSK = 0 ;
	u16 local_u16ArbReg1 = 0 , local_u16ArbReg2 = 0, local_u16MCTL = 0,local_u16MskReg1 = 0,local_u16MskReg2 = 0;
	/*	Initalize Msg Object */
	local_u8ErrorState = CAN_u8MessageObjectConfig(RX ,&psMsgObject,copy_FIFOStatues , &local_u16CMSK ,&local_u16ArbReg1 , &local_u16ArbReg2 ,&local_u16MCTL ,&local_u16MskReg1, &local_u16MskReg2 ,copy_u32ObjID );
	if(local_u8ErrorState == 0 ) {return 0 ;} 
	/*	Set RXIE	*/
	CAN_voidMessageAsyncObjectConfig(RX,&local_u16MCTL);
	switch(channelNumber)
	{
		case CAN0 : 
			/*	Set Callback Function	*/
			Callback_RX_CAN0 = callBack ; 
			// Update F1 Registers 
			CAN0_Chennal -> CANIF1CMSK = local_u16CMSK ; 
			CAN0_Chennal -> CANIF1MSK1 = local_u16MskReg1 ; 
			CAN0_Chennal -> CANIF1MSK2 = local_u16MskReg2 ; 
			CAN0_Chennal -> CANIF1ARB1 = local_u16ArbReg1 ; 
			CAN0_Chennal -> CANIF1ARB2 = local_u16ArbReg2 ; 
			CAN0_Chennal -> CANIF1MCTL = local_u16MCTL ; 	
		    CAN0_Chennal -> CANIF1CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ;
			CAN_u8RecieveMessageObjectConfig(CAN0,&psMsgObject ,copy_u32ObjID);
			break ; 
		case CAN1 : 
			/*	Set Callback Function	*/
			Callback_RX_CAN1 = callBack ; 
			// Update F1 Registers 
			CAN1_Chennal -> CANIF1CMSK = local_u16CMSK ; 
			CAN1_Chennal -> CANIF1MSK1 = local_u16MskReg1 ; 
			CAN1_Chennal -> CANIF1MSK2 = local_u16MskReg2 ; 
			CAN1_Chennal -> CANIF1ARB1 = local_u16ArbReg1 ; 
			CAN1_Chennal -> CANIF1ARB2 = local_u16ArbReg2 ; 
			CAN1_Chennal -> CANIF1MCTL = local_u16MCTL ; 	
		    CAN1_Chennal -> CANIF1CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ;
			CAN_u8RecieveMessageObjectConfig(CAN1,&psMsgObject ,copy_u32ObjID);
			break ; 
	}
	return local_u8ErrorState ;
}
static u8 CAN_u8RecieveMessageObjectConfig(CAN_channel channelNumber, CAN_MassegeObject *psMsgObject , u32 copy_u32ObjID )
{
	u8 Error_Number ; 
	 u16 local_u16IF2CMSK ;
	u16 MaskReg1 = 0 ,MaskReg2 = 0 , ArbReg1 = 0 ,ArbReg2 = 0 ,MCTL =0 ; 
	/*	transfer data bytes 0-3 in message object to CANIFnDA1 and CANIFnDA2.	*/
	SET_BIT(local_u16IF2CMSK , CAN_IF1CMSK_DATAA ) ;
	/*	transfer data bytes 4-7 in message object to CANIFnDA1 and CANIFnDA2.	*/
	SET_BIT(local_u16IF2CMSK, CAN_IF1CMSK_DATAB ) ;
	/*	transfer the control bits into the interface registers 	*/
	SET_BIT(local_u16IF2CMSK, CAN_IF1CMSK_CONTROL ) ;
	/* Transfer ID + DIR + XTD + MSGVAL of the message object into the Interface registers.	*/
	SET_BIT(local_u16IF2CMSK, CAN_IF1CMSK_ARB ) ;
	/* Transfer ID + DIR + XTD + MSGVAL of the message object into the Interface registers.	*/	
	SET_BIT(local_u16IF2CMSK, CAN_IF1CMSK_MASK ) ;
	switch(channelNumber)
	{
	case CAN0:
		            CAN0_Chennal->CANIF2CMSK  = local_u16IF2CMSK  ;
					/* Transfer the message object to Interface Register specified by ui32ObjID */ 
					CAN0_Chennal -> CANIF2CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ;  	
					/*	BUS BUSY Transmit ID	*/
					WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;	
					// Read out the IF Registers.
					MaskReg1=  CAN0_Chennal -> CANIF2MSK1 ; 
					MaskReg2=  CAN0_Chennal -> CANIF2MSK2 ;
					ArbReg1 =  CAN0_Chennal -> CANIF2ARB1 ; 
					ArbReg2 =  CAN0_Chennal -> CANIF2ARB2 ; 
					MCTL    =  CAN0_Chennal -> CANIF2MCTL;
					break ; 
	case CAN1:       CAN1_Chennal->CANIF2CMSK  = local_u16IF2CMSK  ;
					/* Transfer the message object to the message object specified by ui32ObjID */ 
					CAN1_Chennal -> CANIF2CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ;  	
					/*	BUS BUSY Transmit ID	*/
					WAIT_BUS_BE_UNBUSY(CAN1_Chennal -> CANIF1CRQ)	;	
					// Read out the IF Registers.
					MaskReg1=  CAN1_Chennal -> CANIF2MSK1 ; 
					MaskReg2=  CAN1_Chennal -> CANIF2MSK2 ;
					ArbReg1 =  CAN1_Chennal -> CANIF2ARB1 ; 
					ArbReg2 =  CAN1_Chennal -> CANIF2ARB2 ; 
					MCTL    =  CAN1_Chennal ->CANIF2MCTL ;
					break ; 
	}
	/*	CHECK FRAME SIZE	*/
	if(GET_BIT(ArbReg2 , CAN_IF1ARB2_XTD ) == 0 )
	{
		//An 11-bit Standard Identifier is used for this message object.
		psMsgObject -> copy_u8ExtendedFrameFlag =  0 ; 
		// Set ID 
		psMsgObject ->copy_u32MsgID = ((ArbReg2&CAN_IF1ARB2_ID_M) >> 2) ; 
	}
	else 
	{
		// An 11-bit Standard Identifier is used for this message object.
		psMsgObject -> copy_u8ExtendedFrameFlag =  1 ; 
		// Set ID 
		psMsgObject ->copy_u32MsgID = (((ArbReg2&CAN_IF1ARB1_ID_M) << 16) | ArbReg1) ; 
	}
	/*	MSG VALIDATE	*/
	if(LOST_SOME_DATA(MCTL))
	{
		/* LOST DATA	*/
		Error_Number = 1 ; 
	}
	/*	 Check if ID Masking Used	*/ 
	if(GET_BIT(MCTL , CAN_IF1MCTL_UMASK) == 1 )
	{
		/*	Check Frame Size	*/
		if(psMsgObject -> copy_u8ExtendedFrameFlag)
		{
			// Extended Frame 
			psMsgObject -> copy_u32MsgIDMask = 	((MaskReg2 & CAN_IF1MSK2_IDMSK_M) << 16 ) | MaskReg1 ; 
			psMsgObject -> copy_u8FilterExtendedIdentifierFlag = 1 ;
		}
		else 
		{
			//Standard Frame
			psMsgObject -> copy_u32MsgIDMask = 	((MaskReg2 & CAN_IF1MSK2_IDMSK_M) >> 2 ) ; 
		}
		// Indicate if direction filtering was enabled.
		if(GET_BIT(MaskReg2,CAN_IF1MSK2_MDIR))
		{
			psMsgObject -> copy_u8FilterMsgDirectionFlag = 1 ; 
		}		
	}
	/*	CHECK IF NEW DATA EXIST		*/
	if(NEW_DATA_AVAILABE(MCTL))
	{
		/* Check MSG Length		*/
		psMsgObject ->copy_u32MsgLength = MCTL & CAN_IF1MCTL_DLC_M ; 
		/*	Makesure That's Not Remote Frame	*/
		if(psMsgObject -> copy_u8ExtendedFrameFlag == 0 )
		{
			switch(channelNumber)
			{
			case CAN0:
					CAN_voidReadDataHandling (psMsgObject -> pointer_MsgData , CAN0_Chennal->CANIF2DA1,psMsgObject->copy_u32MsgLength) ; 
					/*	Clear New Data Flag optional	*/
					CLR_BIT(CAN0_Chennal->CANIF2CMSK ,CAN_IF1CMSK_NEWDAT ) ; 
					/* Transfer the message object to the message object specified by ui32ObjID */ 
					CAN0_Chennal -> CANIF2CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ;  
					/*	BUS BUSY Transmit ID	*/
					WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;
					break ; 
			case CAN1:
					CAN_voidReadDataHandling (psMsgObject -> pointer_MsgData , CAN1_Chennal->CANIF2DA1,psMsgObject->copy_u32MsgLength) ; 
					/*	Clear New Data Flag optional	*/
					CLR_BIT(CAN1_Chennal->CANIF2CMSK ,CAN_IF1CMSK_NEWDAT ) ; 
					/* Transfer the message object to the message object specified by ui32ObjID */ 
					CAN1_Chennal -> CANIF2CRQ = copy_u32ObjID & CAN_IF1CRQ_MNUM_M ;  
					/*	BUS BUSY Transmit ID	*/
					WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;
					break ;
			}
			
		}
		else
		{
			/* Remote Frame Not Data Frame 	*/
			Error_Number = 2 ; 
		}	
	}
	else 
	{
			/* No New Data Available	*/
			Error_Number = 3 ;		
	}
	return Error_Number ; 
}
static void CAN_voidWriteDataHandling(u8 *pu8Data, u32 *pu32Register, u32 ui32Size)
{
	u32 Local_u32Counter = 0 ;
	u32 Local_u32Data = 0  ;
	for (Local_u32Counter =0 ; Local_u32Counter < ui32Size ; Local_u32Counter++ )
	{
		Local_u32Data = pu8Data[Local_u32Counter];
		if(Local_u32Counter < ui32Size )
		{
			Local_u32Counter++ ; 
			Local_u32Data |= (Local_u32Data << 8);
			Local_u32Counter++ ;
		}
		*(pu32Register++) = Local_u32Data;
	}
}
static void CAN_voidReadDataHandling(u8 *pui8Data, u32 *pui32Register, u32 ui32Size)
{
   u32 ui32Idx, ui32Value;

    //
    // Loop always copies 1 or 2 bytes per iteration.
    //
    for(ui32Idx = 0; ui32Idx < ui32Size; )
    {
        //
        // Read out the data 16 bits at a time since this is how the registers
        // are aligned in memory.
        //
        ui32Value = pui32Register++;

        //
        // Store the first byte.
        //
        pui8Data[ui32Idx++] = (u8)ui32Value;

        //
        // Only read the second byte if needed.
        //
        if(ui32Idx < ui32Size)
        {
            pui8Data[ui32Idx++] = (u8)(ui32Value >> 8);
        }
    }
}
static void CAN_voidMessageAsyncObjectConfig(u8 Tx_RX ,u16 *copy_u16MCTL )
{
	switch(Tx_RX)
	{
		case 1 : 
		//TX
		SET_BIT(*copy_u16MCTL , CAN_IF1MCTL_TXIE ) ; 
		global_u8TX_RX_State = 1 ; 
		break ;
		case 2 : 
		//RX
		SET_BIT(*copy_u16MCTL , CAN_IF1MCTL_RXIE ) ; 
		global_u8TX_RX_State = 2 ; 
		break ;	
		default : break ; 
	}
}	



u8 CAN_u8ErrorCounterGet (CAN_channel channelNumber , u8 *p_u8TX_Count, u8 *p_u8RX_Count)
{
	u32 Local_u32RegErrorVal = 0 ; 
	switch(channelNumber)
	{
		case CAN0 : 
			Local_u32RegErrorVal = CAN0_Chennal->CANERR ; 
		break ; 
		case CAN1 : 
			Local_u32RegErrorVal = CAN1_Chennal->CANERR ; 

		break ; 
	}
	*p_u8RX_Count = (Local_u32RegErrorVal & CAN_ERR_REC_M) >> CAN_ERR_REC_S ; 
	*p_u8TX_Count = (Local_u32RegErrorVal & CAN_ERR_TEC_M) >> CAN_ERR_TEC_S ; 
	if(GET_BIT(Local_u32RegErrorVal,CAN_ERR_RP))
	{
		return 1 ; 
	}
	else
	{
		return 0; 
	}
}
void __vector_39(void)
{	
	if(global_u8TX_RX_State == 1 )
	{
		// TRANSMIT
		Callback_TX_CAN0();
		global_u8TX_RX_State=0; 
	}
	else if(global_u8TX_RX_State == 2 )
	{
		//RECIEVE
		Callback_RX_CAN0();
		global_u8TX_RX_State =0 ;
	}
	/*	Clear Flag	*/

}
void __vector_40(void)
{	
	if(global_u8TX_RX_State == 1 )
	{
		// TRANSMIT
		Callback_TX_CAN1();
		global_u8TX_RX_State=0; 
	}
	else if(global_u8TX_RX_State == 2 )
	{
		//RECIEVE
		Callback_RX_CAN1();
		global_u8TX_RX_State =0 ;
	}
		/*	Clear Flag	*/
	CLR_BIT(CAN1_Chennal->CANSTS , CAN_STS_TXOK ) ;
	CLR_BIT(CAN1_Chennal->CANSTS , CAN_STS_RXOK ) ;
}

