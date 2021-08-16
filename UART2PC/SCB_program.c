/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 27 August 2020                                                    */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SCB_interface.h"
#include "SCB_private.h"
#include "SCB_config.h"


u32 SCB_u32PriorityInit()
{
	u32 LOC_u32RegisterValue = 0;
	LOC_u32RegisterValue	 = SCB_AIRCR_VECT_KEY +0x0+ SCB_GROUP_SUB_SELECTION + 0x00 ;
	SCB_AIRCR = LOC_u32RegisterValue ; 
	return LOC_u32RegisterValue ; 
}
