/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 2 September 2020                                                   */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"



#define BUS_BUSY(I2Cx)	while((GET_BIT(I2Cx,I2C_MCS_BUSBSY)) == 1){}


void I2C_voidInit(I2C_Chennal copy_I2CChennalSelect, I2C_Mode copy_I2CModeSelect,Transmission_speeds copy_I2CSpeed,u8 copy_u8SalveAddress)
{
	
	switch(copy_I2CChennalSelect)
	{
		case I2C0 : 
			//calculate the SCL period
			switch(copy_I2CSpeed)
			{
				case Standard : 
					CLR_BIT(I2C0_I2CMTPR,7);
					CLR_BIT(I2C0_I2CMCS,I2C_MCS_HS);
					I2C0_I2CMTPR = TPR_EQN(Standard_speed) ;
					
					break ; 
				case Fast_Mode : 
					CLR_BIT(I2C0_I2CMTPR,7);
					CLR_BIT(I2C0_I2CMCS,I2C_MCS_HS);
					I2C0_I2CMTPR = TPR_EQN(FastMode_speed) ;
					break;
				case Fast_Mode_Plus : 
					CLR_BIT(I2C0_I2CMTPR,7);
					CLR_BIT(I2C0_I2CMCS,I2C_MCS_HS);
					I2C0_I2CMTPR = TPR_EQN(FastMode_Plus_speed) ;
					break;
				case High_Speed_Mode : 
					SET_BIT(I2C0_I2CMTPR,7);
					SET_BIT(I2C0_I2CMCS,I2C_MCS_HS);
					I2C0_I2CMTPR = TPR_EQN(High_speed) ;
					break;
			}

			switch(copy_I2CModeSelect)
			{
				case Master_Transmit : 
					ENABLE_MASTER; 
					DISABLE_SLAVE;
					// Mode select.
					#if I2C0_GLITCH_FILTER == ENABLE
						SET_BIT(I2C0_I2CMCR,I2C_MCR_GFE);
					#else
						CLR_BIT(I2C0_I2CMCR,I2C_MCR_GFE);
					#endif
					//write slave addresse 7bit and R/W bit.
					I2C0_I2CMSA = (copy_u8SalveAddress << 1 );
					//data byte is acknowledged automatically
					SET_BIT(I2C0_I2CMCS,I2C_MCS_ACK);
					CLR_BIT(I2C0_I2CMSA,I2C_MSA_R_S);	//AS TX	

				break ; 
				case Master_Receive : 
					ENABLE_MASTER; 
					DISABLE_SLAVE;
					// Mode select.
					#if I2C0_GLITCH_FILTER == ENABLE
						SET_BIT(I2C0_I2CMCR,I2C_MCR_GFE);
					#else
						CLR_BIT(I2C0_I2CMCR,I2C_MCR_GFE);
					#endif
					//write slave addresse 7bit and R/W bit.
					I2C0_I2CMSA = (copy_u8SalveAddress << 1 );
					//data byte is acknowledged automatically
					SET_BIT(I2C0_I2CMCS,I2C_MCS_ACK);					
					SET_BIT(I2C0_I2CMSA,I2C_MSA_R_S);	//AS RX	
				break ; 
				case Slave_Transmit :
					DISABLE_MASTER; 
					ENABLE_SLAVE;
					//	Set slave addresse
						I2C0_I2CSOAR = copy_u8SalveAddress ; 
					/*	enable slave operation */
					SET_BIT(I2C0_I2CSCSR,0);
				break ; 
				case Slave_Receive : 
					DISABLE_MASTER; 
					ENABLE_SLAVE;
					//	Set slave addresse
					I2C0_I2CSOAR = copy_u8SalveAddress ; 
					/*	enable slave operation */
					SET_BIT(I2C0_I2CSCSR,0);
					break ; 
			}
			break ;
		case I2C1 : 
			switch(copy_I2CModeSelect)
			{
				case Master_Transmit : break ; 
				case Master_Receive : break ; 
				case Slave_Transmit : break ; 
				case Slave_Receive : break ; 
			}
			break ;
		case I2C2 :
			switch(copy_I2CModeSelect)
			{
				case Master_Transmit : break ; 
				case Master_Receive : break ; 
				case Slave_Transmit : break ; 
				case Slave_Receive : break ; 
			}
			break ;
		case I2C3 :
			switch(copy_I2CModeSelect)
			{
				case Master_Transmit : break ; 
				case Master_Receive : break ; 
				case Slave_Transmit : break ; 
				case Slave_Receive : break ; 
			}
			break ;
	}
	
}
void I2C_voidDisableSlaveOperation(I2C_Chennal copy_I2CChennalSelect)
{
		switch(copy_I2CChennalSelect)
		{
			case I2C0 : 
				CLR_BIT(I2C0_I2CSCSR,0);
				break ; 
			case I2C1 : break ; 
			case I2C2 : break ; 
			case I2C3 : break ; 
		}
}
void I2C_voidEnableSlaveOperation(I2C_Chennal copy_I2CChennalSelect)
{
		switch(copy_I2CChennalSelect)
		{
			case I2C0 : 
				SET_BIT(I2C0_I2CSCSR,0);
				break ; 
			case I2C1 : break ; 
			case I2C2 : break ; 
			case I2C3 : break ; 
		}
}
void I2C_voidMasterEnable(I2C_Chennal copy_I2CChennalSelect)
{
	switch(copy_I2CChennalSelect)
	{
		case I2C0: 
			//Set RUN bit to make MASTER TX and RX.
			SET_BIT(I2C0_I2CMCS,I2C_MCS_RUN);
			break ; 
		case I2C1: break ; 
		case I2C2: break ; 
		case I2C3: break ; 
	}
}
void I2C_voidMasterDisable(I2C_Chennal copy_I2CChennalSelect)
{
	switch(copy_I2CChennalSelect)
	{
		case I2C0: 
		SET_BIT(I2C0_I2CMCS,I2C_MCS_STOP) ;
			break ; 
		case I2C1: break ; 
		case I2C2: break ; 
		case I2C3: break ; 
	}
}

void I2C_voidMaterTransmitMassege(I2C_Chennal copy_I2CChennalSelect, u8 copy_u8Data)
{
    switch (copy_I2CChennalSelect)
    {
    case I2C0:
        I2C0_I2CMDR = copy_u8Data ;
        //Start Condition
        SET_BIT(I2C0_I2CMCS,I2C_MCS_START);
        //Set RUN bit to make MASTER TX and RX.
        SET_BIT(I2C0_I2CMCS,I2C_MCS_RUN);
        // Polling
        BUS_BUSY(I2C0_I2CMCS);
        //Error Detection
        if(GET_BIT(I2C0_I2CMCS,I2C_MCS_ERROR))
        {
            //<!TODO ERROR STATE>
            // return error
        }
        break ;
    case I2C1:break ;
    case I2C2:break ;
    case I2C3:break ;
    }

}
void I2C_voidSlaveTransmitMassege(I2C_Chennal copy_I2CChennalSelect, u8 copy_u8Data)
{
    switch (copy_I2CChennalSelect)
    {
    case I2C0:
        I2C0_I2CMDR = copy_u8Data ;
		//Polling
		while(GET_BIT(I2C0_I2CSCSR,1) == 1 ); //RECIEVE DATA
        break ;
    case I2C1:break ;
    case I2C2:break ;
    case I2C3:break ;
    }

}
u8 I2C_voidMaterRecieveMassege(I2C_Chennal copy_I2CChennalSelect)
{
	u8 Data = 0 ;
	switch(copy_I2CChennalSelect)
	{
		case I2C0: 
		//Start Condition
		SET_BIT(I2C0_I2CMCS,I2C_MCS_START);
		//Set RUN bit to make MASTER TX and RX.
		SET_BIT(I2C0_I2CMCS,I2C_MCS_RUN);
		//CLR STOP
		CLR_BIT(I2C0_I2CMCS,I2C_MCS_STOP) ;
		//Polling
		BUS_BUSY(I2C0_I2CMCS);
		//Error Detection 
		if(GET_BIT(I2C0_I2CMCS,I2C_MCS_ERROR))
		{
			//<!TODO ERROR STATE>	
			// return error
		}
		Data = I2C0_I2CMDR ; 
		break ;
		case I2C1: break ;
		case I2C2: break ;
		case I2C3: break ;
	}	
	return Data ; 
}
u8 I2C_voidSlaveRecieveMassege(I2C_Chennal copy_I2CChennalSelect)
{
	u8 Data = 0 ;
	switch(copy_I2CChennalSelect)
	{
		case I2C0: 

		//Polling
		while(GET_BIT(I2C0_I2CSCSR,0) == 1 ); //RECIEVE DATA
		Data = I2C0_I2CMDR ; 
		break ;
		case I2C1: break ;
		case I2C2: break ;
		case I2C3: break ;
	}	
	return Data ; 
}
