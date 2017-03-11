
#ifndef RTC_PROTOTYPES_H_
#define RTC_PROTOTYPES_H_

#include "../Datatypes/DataTypes.h"

u8 RTC_Read		( u8 Register_Pointer );
void RTC_Update		( void );
void RTC_Set_Time	( u8 Sec, u8 Min, u8 Hrs );
void RTC_Set_Date	( u8 Day, u8 Mon, u8 Yrs );

#endif /* RTC_PROTOTYPES_H_ */
