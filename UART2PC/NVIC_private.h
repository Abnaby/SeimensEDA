/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 26 August 2020                                                    */
/*********************************************************************************/



#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

#define NVIC_BASE_ADDRESS	 0xE000E100
		/*		REGISTER BOUNDARY ADDRESSES 		*/
#define NVIC_ISER       ((volatile u32 *)(NVIC_BASE_ADDRESS + 0x000))
#define NVIC_ICER       ((volatile u32 *)(NVIC_BASE_ADDRESS + 0x080))
#define NVIC_ISPR       ((volatile u32 *)(NVIC_BASE_ADDRESS + 0x100))
#define NVIC_ICPR       ((volatile u32 *)(NVIC_BASE_ADDRESS + 0x180))
#define NVIC_IABR 	((volatile u32 *)(NVIC_BASE_ADDRESS + 0x200))
#define NVIC_IPR	((volatile u32 *)(NVIC_BASE_ADDRESS + 0x300))
#define NVIC_STIR	((volatile u32 *)(NVIC_BASE_ADDRESS + 0xE00))




#endif
