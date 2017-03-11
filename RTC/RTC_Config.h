
#ifndef RTC_CONFIG_H_
#define RTC_CONFIG_H_

#include "../Prototypes/RTC_Prototypes.h"

#define DS1307				0xD0
#define SECONDS_REGISTER	0x00
#define MINUTES_REGISTER	0x01
#define HOURS_REGISTER		0x02
#define DAYOFWK_REGISTER	0x03
#define DAYS_REGISTER		0x04
#define MONTHS_REGISTER		0x05
#define YEARS_REGISTER		0x06
#define CONTROL_REGISTER	0x07

typedef struct{
	u8 Seconds;
	u8 Minutes;
	u8 Hours;
	u8 Days;
	u8 Months;
	u8 Years;
	}Struct_RTC_Data;

#endif /* RTC_CONFIG_H_ */