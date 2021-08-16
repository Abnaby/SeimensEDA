/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 27 August 2020                                                    */
/*********************************************************************************/



#ifndef SCB_PRIVATE_H
#define SCB_PRIVATE_H

#define SCB_BASE_ADDRESS	0xE000ED00 
		/*		REGISTER BOUNDARY ADDRESSES 		*/		
#define SCB_ACTLR 			*((volatile u32 *) SCB_BASE_ADDRESS + 0x00)
#define SCB_CPUID 			*((volatile u32 *) SCB_BASE_ADDRESS + 0x00)
#define SCB_ICSR			*((volatile u32 *) SCB_BASE_ADDRESS + 0x04)
#define SCB_VTOR	 		*((volatile u32 *) SCB_BASE_ADDRESS + 0x08)
#define SCB_AIRCR 			*((volatile u32 *) SCB_BASE_ADDRESS + 0x0C)
#define SCB_SCR			    *((volatile u32 *) SCB_BASE_ADDRESS + 0x10)
#define SCB_CCR			    *((volatile u32 *) SCB_BASE_ADDRESS + 0x14)
#define SCB_SHPR			 ((volatile u32 *) SCB_BASE_ADDRESS + 0x18)
#define SCB_SHCRS			*((volatile u32 *) SCB_BASE_ADDRESS + 0x24)
#define SCB_CFSR			*((volatile u32 *) SCB_BASE_ADDRESS + 0X28)
#define SCB_HFSR			*((volatile u32 *) SCB_BASE_ADDRESS + 0x2C)
#define SCB_MMAR			*((volatile u32 *) SCB_BASE_ADDRESS + 0x34)
#define SCB_BFAR			*((volatile u32 *) SCB_BASE_ADDRESS + 0x38)
		/*		REGISTER VECT KEY 		*/
		
#define SCB_AIRCR_VECT_KEY  0x05FA
		/*		GROUP SELECTION PRIORITY 		*/		
#define SCB_16_GROUP_0_SUB	0x3			//0b011  // 4 bits for group (IPR) ==> Group
#define SCB_8_GROUP_2_SUB	0x4			//0b100  // 3 bits for group and 1 bit for sub
#define SCB_4_GROUP_4_SUB	0x5			//0b101  // 2 bits for group and 2 bit for sun 
#define SCB_2_GROUP_8_SUB	0x6			//0b110  // 1 bit  for group and 3 bits for sub
#define SCB_0_GROUP_16_SUB	0x7			//0b111  // 0 bit for group and 4 bits for sub




#endif
