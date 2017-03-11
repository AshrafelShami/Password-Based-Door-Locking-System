#include "RTC_Config.h"
#include "../I2C/I2C_Config.h"
#include "../Prototypes/LCD_Prototypes.h"

Struct_RTC_Data	RTC;
u8 RTC_Time [6]	= {0};
u8 RTC_Date [6]	= {0};

/********************************************************************************************
  Name:     RTC_Update.
  Purpose:  Function used to Data of the DS1307 (Time and Date)
  Entry:    no parameters.
  Exit:		no parameters.
********************************************************************************************/
void RTC_Update ( void ){
	u8 i = 0;
	RTC.Hours	= RTC_Read( HOURS_REGISTER	);
	RTC_Time[i]	= ((RTC.Hours >> 4) & 0x03) + '0';
	RTC_Time[i+1]	= (RTC.Hours & 0x0F)	    + '0';
	RTC.Minutes	= RTC_Read( MINUTES_REGISTER	);
	RTC_Time[i+2]   = (RTC.Minutes >> 4)        + '0';
	RTC_Time[i+3]	= (RTC.Minutes & 0x0F)      + '0';
	RTC.Seconds	= RTC_Read( SECONDS_REGISTER	);
	RTC_Time[i+4]	= (RTC.Seconds >> 4)        + '0';
	RTC_Time[i+5]	= (RTC.Seconds & 0x0F)      + '0';	

	RTC.Days	= RTC_Read( DAYS_REGISTER	);
	RTC_Date[i]	= ((RTC.Days >> 4) & 0x03)  + '0';
	RTC_Date[i+1]	= (RTC.Days  & 0x0F)	    + '0';
	RTC.Months	= RTC_Read( MONTHS_REGISTER	);
	RTC_Date[i+2]   = ((RTC.Months >> 4) & 0x01)+ '0';
	RTC_Date[i+3]	= (RTC.Months  & 0x0F)	    + '0';
	RTC.Years	= RTC_Read( YEARS_REGISTER	);
	RTC_Date[i+4]   = ((RTC.Years >> 4) & 0x0F) + '0';
	RTC_Date[i+5]	= (RTC.Years  & 0x0F)	    + '0';
}

/********************************************************************************************
  Name:     RTC_Read.
  Purpose:  Function used to Read from the DS1307 from a specific address location.
  Entry:    (u8 Register_Pointer) The address Location.
  Exit:		(return Data) Returns the Data in the specific location.
********************************************************************************************/
u8 RTC_Read( u8 Register_Pointer ){
	u8 Data = 0;
	I2C_Start_Condition();
	I2C_WriteTo_Address(DS1307);
	I2C_Write(Register_Pointer);
	I2C_Start_Condition();
	I2C_ReadFROM_Address(DS1307);
	Data = I2C_Read_With_ACK(0);
	I2C_Stop_Condition();
	return Data;
}

/********************************************************************************************
  Name:     RTC_Set_Time.
  Purpose:  Function used to Set the TIME of the RTC module.
  Entry:    (u8 Sec) Seconds.
			(u8 Min) Minutes.
			(u8 Hrs) Hours.
  Exit:		No parameters.
********************************************************************************************/
void RTC_Set_Time(u8 Sec, u8 Min, u8 Hrs){
	I2C_Start_Condition();
	I2C_WriteTo_Address(DS1307);
	I2C_WriteTo_Address(SECONDS_REGISTER);
	I2C_Write(Sec);
	I2C_Write(Min);
	I2C_Write(Hrs);
	I2C_Stop_Condition();
}

/********************************************************************************************
  Name:     RTC_Set_Date.
  Purpose:  Function used to Set the Date of the RTC module.
  Entry:    (u8 Day) Day.
			(u8 Mon) Month.
			(u8 Yrs) Year.
  Exit:		No parameters.
********************************************************************************************/
void RTC_Set_Date(u8 Day, u8 Mon, u8 Yrs){
	I2C_Start_Condition();
	I2C_WriteTo_Address(DS1307);
	I2C_WriteTo_Address(DAYS_REGISTER);
	I2C_Write(Day);
	I2C_Write(Mon);
	I2C_Write(Yrs);
	I2C_Stop_Condition();
}
