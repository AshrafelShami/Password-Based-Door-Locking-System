#include "EEPROM_Config.h"
#include "../Prototypes/I2C_Prototypes.h"

/********************************************************************************************
  Name:     EEPROM_Read.
  Purpose:  Function to read from the EEPROM.
  Entry:    (u8 Memory_Address) The Address to read from it.
  Exit:     (return Data)		Returns the Data in the Memory_Address.
********************************************************************************************/
u8 EEPROM_Read( u8 Memory_Address ){
	u8 Data = 0;
	I2C_Start_Condition();
	if(I2C_Status() != 0x08)	/*0x08*/	/*	A START condition has been transmitted		*/
		return ERROR;
	
	I2C_WriteTo_Address(EEPROM_Address);		/*	Address of the device 1010 000 + 0 to write.	*/
	if(I2C_Status() != 0x18)	/*0x18*/	/*	SLA+W has been TX; ACK has been received	*/
		return ERROR;
	
	I2C_Write(Memory_Address);			/*	&Memory_ADDRESS inside the EEPROM		*/
	if(I2C_Status() != 0x28)	/*0x28*/	/*	Data byte has been TX; ACK has been received	*/
		return ERROR;
	
	I2C_Start_Condition();
	if (I2C_Status() != 0x10)	/*0x10*/	/*	repeated START condition has been transmitted	*/
		return ERROR;
	
	I2C_ReadFROM_Address(EEPROM_Address);		/*	Address of the device 1010 000 + 1 to Read.	*/
	if (I2C_Status() != 0x40)	/*0x40*/	/*	SLA+R has been TX; ACK has been received	*/
		return ERROR;
	
	Data = I2C_Read_With_ACK (0);			/*	Read with no ACK								*/
	if (I2C_Status() != 0x58)	/*0x58*/	/*	Data byte has been RX;	NOT ACK has been RX	*/
		return ERROR;
	
	I2C_Stop_Condition();
	_delay_ms(2);
	return Data;
}

/********************************************************************************************
  Name:     EEPROM_Write.
  Purpose:  Function used to write data to the EEPROM in a specific address.
  Entry:    (u8 Memory_Address) The Address that will hold the Data.
			(u8 Data)			The Data that will be stored in the Memory_Address.
********************************************************************************************/
u8 EEPROM_Write ( u8 Data, u8 Memory_Address ){
	
	I2C_Start_Condition();
	if(I2C_Status() != 0x08)	/*0x08*/	/*	A START condition has been transmitted		*/
		return ERROR;
	
	I2C_WriteTo_Address(EEPROM_Address);		/*	Address of the device 1010 000 + 0 to write.	*/
	if(I2C_Status() != 0x18)	/*0x18*/	/*	SLA+W has been TX; ACK has been received	*/
		return ERROR;
		
	I2C_Write(Memory_Address);			/*	&Memory_ADDRESS inside the EEPROM		*/
	if(I2C_Status() != 0x28)	/*0x28*/	/*	Data byte has been TX; ACK has been received	*/
		return ERROR;

	I2C_Write(Data);				/*	The Data to be written in the &Memory_ADDRESS	*/
	if(I2C_Status() != 0x28)	/*0x28*/	/*	Data byte has been TX; ACK has been received	*/
		return ERROR;

	I2C_Stop_Condition();
	_delay_ms(2);
	return SUCCESS;	
}

u8 EEPROM_Write_String ( u8 * Data, u8 Memory_Address ){
	u8 i = 0;
	
	I2C_Start_Condition();
	if(I2C_Status() != 0x08)	/*0x08*/	/*	A START condition has been transmitted		*/
	return ERROR;
	
	I2C_WriteTo_Address(EEPROM_Address);		/*	Address of the device 1010 000 + 0 to write.	*/
	if(I2C_Status() != 0x18)	/*0x18*/	/*	SLA+W has been TX; ACK has been received	*/
	return ERROR;
	
	I2C_Write(Memory_Address++);			/*	&Memory_ADDRESS inside the EEPROM		*/
	if(I2C_Status() != 0x28)	/*0x28*/	/*	Data byte has been TX; ACK has been received	*/
	return ERROR;

	while(Data[i] != '\0')
	I2C_Write(Data[i++]);				/*	The Data to be written in the &Memory_ADDRESS	*/
	if(I2C_Status() != 0x28)	/*0x28*/	/*	Data byte has been TX; ACK has been received	*/
	return ERROR;

	I2C_Stop_Condition();
	_delay_ms(2);
	return SUCCESS;
}
