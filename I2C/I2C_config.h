/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 2 September 2020                                                   */
/*********************************************************************************/
#ifndef I2C_CONFIG_H

#define I2C_CONFIG_H

#define I2C0_GLITCH_FILTER	DISABLE
#define I2C1_GLITCH_FILTER	DISABLE
#define I2C2_GLITCH_FILTER	DISABLE
#define I2C3_GLITCH_FILTER	DISABLE

/****************************************************************/
/**	 Enter the CPU FREQ											*/
/** 		   F_CPU can be : 									*/
/*					    			16MHz = 16000000UL	 		*/
/*						    		8MHz  = 8000000UL 			*/
/****************************************************************/

#define SYS_CLK				8000000UL		

#endif

