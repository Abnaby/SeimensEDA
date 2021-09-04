/*********************************************************************************/
/* Author    : Mohamed Abd El-Naby                                               */
/* Version   : V01                                                               */
/* Date      : 2 September 2020                                                   */
/*********************************************************************************/

#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H
	
typedef enum
{
	I2C0,
	I2C1,
	I2C2,
	I2C3
}I2C_Chennal;

typedef enum
{
	Master_Transmit,
	Master_Receive,
	Slave_Transmit,
	Slave_Receive
}I2C_Mode;

typedef enum 
{
	Standard,
	Fast_Mode,
	Fast_Mode_Plus,
	High_Speed_Mode
}Transmission_speeds;




		/*			PUBLIC FUNCTIONS  					*/	

void I2C_voidInit(I2C_Chennal copy_I2CChennalSelect, I2C_Mode copy_I2CModeSelect,Transmission_speeds copy_I2CSpeed,u8 copy_u8SalveAddress);
void I2C_voidMasterEnable(I2C_Chennal copy_I2CChennalSelect);
void I2C_voidMasterDisable(I2C_Chennal copy_I2CChennalSelect);
void I2C_voidMaterTransmitMassege(I2C_Chennal copy_I2CChennalSelect, u8 copy_u8Data);
u8 I2C_voidMaterRecieveMassege(I2C_Chennal copy_I2CChennalSelect);
void I2C_voidSlaveTransmitMassege(I2C_Chennal copy_I2CChennalSelect, u8 copy_u8Data);
u8 I2C_voidSlaveRecieveMassege(I2C_Chennal copy_I2CChennalSelect);

#endif
