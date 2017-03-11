
#ifndef EEPROM_PROTOTYPES_H_
#define EEPROM_PROTOTYPES_H_
#include "../Datatypes/DataTypes.h"

u8	EEPROM_Read	    ( u8 Memory_Address );
u8	EEPROM_Write	    ( u8 Data, u8 Memory_Address );
u8	EEPROM_Write_String ( u8 * Data, u8 Memory_Address );

#endif /* EEPROM_PROTOTYPES_H_ */
