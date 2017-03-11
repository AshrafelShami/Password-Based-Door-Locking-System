
#ifndef FUNCTION_PROTOTYPES_H_
#define FUNCTION_PROTOTYPES_H_
#include "../Datatypes/DataTypes.h"

void I2C_Start_Condition ( void );
void I2C_Stop_Condition  ( void );

u8   I2C_Status( void );
void I2C_Address_Set( u8 Address );

void I2C_WriteTo_Address ( u8 Address );
void I2C_Write ( u8 Data );

void I2C_ReadFROM_Address ( u8 Address );
u8   I2C_Read ( void );
u8   I2C_Read_With_ACK ( u8 ACK );

void I2C_Restart( void );


#endif /* FUNCTION_PROTOTYPES_H_ */