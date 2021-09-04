#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C_interface.h"

int main(void)
{
    /*  FOR I2C ONLY    */
    I2C_voidInit(I2C0, Master_Transmit,Standard,0x05) ;
    I2C_voidMasterEnable(I2C0);
    I2C_voidMaterTransmitMassege(I2C0,'a');
	while(1)
	{
		

	}
}
