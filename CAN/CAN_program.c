/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 2 September 2020                                                   */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "CAN_interface.h"
#include "CAN_private.h"
#include "CAN_config.h"


#define WAIT_BUS_BE_UNBUSY(CAN_IF2CRQ_Reg)					while((GET_BIT(CAN_IF2CRQ_Reg,CAN_IF1CRQ_BUSY)) == 1)
#define CONFIG_MODE_ENABLE(CAN_CHENNAL) 					SET_BIT(CAN_CHENNAL , CAN_CTL_INIT)
#define CONFIG_MODE_DISABLE(CAN_CHENNAL)					CLR_BIT(CAN_CHENNAL , CAN_CTL_INIT)
#define ENABLE_GLOBAL_INT(CAN_CHENNAL_CTL_REG)				SET_BIT(CAN_CHENNAL_CTL_REG,CAN_CTL_IE) 
#define DISABLE_GLOBAL_INT(CAN_CHENNAL_CTL_REG)				CLR_BIT(CAN_CHENNAL_CTL_REG,CAN_CTL_IE)
#define SUCCESSFUL_MSG_OBJ_TRANSMISSION(CAN_CHENNAL_CANNWDA1_REG)	(GET_BIT(CAN_CHENNAL_CANNWDA1_REG , 0) == 0)
#define NO_NEW_DATA_WRITEN_IN_MSG_OBJ(CAN_CHENNAL_CANTXRQ1_REG)	(GET_BIT(CAN_CHENNAL_CANTXRQ1_REG , 0) == 0)
#define CHECK_DLC_IN_RANGE(value)	(value >= 0x0 && value <= 0xF)
void CAN_voidInit(CAN_channel channelNumber,CAN_Mode WorkingMode,BitTiming_Parameter *BitRateParameter)
{
    switch(channelNumber)
    {
    case CAN0 :
		/* Enter Configuration Mode	*/	
		CONFIG_MODE_ENABLE(CAN0_Chennal -> CANCTL);
		/*	Makesure Bus Now is unbusy no message to/from bus 	*/
		WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;
		/*	Enter TEST Mode*/
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
u8 CAN_u8TransmitMessageObject(CAN_channel channelNumber,u32 copy_u32ObjID , CAN_MassegeObject *psMsgObject , FIFO_Mode copy_FIFOStatues)
{
	u8 local_u8ErrorState = 1 ;
    u16 local_u16CMSK = 0 ;
	u16 local_u16ArbReg1 = 0 , local_u16ArbReg2 = 0, local_u16MCTL = 0,local_u16MskReg1 = 0,local_u16MskReg2 = 0;
	/*	GET REG VALUES FOR THIS CONFIGURATION	*/
	local_u8ErrorState = CAN_u8TransmitMessageObjectConfig(&psMsgObject ,copy_FIFOStatues , local_u16CMSK , local_u16ArbReg1,local_u16ArbReg2,local_u16MCTL,local_u16MskReg1,local_u16MskReg2,copy_u32ObjID) ; 
	if(local_u8ErrorState == 0 ) {return 0 ;} 

	switch(channelNumber)
	{
		case CAN0 : 
			/*	Makesure Bus Now is unbusy no message to/from bus 	*/
			WAIT_BUS_BE_UNBUSY(CAN0_Chennal -> CANIF1CRQ)	;
			CAN_voidDataHandling(psMsgObject -> pointer_MsgData,CAN0_Chennal->CANIF1DA1 , psMsgObject -> copy_u32MsgLength ) ;  
			  //
			  CAN0_Chennal -> CANIF1CMSK = local_u16CMSK ; 
			  CAN0_Chennal -> CANIF1MSK1 = local_u16MskReg1 ; 
			  CAN0_Chennal -> CANIF1MSK2 = local_u16MskReg2 ; 
			  CAN0_Chennal -> CANIF1ARB1 = local_u16ArbReg1 ; 
			  CAN0_Chennal -> CANIF1ARB2 = local_u16ArbReg2 ; 
			  CAN0_Chennal -> CANIF1MCTL = local_u16MCTL ; 			
			break ; 
		case CAN1 : break ;
	}
	
}
static u8 CAN_u8TransmitMessageObjectConfig(CAN_MassegeObject *psMsgObject ,FIFO_Mode copy_FIFOStatues , u16 *local_u16CMSK ,u16 *copy_u16ArbReg1 , u16 *copy_u16ArbReg2, u16 *copy_u16MCTL,u16 *copy_u16MskReg1, u16 *copy_u16MskReg2 , u32 copy_u32ObjID )
{
	u8 local_u8ErrorState = 1 ;
	u8 local_u8ExtendedFrame = 0 ; 
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
		local_u8ExtendedFrame = 1 ;
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
		local_u8ExtendedFrame = 0 ;
		// Lower 16 bit are unused so set them to zero.
		*copy_u16MskReg1 = 0 ;
		*copy_u16ArbReg1 = 0 ;
		*copy_u16MskReg2 = (psMsgObject->copy_u32MsgID << 2) &(CAN_IF1MSK2_IDMSK_M ) ; // I don't care about last two lSB
		*copy_u16ArbReg2 = (psMsgObject->copy_u32MsgID << 2) &(CAN_IF1ARB2_XTD ) ; // I don't care about last two lSB
	}
	/*	Set the TXRQST bit	*/
	SET_BIT(*copy_u16MCTL , CAN_IF1MCTL_TXRQST) ;
	/*	Set Transmit Direction	*/
	SET_BIT(*copy_u16ArbReg2 , CAN_IF1ARB2_DIR ) ;
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
		*local_u16CMSK |= ((psMsgObject-> copy_u32MsgLength)& CAN_IF1MCTL_DLC_M) ;
	}
	else 
	{
		//<!TODO ERROR>
		 local_u8ErrorState = 0 ; return local_u8ErrorState ; 
	}
	switch(copy_FIFOStatues)
	{
		case Enable_FIFO: 
			CLR_BIT(*local_u16CMSK ,CAN_IF1MCTL_EOB ) ;
			break ; 
		case Disable_FIFO: SET_BIT(*local_u16CMSK ,CAN_IF1MCTL_EOB ) ; break ;
	}
	return local_u8ErrorState ; 
}


static void CAN_voidDataHandling(u8 *pu8Data, u32 *pu32Register, u32 ui32Size)
{
	u32 Local_u32Counter = 0 ;
	u32 Local_u32Data = 0  ;
	for (Local_u32Counter =0 ; Local_u32Counter < ui32Size ; Local_u32Counter++ )
	{
		Local_u32Data = pu8Data[Local_u32Counter];
		if(Local_u32Counter < ui32Size )
		{
			Local_u32Data |= (Local_u32Data << 8);
			Local_u32Counter++ ;
		}
		*(pu32Register++) = Local_u32Data;
	}
}







