/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 26 August 2020                                                    */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"

#include "SCB_interface.h"


void NVIC_voidEnableInterrupt  ( u8 Copy_u8IntNumber )
{
	if(Copy_u8IntNumber <= 31)
	{
		SET_BIT(NVIC_ISER[0] , Copy_u8IntNumber ); 
	}
	else if (Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber -= 32 ; 
		SET_BIT(NVIC_ISER[1] , Copy_u8IntNumber ); 
	}
	else 
	{
		/*	 <TODO> ERROR OUT OF INTERRUPT NUMBERS	*/
	}
}
void NVIC_voidDisableInterrupt ( u8 Copy_u8IntNumber )
{
	if(Copy_u8IntNumber <= 31)
	{
		SET_BIT(NVIC_ICER[0] , Copy_u8IntNumber ); 
	}
	else if (Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber -= 32 ; 
		SET_BIT(NVIC_ICER[1] , Copy_u8IntNumber ); 
	}
	else 
	{
		/*	 <TODO> ERROR OUT OF INTERRUPT NUMBERS	*/
	}	
}
void NVIC_voidSetPenddingFlag  ( u8 Copy_u8IntNumber )
{
	if(Copy_u8IntNumber <= 31)
	{

		SET_BIT(NVIC_ISPR[0] , Copy_u8IntNumber ); 
	}
	else if (Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber -= 32 ; 
		SET_BIT(NVIC_ISPR[1] , Copy_u8IntNumber ); 
	}
	else 
	{
		/*	 <TODO> ERROR OUT OF INTERRUPT NUMBERS	*/
	}		
}
void NVIC_voidClearPenddingFlag( u8 Copy_u8IntNumber )
{
	if(Copy_u8IntNumber <= 31)
	{
		SET_BIT(NVIC_ICPR[0] , Copy_u8IntNumber ); 
	}
	else if (Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber -= 32 ; 
		SET_BIT(NVIC_ICPR[1] , Copy_u8IntNumber ); 
	}
	else 
	{
		/*	 <TODO> ERROR OUT OF INTERRUPT NUMBERS	*/
	}	
}
u8 	 NVIC_u8GetInterruptStatus ( u8 Copy_u8IntNumber )
{
	u8 LOC_u8ActiveBitStatues = 0 ;
	if(Copy_u8IntNumber <= 31)
	{
		LOC_u8ActiveBitStatues = GET_BIT(NVIC_IABR[0] , Copy_u8IntNumber ); 
	}
	else if (Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber -= 32 ; 
		LOC_u8ActiveBitStatues = GET_BIT(NVIC_IABR[1] , Copy_u8IntNumber ); 
	}
	else 
	{
		/*	 <TODO> ERROR OUT OF INTERRUPT NUMBERS	*/
	}
	return LOC_u8ActiveBitStatues ; 
}

void NVIC_voidSetPeriority(u8 Copy_u8IntNumber , u8 Copy_u8GroupPriority , u8 Copy_u8SubGroupPriority)
{
	u8  LOC_u8SetIprRegValue = 0 ;
	u32 LOC_u32NumOfGrousAndSub = SCB_u32PriorityInit();
	/*	Copy_u8GroupPriority<<((NO - 0x05FA0300 ) / 0x100 To get Number of bits of sub group */
	LOC_u8SetIprRegValue = Copy_u8SubGroupPriority | (Copy_u8GroupPriority<<((LOC_u32NumOfGrousAndSub - 0x05FA0300 ) / 0x100 ) );
	if (Copy_u8IntNumber < 60 )
	{
		NVIC_IPR[Copy_u8IntNumber] = (LOC_u8SetIprRegValue << 4 ); 
	}
	else 
	{
		/*	 <TODO> ERROR OUT OF INTERRUPT NUMBERS	*/
	}
}
