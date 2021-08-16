/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 26 August 2020                                                    */
/*********************************************************************************/

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H


		/*			PUBLIC FUNCTIONS  					*/	
void NVIC_voidEnableInterrupt  ( u8 Copy_u8IntNumber ) ; 
void NVIC_voidDisableInterrupt ( u8 Copy_u8IntNumber ) ; 
void NVIC_voidSetPenddingFlag  ( u8 Copy_u8IntNumber ) ; 
void NVIC_voidClearPenddingFlag( u8 Copy_u8IntNumber ) ; 
void NVIC_voidSetPeriority(u8 Copy_u8IntNumber , u8 Copy_u8GroupPriority , u8 Copy_u8SubGroupPriority);

#endif
