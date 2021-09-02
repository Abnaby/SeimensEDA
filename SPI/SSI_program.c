/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 2 September 2020                                                   */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SSI_interface.h"
#include "SSI_private.h"
#include "SSI_config.h"


#define TX_FIFO_NOT_FULL(SSIx)  while((GET_BIT(SSIx,SSI_SR_TNF)) == 0){}
#define RX_FIFO_NOT_FULL(SSIx)  while((GET_BIT(SSIx,SSI_SR_RFF)) == 1){}
#define BUS_BUSY(SSIx)	while((GET_BIT(SSIx,SSI_SR_BSY)) == 1){}
static void (*Callback_RX_SSI0) (u16) = NULL ;
static void (*Callback_TX_SSI0) (void) = NULL ;
static void (*Callback_TX_SSI1) (void) = NULL ;
static void (*Callback_TX_SSI2) (void) = NULL ;
static void (*Callback_TX_SSI3) (void) = NULL ;
u8 global_u8TX_RX_State = 0 ;
void SSI_voidInit(SSI_Channel copy_SSIChennal,SSI_Mode copy_workingMode,SSI_CLK_Mode copy_CLKSelection,u8 copy_u8BaudRate,SSI_Protocol_Mode copy_protocolMode,u8 copy_u8DataSize)
{
	u8 global_u8SerialCLKRate ; 

	switch(copy_SSIChennal)
	{
		case SSI0: 
			/*	 SSE bit in the SSICR1 register is clear before making any configuration changes.	*/
			CLR_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);
			/*	Select whether the SSI is a master or slave	*/
			switch(copy_workingMode)
			{
				case Slave : SET_BIT(SSI0_module->SSICR1,SSI_CR1_MS); break; 
				case Master : CLR_BIT(SSI0_module->SSICR1,SSI_CR1_MS); break; 
			}
			/*	Configure the SSI clock source by writing to the SSICC register	*/
			switch(copy_CLKSelection)
			{
				case SysCLK : 
					SSI0_module->SSICC = SYSTEM_CLK ; 
					break ;
				case PIOSC : 
					SSI0_module->SSICC = PIOS_CLK ; 
					break ;
			}
			/*	Configure the clock prescale divisor by writing the SSICPSR register	*/
			if(SSI0_CLK_PRESCALER%2==0 && SSI0_CLK_PRESCALER>=2 && SSI0_CLK_PRESCALER <= 254)
			{
                SSI0_module->SSICPSR = (0xFF&SSI0_CLK_PRESCALER);

			}
			else
			{
				//<!TODO ERROR>
			}
			/*	Write the SSICR0 register with the following configuration	*/
			global_u8SerialCLKRate = (SYS_CLK/(copy_u8BaudRate*SSI0_CLK_PRESCALER))-1 ; 
			if(global_u8SerialCLKRate>=0 && global_u8SerialCLKRate <=255)
			{
				SSI0_module->SSICR0 = global_u8SerialCLKRate << 8 ;  
			}else
			{
				//<!TODO ERROR>
			}

            #if SSI0_IDLE_STATE == IDLE_HIGH
                SET_BIT(SSI0_module->SSICR0,SSI_CR0_SPO);
            #elif SSI0_IDLE_STATE == IDLE_LOW
                CLR_BIT(SSI0_module->SSICR0,SSI_CR0_SPO);
            #else
                #error ("Wrong SSI_CR0_SPO Selection")
            #endif
			// Set Phase
			#if SSI0_DATA_CAPTURING == CAPTURE_AT_FIRST_CLK_EDGE
				CLR_BIT(SSI0_module->SSICR0,SSI_CR0_SPH);
			#elif SSI0_DATA_CAPTURING == CAPTURE_AT_SECOND_CLK_EDGE
				SET_BIT(SSI0_module->SSICR0,SSI_CR0_SPH);
			#endif
			// set Protocol Mode
			switch(copy_protocolMode)
			{
				case SPI : 
				CLR_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_4);
				CLR_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_5);
				break ;
				case TI_SSF :
				CLR_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_4);
				SET_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_5);
				break;
				case MICROWIRE:
				SET_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_4);
				SET_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_5);
				break;
			}
			if(copy_u8DataSize>=4 && copy_u8DataSize<=16)
			{
			    SSI0_module->SSICR0 |= (0xFF & copy_u8DataSize) ;
			}
			else
			{
				//<!TODO ERROR>
			}
			/*	Enable the SSI by setting the SSE bit in the SSICR1 register.	*/
			SET_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);
		break;
		case SSI1: break;
		case SSI2: break;
		case SSI3: break;
	}
	
}

void SSI_voidDisable(SSI_Channel copy_SSIChennal)
{
	switch(copy_SSIChennal)
	{
		case SSI0: 
		CLR_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI1:
		CLR_BIT(SSI1_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI2: 
		CLR_BIT(SSI2_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI3: 
		CLR_BIT(SSI3_module->SSICR1,SSI_CR1_SSE);
		break ; 
	}
}
void SSI_voidEnable(SSI_Channel copy_SSIChennal)
{
	switch(copy_SSIChennal)
	{
		case SSI0: 
		SET_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI1:
		SET_BIT(SSI1_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI2: 
		SET_BIT(SSI2_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI3: 
		SET_BIT(SSI3_module->SSICR1,SSI_CR1_SSE);
		break ; 
	}
}
void SSI_voidChangeSSIMode(SSI_Channel copy_SSIChennal,SSI_Mode copy_workingMode)
{
	u8 global_u8SerialCLKRate ; 
	switch(copy_SSIChennal)
	{
		case SSI0: 
			CLR_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);
			switch(copy_workingMode)
			{
				case Slave : SET_BIT(SSI0_module->SSICR1,SSI_CR1_MS); break; 
				case Master : CLR_BIT(SSI0_module->SSICR1,SSI_CR1_MS); break; 
			}
			SET_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI1: 
			CLR_BIT(SSI1_module->SSICR1,SSI_CR1_SSE);
			switch(copy_workingMode)
			{
				case Slave : SET_BIT(SSI1_module->SSICR1,SSI_CR1_MS); break; 
				case Master : CLR_BIT(SSI1_module->SSICR1,SSI_CR1_MS); break; 
			}
			SET_BIT(SSI1_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI2: 
			CLR_BIT(SSI2_module->SSICR1,SSI_CR1_SSE);	
			switch(copy_workingMode)
			{
				case Slave : SET_BIT(SSI2_module->SSICR1,SSI_CR1_MS); break; 
				case Master : CLR_BIT(SSI2_module->SSICR1,SSI_CR1_MS); break; 
			}
			SET_BIT(SSI2_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI3: 
			CLR_BIT(SSI3_module->SSICR1,SSI_CR1_SSE);
			switch(copy_workingMode)
			{
				case Slave : SET_BIT(SSI3_module->SSICR1,SSI_CR1_MS); break; 
				case Master : CLR_BIT(SSI3_module->SSICR1,SSI_CR1_MS); break; 
			}
			SET_BIT(SSI3_module->SSICR1,SSI_CR1_SSE);
		break ; 
	}
}
void SSI_voidChangeBuadRate(SSI_Channel copy_SSIChennal,u8 copy_u8BaudRate)
{
    u8 global_u8SerialCLKRate ;
	switch(copy_SSIChennal)
	{
		case SSI0: 
			CLR_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);
			/*	Write the SSICR0 register with the following configuration	*/
			global_u8SerialCLKRate = (SYS_CLK/(copy_u8BaudRate*SSI0_CLK_PRESCALER))-1 ; 
			if(global_u8SerialCLKRate>=0 && global_u8SerialCLKRate <=255)
			{
				SSI0_module->SSICR0 = global_u8SerialCLKRate << 8 ;  
			}else
			{
				//<!TODO ERROR>
			}
			SIT_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI1: 
			CLR_BIT(SSI1_module->SSICR1,SSI_CR1_SSE);
			/*	Write the SSICR0 register with the following configuration	*/
			global_u8SerialCLKRate = (SYS_CLK/(copy_u8BaudRate*SSI1_CLK_PRESCALER))-1 ; 
			if(global_u8SerialCLKRate>=0 && global_u8SerialCLKRate <=255)
			{
				SSI1_module->SSICR0 = global_u8SerialCLKRate << 8 ;  
			}else
			{
				//<!TODO ERROR>
			}
			SET_BIT(SSI1_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI2: 
			CLR_BIT(SSI2_module->SSICR1,SSI_CR1_SSE);
			/*	Write the SSICR0 register with the following configuration	*/
			global_u8SerialCLKRate = (SYS_CLK/(copy_u8BaudRate*SSI2_CLK_PRESCALER))-1 ; 
			if(global_u8SerialCLKRate>=0 && global_u8SerialCLKRate <=255)
			{
				SSI2_module->SSICR0 = global_u8SerialCLKRate << 8 ;  
			}else
			{
				//<!TODO ERROR>
			}
			SET_BIT(SSI2_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI3:
			CLR_BIT(SSI3_module->SSICR1,SSI_CR1_SSE);
			/*	Write the SSICR0 register with the following configuration	*/
			global_u8SerialCLKRate = (SYS_CLK/(copy_u8BaudRate*SSI3_CLK_PRESCALER))-1 ; 
			if(global_u8SerialCLKRate>=0 && global_u8SerialCLKRate <=255)
			{
				SSI3_module->SSICR0 = global_u8SerialCLKRate << 8 ;  
			}else
			{
				//<!TODO ERROR>
			}
			CLR_BIT(SSI3_module->SSICR1,SSI_CR1_SSE);
		break ; 
	}
}
void SSI_voidChangeProtocol(SSI_Channel copy_SSIChennal,SSI_Protocol_Mode copy_protocolMode)
{
	switch(copy_SSIChennal)
	{
		case SSI0:
		CLR_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);		
			switch(copy_protocolMode)
			{
				case SPI : 
				CLR_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_4);
				CLR_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_5);
				break ;
				case TI_SSF :
				CLR_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_4);
				SET_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_5);
				break;
				case MICROWIRE:
				SET_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_4);
				SET_BIT(SSI0_module->SSICR0 , SSI_CR0_FRF_5);
				break;
			}
			SET_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI1: 
			CLR_BIT(SSI1_module->SSICR1,SSI_CR1_SSE);
			switch(copy_protocolMode)
			{
				case SPI : 
				CLR_BIT(SSI1_module->SSICR0 , SSI_CR0_FRF_4);
				CLR_BIT(SSI1_module->SSICR0 , SSI_CR0_FRF_5);
				break ;
				case TI_SSF :
				CLR_BIT(SSI1_module->SSICR0 , SSI_CR0_FRF_4);
				SET_BIT(SSI1_module->SSICR0 , SSI_CR0_FRF_5);
				break;
				case MICROWIRE:
				SET_BIT(SSI1_module->SSICR0 , SSI_CR0_FRF_4);
				SET_BIT(SSI1_module->SSICR0 , SSI_CR0_FRF_5);
				break;
			}
			SET_BIT(SSI1_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI2: 
			CLR_BIT(SSI2_module->SSICR1,SSI_CR1_SSE);
			switch(copy_protocolMode)
			{
				case SPI : 
				CLR_BIT(SSI2_module->SSICR0 , SSI_CR0_FRF_4);
				CLR_BIT(SSI2_module->SSICR0 , SSI_CR0_FRF_5);
				break ;
				case TI_SSF :
				CLR_BIT(SSI2_module->SSICR0 , SSI_CR0_FRF_4);
				SET_BIT(SSI2_module->SSICR0 , SSI_CR0_FRF_5);
				break;
				case MICROWIRE:
				SET_BIT(SSI2_module->SSICR0 , SSI_CR0_FRF_4);
				SET_BIT(SSI2_module->SSICR0 , SSI_CR0_FRF_5);
				break;
			}
			SET_BIT(SSI2_module->SSICR1,SSI_CR1_SSE);
		break ; 
		case SSI3: 
			CLR_BIT(SSI3_module->SSICR1,SSI_CR1_SSE);
			switch(copy_protocolMode)
			{
				case SPI : 
				CLR_BIT(SSI3_module->SSICR0 , SSI_CR0_FRF_4);
				CLR_BIT(SSI3_module->SSICR0 , SSI_CR0_FRF_5);
				break ;
				case TI_SSF :
				CLR_BIT(SSI3_module->SSICR0 , SSI_CR0_FRF_4);
				SET_BIT(SSI3_module->SSICR0 , SSI_CR0_FRF_5);
				break;
				case MICROWIRE:
				SET_BIT(SSI3_module->SSICR0 , SSI_CR0_FRF_4);
				SET_BIT(SSI3_module->SSICR0 , SSI_CR0_FRF_5);
				break;
			}
			SET_BIT(SSI3_module->SSICR1,SSI_CR1_SSE);
		break ; 
	}
}
void SSI_voidChangeDataSize(SSI_Channel copy_SSIChennal,u8 copy_u8DataSize)
{
	switch(copy_SSIChennal)
	{
		case SSI0: 
			CLR_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);
			if(copy_u8DataSize>=4 && copy_u8DataSize<=16)
			{
			    SSI0_module->SSICR0 |= (0xFF & copy_u8DataSize) ;
			}
			else
			{
				//<!TODO ERROR>
			}
			SET_BIT(SSI0_module->SSICR1,SSI_CR1_SSE);
			break ; 
		case SSI1: 
			CLR_BIT(SSI1_module->SSICR1,SSI_CR1_SSE);
			if(copy_u8DataSize>=4 && copy_u8DataSize<=16)
			{
			    SSI1_module->SSICR0 |= (0xFF & copy_u8DataSize) ;
			}
			else
			{
				//<!TODO ERROR>
			}	
			SET_BIT(SSI1_module->SSICR1,SSI_CR1_SSE);			
			break ; 
		case SSI2: 
			CLR_BIT(SSI2_module->SSICR1,SSI_CR1_SSE);
			if(copy_u8DataSize>=4 && copy_u8DataSize<=16)
			{
			    SSI2_module->SSICR0 |= (0xFF & copy_u8DataSize) ;
			}
			else
			{
				//<!TODO ERROR>
			}
			SET_BIT(SSI2_module->SSICR1,SSI_CR1_SSE);
			break ; 
		case SSI3:
			CLR_BIT(SSI3_module->SSICR1,SSI_CR1_SSE);
			if(copy_u8DataSize>=4 && copy_u8DataSize<=16)
			{
			    SSI3_module->SSICR0 |= (0xFF & copy_u8DataSize) ;
			}
			else
			{
				//<!TODO ERROR>
			}
			SET_BIT(SSI3_module->SSICR1,SSI_CR1_SSE);
		break ; 
	}
}

void SSI_voidEnableInt(SSI_Channel copy_SSIChennal ,Interrupt_Type copy_IntType)
{
	switch(copy_SSIChennal)
	{
		case SSI0: 
			switch(copy_IntType)
			{
				case Receive_Overrun_Interrupt : SET_BIT(SSI0_module->SSIIM , SSI_IM_RORIM); break ;
				case Receive_TimeOut_Interrupt : SET_BIT(SSI0_module->SSIIM , SSI_IM_RTIM); break ;
				case Receive_FIFO_Interrupt    : SET_BIT(SSI0_module->SSIIM , SSI_IM_RXIM); break ;
				case Transmit_FIFO_Interrupt   : SET_BIT(SSI0_module->SSIIM , SSI_IM_TXIM); break ;
				case All_Interrupts :			
					SET_BIT(SSI0_module->SSIIM , SSI_IM_RORIM);
					SET_BIT(SSI0_module->SSIIM , SSI_IM_RTIM);
					SET_BIT(SSI0_module->SSIIM , SSI_IM_RXIM);
					SET_BIT(SSI0_module->SSIIM , SSI_IM_TXIM);
				break ;
			}
			break;
		case SSI1:
			switch(copy_IntType)
			{
				case Receive_Overrun_Interrupt : SET_BIT(SSI1_module->SSIIM , SSI_IM_RORIM); break ;
				case Receive_TimeOut_Interrupt : SET_BIT(SSI1_module->SSIIM , SSI_IM_RTIM); break ;
				case Receive_FIFO_Interrupt    : SET_BIT(SSI1_module->SSIIM , SSI_IM_RXIM); break ;
				case Transmit_FIFO_Interrupt   : SET_BIT(SSI1_module->SSIIM , SSI_IM_TXIM); break ;
				case All_Interrupts :			
					SET_BIT(SSI1_module->SSIIM , SSI_IM_RORIM);
					SET_BIT(SSI1_module->SSIIM , SSI_IM_RTIM);
					SET_BIT(SSI1_module->SSIIM , SSI_IM_RXIM);
					SET_BIT(SSI1_module->SSIIM , SSI_IM_TXIM);
				break ;
			}
			break;
		case SSI2:
			switch(copy_IntType)
			{
				case Receive_Overrun_Interrupt : SET_BIT(SSI2_module->SSIIM , SSI_IM_RORIM); break ;
				case Receive_TimeOut_Interrupt : SET_BIT(SSI2_module->SSIIM , SSI_IM_RTIM); break ;
				case Receive_FIFO_Interrupt    : SET_BIT(SSI2_module->SSIIM , SSI_IM_RXIM); break ;
				case Transmit_FIFO_Interrupt   : SET_BIT(SSI2_module->SSIIM , SSI_IM_TXIM) ;break ;
				case All_Interrupts :			
					SET_BIT(SSI2_module->SSIIM , SSI_IM_RORIM);
					SET_BIT(SSI2_module->SSIIM , SSI_IM_RTIM);
					SET_BIT(SSI2_module->SSIIM , SSI_IM_RXIM);
					SET_BIT(SSI2_module->SSIIM , SSI_IM_TXIM);
				break ;
			}
			break;
		case SSI3:
			switch(copy_IntType)
			{
				case Receive_Overrun_Interrupt : SET_BIT(SSI3_module->SSIIM , SSI_IM_RORIM); break ;
				case Receive_TimeOut_Interrupt : SET_BIT(SSI3_module->SSIIM , SSI_IM_RTIM); break ;
				case Receive_FIFO_Interrupt    : SET_BIT(SSI3_module->SSIIM , SSI_IM_RXIM); break ;
				case Transmit_FIFO_Interrupt   : SET_BIT(SSI3_module->SSIIM , SSI_IM_TXIM); break ;
				case All_Interrupts :			
					SET_BIT(SSI3_module->SSIIM , SSI_IM_RORIM);
					SET_BIT(SSI3_module->SSIIM , SSI_IM_RTIM);
					SET_BIT(SSI3_module->SSIIM , SSI_IM_RXIM);
					SET_BIT(SSI3_module->SSIIM , SSI_IM_TXIM);
				break ;
			}
			break;
	}
}
void SSI_voidDisableInt(SSI_Channel copy_SSIChennal ,Interrupt_Type copy_IntType)
{
	switch(copy_SSIChennal)
	{
		case SSI0: 
			switch(copy_IntType)
			{
				case Receive_Overrun_Interrupt : CLR_BIT(SSI0_module->SSIIM , SSI_IM_RORIM); break ;
				case Receive_TimeOut_Interrupt : CLR_BIT(SSI0_module->SSIIM , SSI_IM_RTIM); break ;
				case Receive_FIFO_Interrupt    : CLR_BIT(SSI0_module->SSIIM , SSI_IM_RXIM); break ;
				case Transmit_FIFO_Interrupt   : CLR_BIT(SSI0_module->SSIIM , SSI_IM_TXIM) ;break ;
				case All_Interrupts :			
					CLR_BIT(SSI0_module->SSIIM , SSI_IM_RORIM);
					CLR_BIT(SSI0_module->SSIIM , SSI_IM_RTIM);
					CLR_BIT(SSI0_module->SSIIM , SSI_IM_RXIM);
					CLR_BIT(SSI0_module->SSIIM , SSI_IM_TXIM);
				break ;
			}
			break;
		case SSI1:
			switch(copy_IntType)
			{
				case Receive_Overrun_Interrupt : CLR_BIT(SSI1_module->SSIIM , SSI_IM_RORIM); break ;
				case Receive_TimeOut_Interrupt : CLR_BIT(SSI1_module->SSIIM , SSI_IM_RTIM); break ;
				case Receive_FIFO_Interrupt    : CLR_BIT(SSI1_module->SSIIM , SSI_IM_RXIM); break ;
				case Transmit_FIFO_Interrupt   : CLR_BIT(SSI1_module->SSIIM , SSI_IM_TXIM); break ;
				case All_Interrupts :			
					CLR_BIT(SSI1_module->SSIIM , SSI_IM_RORIM);
					CLR_BIT(SSI1_module->SSIIM , SSI_IM_RTIM);
					CLR_BIT(SSI1_module->SSIIM , SSI_IM_RXIM);
					CLR_BIT(SSI1_module->SSIIM , SSI_IM_TXIM);
				break ;
			}
			break;
		case SSI2:
			switch(copy_IntType)
			{
				case Receive_Overrun_Interrupt : CLR_BIT(SSI2_module->SSIIM , SSI_IM_RORIM); break ;
				case Receive_TimeOut_Interrupt : CLR_BIT(SSI2_module->SSIIM , SSI_IM_RTIM); break ;
				case Receive_FIFO_Interrupt    : CLR_BIT(SSI2_module->SSIIM , SSI_IM_RXIM); break ;
				case Transmit_FIFO_Interrupt   : CLR_BIT(SSI2_module->SSIIM , SSI_IM_TXIM); break ;
				case All_Interrupts :			
					CLR_BIT(SSI2_module->SSIIM , SSI_IM_RORIM);
					CLR_BIT(SSI2_module->SSIIM , SSI_IM_RTIM);
					CLR_BIT(SSI2_module->SSIIM , SSI_IM_RXIM);
					CLR_BIT(SSI2_module->SSIIM , SSI_IM_TXIM);
				break ;
			}
			break;
		case SSI3:
			switch(copy_IntType)
			{
				case Receive_Overrun_Interrupt : CLR_BIT(SSI3_module->SSIIM , SSI_IM_RORIM); break ;
				case Receive_TimeOut_Interrupt : CLR_BIT(SSI3_module->SSIIM , SSI_IM_RTIM); break ;
				case Receive_FIFO_Interrupt    : CLR_BIT(SSI3_module->SSIIM , SSI_IM_RXIM); break ;
				case Transmit_FIFO_Interrupt   : CLR_BIT(SSI3_module->SSIIM , SSI_IM_TXIM); break ;
				case All_Interrupts :			
					CLR_BIT(SSI3_module->SSIIM , SSI_IM_RORIM);
					CLR_BIT(SSI3_module->SSIIM , SSI_IM_RTIM);
					CLR_BIT(SSI3_module->SSIIM , SSI_IM_RXIM);
					CLR_BIT(SSI3_module->SSIIM , SSI_IM_TXIM);
				break ;
			}
			break;
	}
}
void SSI_voidTransmitSynch(SSI_Channel copy_SSIChennal ,u16 copy_u16DataBeTransmited)
{
	/*	Must Select the slave by making active-low slave select line low GPIOA->DATA 	*/
	switch(copy_SSIChennal)
	{
		case SSI0: 
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI0_module->SSISR);
			SSI0_module->SSIDR = (copy_u16DataBeTransmited);
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI0_module->SSISR);
			break ;
		case SSI1: 
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI1_module->SSISR);
			SSI1_module->SSIDR = (copy_u16DataBeTransmited);
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI1_module->SSISR);
			break ;
		case SSI2: 
			/*	Wait Until Buss Be IDLE	*/
			BUS_BUSY(SSI1_module->SSISR);
			SSI1_module->SSIDR = (copy_u16DataBeTransmited);
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI1_module->SSISR);
			break ;
		case SSI3:
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI3_module->SSISR);
			SSI3_module->SSIDR = (copy_u16DataBeTransmited);
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI2_module->SSISR);
			break ;
	}
	 // Must Deselect the slave  
}
void SSI_voidTransmitAsynch(SSI_Channel copy_SSIChennal ,u16 copy_u16DataBeTransmited,void(*callBack)(u8))
{
	global_u8TX_RX_State = 1 ; 

	/*	Must Select the slave by making active-low slave select line low GPIOA->DATA 	*/
	switch(copy_SSIChennal)
	{
		case SSI0: 
			Callback_TX_SSI0 = callBack ; 
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI0_module->SSISR);
			/*	Enable Transmit_FIFO_Interrupt	*/	
			SSI_voidEnableInt(SSI0,Transmit_FIFO_Interrupt);
			/*	Transmit DATA	*/
			SSI0_module->SSIDR = (copy_u16DataBeTransmited);
			break ;
		case SSI1:
			Callback_TX_SSI1 = callBack ; 
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI1_module->SSISR);
			/*	Enable Transmit_FIFO_Interrupt	*/	
			SSI_voidEnableInt(SSI1,Transmit_FIFO_Interrupt);
			/*	Transmit DATA	*/
			SSI1_module->SSIDR = (copy_u16DataBeTransmited);
		break ;
		case SSI2:
			Callback_TX_SSI2 = callBack ; 
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI2_module->SSISR);
			/*	Enable Transmit_FIFO_Interrupt	*/	
			SSI_voidEnableInt(SSI2,Transmit_FIFO_Interrupt);
			/*	Transmit DATA	*/
			SSI2_module->SSIDR = (copy_u16DataBeTransmited);
		break ;
		case SSI3:
			Callback_TX_SSI3 = callBack ; 
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI3_module->SSISR);
			/*	Enable Transmit_FIFO_Interrupt	*/	
			SSI_voidEnableInt(SSI3,Transmit_FIFO_Interrupt);
			/*	Transmit DATA	*/
			SSI3_module->SSIDR = (copy_u16DataBeTransmited);
			break ;
	}
	// Must Deselect the slave  	
}
u16 SSI_voidRecieveSynch(SSI_Channel copy_SSIChennal)
{
	u16 local_u16DataBeRecieved = 0 ; 
	switch(copy_SSIChennal)
	{
		case SSI0 : 
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI0_module->SSISR);
			local_u16DataBeRecieved = SSI0_module->SSIDR ; 
			break ; 
		case SSI1 : 
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI1_module->SSISR);
			local_u16DataBeRecieved = SSI1_module->SSIDR ; 
			break ; 
		case SSI2 :
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI2_module->SSISR);
			local_u16DataBeRecieved = SSI2_module->SSIDR ; 
			break ; 
		case SSI3 :
			/*	Wait Until Buss Be IDLE*/
			BUS_BUSY(SSI3_module->SSISR);
			local_u16DataBeRecieved = SSI3_module->SSIDR ; 
			break ; 
	}
	return local_u16DataBeRecieved; 
}
void __vector_7(void)
{	
	if(global_u8TX_RX_State == 1 )
	{
		// TRANSMIT
		Callback_TX_UART0();
		global_u8TX_RX_State=0; 
	}
	else if(global_u8TX_RX_State == 2 )
	{
		//RECIEVE
		
		global_u8TX_RX_State =0 ;
	}
	SET_BIT(SSI0_module->SSIICR , SSI_ICR_RTIC ) ;
	SET_BIT(SSI0_module->SSIICR , SSI_ICR_RORIC ) ;
}

