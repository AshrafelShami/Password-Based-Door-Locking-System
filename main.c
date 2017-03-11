/*		OS System Include Files			*/
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/queue.h"
#include "FreeRTOS/semphr.h"
#include "FreeRTOS/event_groups.h"

/*		Included Project Files			*/
#include "Prototypes/Password_Prototypes.h"
#include "Prototypes/Keypad_Prototypes.h"
#include "Prototypes/EEPROM_Prototypes.h"
#include "Prototypes/LCD_Prototypes.h"
#include "PW_Module/Password_Config.h"
#include "Menu_Module/Menu_Config.h"
#include "I2C/I2C_Config.h"
#include "RTC/RTC_Config.h"

/*      Tasks and functions declaration			*/
void T_Menu		( void * pvData );
void T_RTC		( void * pvData );
void T_EEPROM		( void * pvData );	

void System_Init	( void );

/*		Service declaration.			*/
xSemaphoreHandle	Save_In_EEPROM;

/*	 	  Global Variables			*/
extern u8 Password  [4];
extern u8 User_Login_Date[16];

int main(void){
	/*			System Initialization		*/
	System_Init();
	 
	/*	OS service Creation and initialization		*/
	vSemaphoreCreateBinary (Save_In_EEPROM, 0);
	
	/*	Tasks Creation	*/
	xTaskCreate (T_Menu	, NULL, 100, NULL, 1, NULL);
	xTaskCreate (T_RTC	, NULL, 100, NULL, 2, NULL);
	xTaskCreate (T_EEPROM	, NULL, 100, NULL, 3, NULL);
	
	/*	Start the OS	*/
	vTaskStartScheduler();
}

void T_Menu(void * pvData){
	u8 i ;
	while(1){
		i = Menu();
		switch(i){
			case 0: LCD_MENU_Start();	break;
			case 1: Password_Enter();
				User_Login();
				xSemaphoreGive
				(Save_In_EEPROM);	break;
			case 2: LCD_MENU_Time();	break;
			case 3: LCD_MENU_Date();	break;
			default:			break;
		}
	}
}

void T_RTC(void * pvData){
	while (1){
		RTC_Update();
		vTaskDelay(1000);
	}
}

void T_EEPROM(void * pvData){
	while (1){
		if(xSemaphoreTake(Save_In_EEPROM, 0xFFFF)){
			EEPROM_Write_String(User_Login_Date, 0x00);
		}
	}
}

void System_Init( void ){
	/*			LED pins Initialization			*/
	DDRB = (1 << 2)|(1 << 5);
	
	/*			LCD Initialization			*/
	LCD_Init(&PINC, &PINC, 2, 1, 0, 3, 4, 5, 6);
	
	/*			Keypad Initialization			*/
	Keypad_Init(&PINA, &PINA, 0, 1, 2, 3, 4, 5, 6, 7);
	
	/*			I2C Initialization			*/
	Struct_I2C I2C_Init_Struct;
	I2C_Init_Struct.SCL_Freq	=	SCL_100K;
	I2C_Init_Struct.Interrupt_Sel	=	Disable;
	I2C_Init(I2C_Init_Struct);
}
