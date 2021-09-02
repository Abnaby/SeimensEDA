/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 2 September 2020                                                   */
/*********************************************************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

	#define SET_BIT(VAR,BIT_NUM)	VAR |= (1 << BIT_NUM)
	#define CLR_BIT(VAR,BIT_NUM)	VAR &= ~(1<<BIT_NUM)
	#define TOG_BIT(VAR,BIT_NUM)	VAR ^= (1 << BIT_NUM)
	#define GET_BIT(VAR,BIT_NUM)	VAR  = ((1 >>  BIT_NUM) & 1	)	
	#define NULL (void *)0


#endif

	