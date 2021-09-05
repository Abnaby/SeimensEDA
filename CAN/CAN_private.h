/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 29 August 2020                                                    */
/*********************************************************************************/



#ifndef CAN_PRIVATE_H
#define CAN_PRIVATE_H

typedef struct{
	volatile u32 CANCTL ;
	volatile u32 CANSTS ;
	volatile u32 CANBIT ;
	volatile u32 CANINT ;
	volatile u32 CANTST ;
	volatile u32 CANBRPE ;
	volatile u32 CANIF1CRQ ;
	volatile u32 CANIF1CMSK ;
	volatile u32 CANIF1MSK1 ;
	volatile u32 CANIF1MSK2 ;
	volatile u32 CANIF1ARB1 ;
	volatile u32 CANIF1ARB2 ;
	volatile u32 CANIF1MCTL ;
	volatile u32 CANIF1DA1 ;
	volatile u32 CANIF1DA2 ;
	volatile u32 CANIF1DB1 ;
	volatile u32 CANIF1DB2 ;
	volatile u32 CANIF2CRQ ;
	volatile u32 CANIF2CMSK ;
	volatile u32 CANIF2MSK1 ;
	volatile u32 CANIF2MSK2 ;
	volatile u32 CANIF2ARB1 ;
	volatile u32 CANIF2ARB2 ;
	volatile u32 CANIF2MCTL ;
	volatile u32 CANIF2DA1 ;
	volatile u32 CANIF2DA2 ;
	volatile u32 CANIF2DB1 ;
	volatile u32 CANIF2DB2 ;
	volatile u32 CANTXRQ1 ;
	volatile u32 CANTXRQ2 ;
	volatile u32 CANNWDA1 ;
	volatile u32 CANNWDA2 ;
	volatile u32 CANMSG1INT ;
	volatile u32 CANMSG2INT ;
	volatile u32 CANMSG1VAL ;
	volatile u32 CANMSG2VAL ;

}CAN_Registers;

#define CAN0_Chennal  ((volatile CAN_Registers *)0x40040000)
#define CAN1_Chennal  ((volatile CAN_Registers *)0x40041000)


/******************************************************************************
* Configuration Constants
*******************************************************************************/
//*****************************************************************************
//
// This is the maximum number that can be stored as an 11bit Message
// identifier.
//
//*****************************************************************************
#define CAN_MAX_11BIT_MSG_ID    0x7ff
//*****************************************************************************
//
// ID Object maximum number and minmum number.
//
//*****************************************************************************
#define ID_OBJ_MAX	32
#define ID_OBJ_MIN	1

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_CTL register.
//
//*****************************************************************************
#define CAN_CTL_TEST            7					  // Test Mode Enable
#define CAN_CTL_CCE             6					  // Configuration Change Enable
#define CAN_CTL_DAR             5					  // Disable Automatic-Retransmission
#define CAN_CTL_EIE             3					  // Error Interrupt Enable
#define CAN_CTL_SIE             2					  // Status Interrupt Enable
#define CAN_CTL_IE              1					  // CAN Interrupt Enable
#define CAN_CTL_INIT            0					  // Initialization
//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1CRQ register.
//
//*****************************************************************************
#define CAN_IF1CRQ_BUSY         15				  // Busy Flag
//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1CMSK register.
//
//*****************************************************************************
#define CAN_IF1CMSK_WRNRD       7  // Write, Not Read
#define CAN_IF1CMSK_MASK        6  // Access Mask Bits
#define CAN_IF1CMSK_ARB         5  // Access Arbitration Bits
#define CAN_IF1CMSK_CONTROL     4  // Access Control Bits
#define CAN_IF1CMSK_CLRINTPND   3  // Clear Interrupt Pending Bit
#define CAN_IF1CMSK_NEWDAT      2  // Access New Data
#define CAN_IF1CMSK_TXRQST      2  // Access Transmission Request
#define CAN_IF1CMSK_DATAA       1  // Access Data Byte 0 to 3
#define CAN_IF1CMSK_DATAB       0  // Access Data Byte 4 to 7
//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_TST register.
//
//*****************************************************************************
#define CAN_TST_RX              7  // Receive Observation
#define CAN_TST_TX_H            6  // Transmit Control
#define CAN_TST_TX_L	      	5  // Transmit Control
#define CAN_TST_LBACK           4  // Loopback Mode
#define CAN_TST_SILENT          3  // Silent Mode
#define CAN_TST_BASIC           2  // Basic Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_BIT register.
//
//*****************************************************************************
#define CAN_BIT_TSEG2_M        12  // Time Segment after Sample Point
#define CAN_BIT_TSEG1_M 	   8  // Time Segment Before Sample Point
#define CAN_BIT_SJW_M	       6  // (Re)Synchronization Jump Width
#define CAN_BIT_BRP_M          0  // Baud Rate Prescaler
//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1MCTL register.
//
//*****************************************************************************
#define CAN_IF1MCTL_NEWDAT      15  // New Data
#define CAN_IF1MCTL_MSGLST      14  // Message Lost
#define CAN_IF1MCTL_INTPND      13  // Interrupt Pending
#define CAN_IF1MCTL_UMASK       12  // Use Acceptance Mask
#define CAN_IF1MCTL_TXIE        11  // Transmit Interrupt Enable
#define CAN_IF1MCTL_RXIE        10  // Receive Interrupt Enable
#define CAN_IF1MCTL_RMTEN       9  // Remote Enable
#define CAN_IF1MCTL_TXRQST      8  // Transmit Request
#define CAN_IF1MCTL_EOB         7			// End of Buffer
#define CAN_IF1MCTL_DLC_M       0x0000000F  // Data Length Code
#define CAN_IF1MCTL_DLC_S       0
//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1ARB2 register.
//
//*****************************************************************************
#define CAN_IF1ARB2_MSGVAL      15  // Message Valid
#define CAN_IF1ARB2_XTD         14  // Extended Identifier
#define CAN_IF1ARB2_DIR         13  // Message Direction
#define CAN_IF1ARB2_ID_M        0x00001FFF  // Message Identifier
#define CAN_IF1ARB2_ID_S        0
//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1MSK1 register.
//
//*****************************************************************************
#define CAN_IF1MSK1_IDMSK_M     0x0000FFFF  // Identifier Mask
#define CAN_IF1MSK1_IDMSK_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1MSK2 register.
//
//*****************************************************************************
#define CAN_IF1MSK2_MXTD        15  // Mask Extended Identifier
#define CAN_IF1MSK2_MDIR        14  // Mask Message Direction
#define CAN_IF1MSK2_IDMSK_M     0x00001FFF  // Identifier Mask
#define CAN_IF1MSK2_IDMSK_S     0
//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1ARB1 register.
//
//*****************************************************************************
#define CAN_IF1ARB1_ID_M        0x0000FFFF  // Message Identifier
#define CAN_IF1ARB1_ID_S        0

/*		Equations		*/
	
#define BRP_RANGE_CHECK(BRP_VALUE)	(BRP_VALUE>= 0x00 && BRP_VALUE <= 0x03F)
#define SJW_RANGE_CHECK(SJW_VALUE)	(SJW_VALUE>= 0x00 && SJW_VALUE <= 0x03)
#define TSEG1_RANGE_CHECK(TSEG1_VALUE)	(TSEG1_VALUE>= 0x00 && TSEG1_VALUE <= 0x0F)
#define TSEG2_RANGE_CHECK(TSEG2_VALUE)	(TSEG2_VALUE>= 0x00 && TSEG2_VALUE <= 0x07)
		
/*  private fn  */
static u8
CAN_u8TransmitMessageObjectConfig(CAN_MassegeObject *psMsgObject ,FIFO_Mode copy_FIFOStatues , u16 *local_u16CMSK ,u16 *copy_u16ArbReg1 , u16 *copy_u16ArbReg2, u16 *copy_u16MCTL,u16 *copy_u16MskReg1, u16 *copy_u16MskReg2 , u32 copy_u32ObjID );
static void CAN_voidDataHandling(u8 *pu8Data, u32 *pu32Register, u32 ui32Size);



#endif
