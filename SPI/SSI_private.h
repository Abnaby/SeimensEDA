/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 2 September 2020                                                   */
/*********************************************************************************/


#ifndef SSI_PRIVATE_H
#define SSI_PRIVATE_H

typedef struct
{
    volatile u32 SSICR0 ; 						//SSI Control 0
	volatile u32 SSICR1 ; 						//SSI Control 1
	volatile u32 SSIDR ; 						//SSI Data
	volatile u32 SSISR ; 						//SSI Status
	volatile u32 SSICPSR ; 						//SSI Clock Prescale
	volatile u32 SSIIM ; 						//SSI Interrupt Mask
	volatile u32 SSIRIS ; 						//SSI Raw Interrupt Status
	volatile u32 SSIMIS ; 						//SSI DMA Control
	volatile u32 SSIICR ; 						//SSI DMA Control
	volatile u32 SSIDMACTL ; 					//SSI DMA Control
	volatile u32 SSICC ; 						//SSI Clock Configuration
	volatile u32 SSIPeriphID4 ; 				//SSI PrimeCell Identification 4
	volatile u32 SSIPeriphID5 ; 				//SSI PrimeCell Identification 5
	volatile u32 SSIPeriphID6 ; 				//SSI PrimeCell Identification 6
	volatile u32 SSIPeriphID7 ; 				//SSI PrimeCell Identification 7
	volatile u32 SSIPeriphID0 ; 				//SSI PrimeCell Identification 0
	volatile u32 SSIPeriphID1 ; 				//SSI PrimeCell Identification 1
	volatile u32 SSIPeriphID2 ; 				//SSI PrimeCell Identification 2
	volatile u32 SSIPeriphID3 ; 				//SSI PrimeCell Identification 3
	volatile u32 SSIPCellID0 ; 					//SSI PrimeCell Identification 0
	volatile u32 SSIPCellID1 ;					//SSI PrimeCell Identification 1
	volatile u32 SSIPCellID2 ;					//SSI PrimeCell Identification 2
	volatile u32 SSIPCellID3 ;					//SSI PrimeCell Identification 3
}SSI_Registers;


#define SSI0_module  ((volatile SSI_Registers *)0x40008000)
#define SSI1_module  ((volatile SSI_Registers *)0x40009000)	
#define SSI2_module  ((volatile SSI_Registers *)0x4000A000)	
#define SSI3_module  ((volatile SSI_Registers *)0x4000B000)	


/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define MASTER_OPERATION		0x00000000
#define SLAVE_MOD_OP_ENABLE		0x00000004
#define SLAVE_MOD_OP_DISABLE	0x0000000C

#define SYSTEM_CLK	0x00000000
#define PIOS_CLK	0x00000005 

#define IDLE_LOW    0
#define IDLE_HIGH   1

#define CAPTURE_AT_FIRST_CLK_EDGE	0
#define CAPTURE_AT_SECOND_CLK_EDGE	2
//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CR1 register.
//
//*****************************************************************************
#define SSI_CR1_EOT             4  // End of Transmission
#define SSI_CR1_MS              2  // SSI Master/Slave Select
#define SSI_CR1_SSE             1  // SSI Synchronous Serial Port
#define SSI_CR1_LBM             0  // SSI Loopback Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CR0 register.
//
//*****************************************************************************
#define SSI_CR0_SPH             7  // SSI Serial Clock Phase
#define SSI_CR0_SPO             6  // SSI Serial Clock Polarity
#define SSI_CR0_FRF_4      		4  //   Frame Format
#define SSI_CR0_FRF_5      		5  //   Frame Format

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_SR register.
//
//*****************************************************************************
#define SSI_SR_BSY              4  // SSI Busy Bit
#define SSI_SR_RFF              3  // SSI Receive FIFO Full
#define SSI_SR_RNE              2  // SSI Receive FIFO Not Empty
#define SSI_SR_TNF              1  // SSI Transmit FIFO Not Full
#define SSI_SR_TFE              0  // SSI Transmit FIFO Empty
//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_IM register.
//
//*****************************************************************************
#define SSI_IM_TXIM             3  // SSI Transmit FIFO Interrupt Mask
#define SSI_IM_RXIM             2  // SSI Receive FIFO Interrupt Mask
#define SSI_IM_RTIM             1  // SSI Receive Time-Out Interrupt 
#define SSI_IM_RORIM            0  // SSI Receive Overrun Interrupt
//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_ICR register.
//
//*****************************************************************************
#define SSI_ICR_RTIC            1  // SSI Receive Time-Out Interrupt
#define SSI_ICR_RORIC           0  // SSI Receive Overrun Interrupt
                                            
/*	IRQs	*/
 void __vector_7(void) __attribute__(( signal , used ));	//SSI0
 void __vector_34(void) __attribute__(( signal , used ));	//SSI0
 void __vector_57(void) __attribute__(( signal , used ));	//SSI0
 void __vector_58(void) __attribute__(( signal , used ));	//SSI0



#endif
