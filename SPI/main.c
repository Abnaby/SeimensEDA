#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SSI_interface.h"

int main(void)
{
	/*	CLK	*/
	SYSCTL->RCGCSSI |= 0x1; // Enable and provide a clock to SPI0
 	SYSCTL->RCGCGPIO |= 0x1; // Enable and provide a clock to GPIO PortA 

	/*	Must Select the slave by making active-low slave select line low GPIOA->DATA 	*/
	GPIOA->AFSEL |= 0x3C; // Enable alternate functions on PA2, PA3, PA4, PA5  
	GPIOA->PCTL |= 0x222200; // Assign SPI signals to PA2, PA3, PA4, PA5   
	GPIOA->DEN |= 0x3C; // Enable digital functions for PA2, PA3, PA4, PA5    
	GPIOA->DIR |= 0x8; // Set PA3 as output 
	GPIOA->DATA |= 0x8; // Make slave select line high when idle 
	/*	Init SPI0
					on : SSI0	MasterMode	using SysCLK	11500bitPerSecond  SPI_Frame	7-bit Data size*/
	void SSI_voidInit(SSI0,Master,SysCLK, 11500 ,SPI,7);
	void SSI_voidEnable(SSI0);
	void SSI_voidTransmitSynch(SSI0 ,'A');
	
	while(1)
	{
		
	}
	return 0;
}
