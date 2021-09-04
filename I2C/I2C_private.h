/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 2 September 2020                                                   */
/*********************************************************************************/


#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

/******************************************************************************
* Reg Description
*******************************************************************************/


#define	I2C0_BASE_ADDRESS	 0x40020000 
#define	I2C1_BASE_ADDRESS	 0x40021000 
#define	I2C2_BASE_ADDRESS	 0x40022000 
#define	I2C3_BASE_ADDRESS	 0x40023000 

/*	Offsets	*/
//Master
#define I2CMSA			0x000
#define I2CMCS			0x004
#define I2CMDR			0x008
#define I2CMTPR			0x00C
#define I2CMIMR			0x010
#define I2CMRIS			0x014
#define I2CMMIS			0x018
#define I2CMICR			0x01C
#define I2CMCR			0x020
#define I2CMCLKOCNT		0x024
#define I2CMBMON		0x02C
#define I2CMCR2			0x038

//Slave 
#define I2CSOAR			0x800
#define I2CSCSR			0x804
#define I2CSDR			0x808
#define I2CSIMR			0x80C
#define I2CSRIS			0x810
#define I2CSMIS			0x814
#define I2CSICR			0x818
#define I2CSOAR2		0x81C
#define I2CSACKCTL		0x820

//Common
#define I2CPP		0xFC0
#define I2CPC		0xFC4


#define I2C0_I2CMCR		*((volatile u32 * ) (I2C0_BASE_ADDRESS+I2CMCR))
#define I2C0_I2CMTPR	*((volatile u32 * ) (I2C0_BASE_ADDRESS+I2CMTPR))
#define I2C0_I2CMSA		*((volatile u32 * ) (I2C0_BASE_ADDRESS+I2CMSA))
#define I2C0_I2CMCS		*((volatile u32 * ) (I2C0_BASE_ADDRESS+I2CMCS))
#define I2C0_I2CMDR     *((volatile u32 * ) (I2C0_BASE_ADDRESS+I2CMDR ))
#define I2C0_I2CSOAR     *((volatile u32 * ) (I2C0_BASE_ADDRESS+I2CSOAR ))
#define I2C0_I2CSCSR     *((volatile u32 * ) (I2C0_BASE_ADDRESS+I2CSCSR ))


/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define DISABLE	0 
#define ENABLE	1

#define SCL_LP	6
#define SCL_HP	4

#define ENABLE_MASTER	SET_BIT(I2C0_I2CMCR,I2C_MCR_MFE)
#define DISABLE_MASTER	CLR_BIT(I2C0_I2CMCR,I2C_MCR_MFE)

#define ENABLE_SLAVE SET_BIT(I2C0_I2CMCR,I2C_MCR_SFE)
#define DISABLE_SLAVE CLR_BIT(I2C0_I2CMCR,I2C_MCR_SFE)
#define TPR_EQN(SPEED)	(SYS_CLK/(2*(SCL_LP + SCL_HP)*SPEED))-1

#define Standard_speed 			100000
#define FastMode_speed 			400000
#define FastMode_Plus_speed 	1000000
#define High_speed 				3330000


//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MCR register.
//
//*****************************************************************************
#define I2C_MCR_GFE             6  // I2C Glitch Filter Enable
#define I2C_MCR_SFE             5  // I2C Slave Function Enable
#define I2C_MCR_MFE             4  // I2C Master Function Enable
#define I2C_MCR_LPBK            0  // I2C Loopback
//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MSA register.
//
//*****************************************************************************

#define I2C_MSA_R_S            0
//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MCS register.
//
//*****************************************************************************
#define I2C_MCS_CLKTO           7  // Clock Timeout Error
#define I2C_MCS_BUSBSY          6  // Bus Busy
#define I2C_MCS_IDLE            5  // I2C Idle
#define I2C_MCS_ARBLST          4  // Arbitration Lost
#define I2C_MCS_DATACK          3  // Acknowledge Data
#define I2C_MCS_ADRACK          2  // Acknowledge Address
#define I2C_MCS_ERROR           1  // Error
#define I2C_MCS_BUSY            0  // I2C Busy
//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MCS register.
//
//*****************************************************************************
#define I2C_MCS_HS              4  // High-Speed Enable
#define I2C_MCS_ACK             3  // Data Acknowledge Enable
#define I2C_MCS_STOP            2  // Generate STOP
#define I2C_MCS_START           1  // Generate START
#define I2C_MCS_RUN             0  // I2C Master Enable

/*	IRQs	*/
 void __vector_8(void) __attribute__(( signal , used ));	//I2C0
 void __vector_37(void) __attribute__(( signal , used ));	//I2C1
 void __vector_68(void) __attribute__(( signal , used ));	//I2C2
 void __vector_69(void) __attribute__(( signal , used ));	//I2C3



#endif
