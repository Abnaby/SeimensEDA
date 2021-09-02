/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 2 September 2020                                                   */
/*********************************************************************************/
#ifndef SSI_CONFIG_H

#define SSI_CONFIG_H
/*	NOTE THAT BaudRate= SysClk/(SSIn_CLK_PRESCALER * (1 + Serial CLK Rate))
					U Enter 
							BaudRate in BitPerSecond
							SysClk 
							SSIn_CLK_PRESCALER even Number

*/		
/****************************************************************/
/**	 Enter the CPU FREQ											*/
/** 		   F_CPU can be : 									*/
/*					    			16MHz = 16000000UL	 		*/
/*						    		8MHz  = 8000000UL 			*/
/****************************************************************/

#define SYS_CLK				8000000UL					
/*
	*SSI0_CLK_PRESCALER : This value must be an even number from 2 to 254
							OPTIONS IF USED SSI0: 
									even number from 2 to 254
*/
	#define SSI0_CLK_PRESCALER		2
/*
	*SSI1_CLK_PRESCALER : This value must be an even number from 2 to 254
							OPTIONS IF USED SSI1: 
									even number from 2 to 254
*/
	#define SSI1_CLK_PRESCALER		2
/*
	*SSI2_CLK_PRESCALER : This value must be an even number from 2 to 254
							OPTIONS IF USED SSI2 : 
									even number from 2 to 254
*/
	#define SSI2_CLK_PRESCALER		2
/*
	*SSI3_CLK_PRESCALER : This value must be an even number from 2 to 254
							OPTIONS IF USED SSI3: 
									even number from 2 to 254
*/
	#define SSI3_CLK_PRESCALER		2
/*
	*SSI0_IDLE_STATE : 
							OPTIONS IF USED SSI0: 
									IDLE_LOW
									IDLE_HIGH
	if Select High, then software must also configure the GPIO port pin signal as a pull-up in the GPIO Pull-Up Select 
*/
    #define SSI0_IDLE_STATE      IDLE_HIGH

/*
*SSI0_DATA_CAPTURING : 
						OPTIONS IF USED SSI0: 
								CAPTURE_AT_FIRST_CLK_EDGE
								CAPTURE_AT_SECOND_CLK_EDGE
*/
	#define SSI0_DATA_CAPTURING		CAPTURE_AT_SECOND_CLK_EDGE

#endif

