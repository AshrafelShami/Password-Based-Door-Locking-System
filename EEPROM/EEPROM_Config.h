
#ifndef EEPROM_CONFIG_H_
#define EEPROM_CONFIG_H_

#include "../Prototypes/EEPROM_Prototypes.h"

#define F_CPU 16000000UL
#include <util/delay.h>

#define EEPROM_Address	0xA0

#define ERROR	0
#define SUCCESS	1

#endif /* EEPROM_CONFIG_H_ */