/*
 * hd44780_no_RW.c
 *
 *  Created on: 11 maj 2026
 *      Author: silnymaciej
 */

#include "hd44780_no_RW.h"
#include <stdlib.h>

#ifdef LCD_MODE_4_BIT
	static void LCD_Send_4_Bits(uint8_t data, bool mode);

#elif defined(LCD_MODE_8_BIT)
	static void LCD_Send_8_Bits(uint8_t data, bool flag);
#endif

static void LCD_Send_Command(uint8_t command);
static inline void LCD_Enable_Up(void);
static inline void LCD_Enable_Down(void);
static inline void LCD_RS_Mode_Write_Data(void);
static inline void LCD_RS_Mode_Send_Data(void);





#ifdef LCD_MODE_4_BIT
	static void LCD_Send_4_Bits(uint8_t data, bool flag){

		if(flag) LCD_RS_Mode_Write_Data();
		else LCD_RS_Mode_Send_Data();

		delay_us(1U); // Time for LCD processor

		LCD_Enable_Up(); // Setting enable pulse up

		/*
		 *
		 * If is 'data', pin go to 'write 1' mode
		 *
		 */


		if((data) & 0x1) 	  D4_GPIO -> PSOR = D4_PIN_MASK;
		if((data >> 1) & 0x1) D5_GPIO -> PSOR = D5_PIN_MASK;
		if((data >> 2) & 0x1) D6_GPIO -> PSOR = D6_PIN_MASK;
		if((data >> 3) & 0x1) D7_GPIO -> PSOR = D7_PIN_MASK;
		delay_us(1U);

		LCD_Enable_Down(); // Setting enable pulse down

		/*
		 *
		 * Setting the all 4 pins to 'write 0' mode
		 *
		 */

		D4_GPIO->PCOR = D4_PIN_MASK;
		D5_GPIO->PCOR = D5_PIN_MASK;
		D6_GPIO->PCOR = D6_PIN_MASK;
		D7_GPIO->PCOR = D7_PIN_MASK;



		RS_GPIO->PCOR = RS_PIN_MASK; // Setting RS pin to 'write 0' mode
	}

#elif defined(LCD_MODE_8_BIT)
	static void LCD_Send_8_Bits(uint8_t data, bool flag){

			if(flag) LCD_RS_Mode_Write_Data();
			else LCD_RS_Mode_Send_Data();
			delay_us(1U);

			LCD_Enable_Up();

			if((data) & 0x1) 	  D0_GPIO -> PSOR = D0_PIN_MASK;
			if((data >> 1) & 0x1) D1_GPIO -> PSOR = D1_PIN_MASK;
			if((data >> 2) & 0x1) D2_GPIO -> PSOR = D2_PIN_MASK;
			if((data >> 3) & 0x1) D3_GPIO -> PSOR = D3_PIN_MASK;

			if((data >> 4) & 0x1) D4_GPIO -> PSOR = D4_PIN_MASK;
			if((data >> 5) & 0x1) D5_GPIO -> PSOR = D5_PIN_MASK;
			if((data >> 6) & 0x1) D6_GPIO -> PSOR = D6_PIN_MASK;
			if((data >> 7) & 0x1) D7_GPIO -> PSOR = D7_PIN_MASK;
			delay_us(1U);

			LCD_Enable_Down();

			D0_GPIO->PCOR = D0_PIN_MASK;
			D1_GPIO->PCOR = D1_PIN_MASK;
			D2_GPIO->PCOR = D2_PIN_MASK;
			D3_GPIO->PCOR = D3_PIN_MASK;
			D4_GPIO->PCOR = D4_PIN_MASK;
			D5_GPIO->PCOR = D5_PIN_MASK;
			D6_GPIO->PCOR = D6_PIN_MASK;
			D7_GPIO->PCOR = D7_PIN_MASK;

			RS_GPIO->PCOR = RS_PIN_MASK;
		}

#endif




void LCD_Init(){
	delay_us(18000);

	#ifdef LCD_MODE_4_BIT

	BOARD_Init_4bitMode_2x16_lcd(); // Your functional group can be different than than default. If it is, you must change it
	delay_us(1);

	LCD_Send_4_Bits(0x3, 0);
	delay_us(5000);

	LCD_Send_4_Bits(0x3, 0);
	delay_us(100);

	LCD_Send_4_Bits(0x3, 0);
	delay_us(45);
	LCD_Send_4_Bits(0x2, 0);  // 4 Bit Mode
	delay_us(45);
	LCD_Send_Command(0x28);

	#elif defined(LCD_MODE_8_BIT)


		delay_us(1);

		LCD_Send_8_Bits(0x30, 0);
		delay_us(5000);

		LCD_Send_8_Bits(0x30, 0);
		delay_us(100);

		LCD_Send_8_Bits(0x30, 0);
		delay_us(45);
		LCD_Send_8_Bits(0x38, 0); // 8 Bit Mode
		delay_us(45);
	#endif

	LCD_Send_Command(0x0F); // Display On, Cursor On, Blinking On
	LCD_Clear();
}


void LCD_Set_Position(uint8_t row, uint8_t column){
	if(column < 16 && row < 2){
		uint8_t adress = row == 0 ? (0x00 + column) : (0x40 + column); // 0x00 is a first start DDRAM address row. 0x40 is a second start DDRAM address row
		LCD_Send_Command(0x80 | adress); // 0x80 is a DDRAM address
	}

}


void LCD_Send_Data(const char* buffer){

	for(; *buffer != '\0'; buffer++){

		#ifdef LCD_MODE_4_BIT
			LCD_Send_4_Bits((*buffer >> 4) & 0x0F, 1); // First, send the MSB nibble
			LCD_Send_4_Bits((*buffer) & 0x0F,1);       // Second, send the LSB nibble

		#elif defined(LCD_MODE_8_BIT)

			LCD_Send_8_Bits((uint8_t)*buffer, 1);

		#endif

		delay_us(43U); // RS and Data Setup Time (min. 40-80ns)
	}
}



void LCD_Send_Int(int val){

	char buffer[12]; 		// buffer for 32 bit integer
	itoa(val, buffer, 10); // transforming integer to the string

	LCD_Send_Data(buffer); // sending the 'string integer' data
}


void LCD_Clear(void){
	LCD_Send_Command(0x01); // Clear command
	delay_us(2000);
}


/*
 *
 *
 * Helper Functions
 *
 *
 */

static void LCD_Send_Command(uint8_t command){

	#ifdef LCD_MODE_4_BIT
			LCD_Send_4_Bits((command >> 4) & 0x0F, 0); // First data is MSB bits
			LCD_Send_4_Bits((command) & 0x0F,0);       // Second data is a LSB bits
	#elif defined(LCD_MODE_8_BIT)

			LCD_Send_8_Bits((uint8_t)command, 0);
	#endif
			delay_us(43U);
}



static inline void LCD_Enable_Up(void){ E_GPIO->PSOR = E_PIN_MASK; } // EN /  E pin set UP



static inline void LCD_Enable_Down(void){ E_GPIO->PCOR = E_PIN_MASK; } // EN /  E pin set Down



static inline void LCD_RS_Mode_Write_Data(void){ RS_GPIO->PSOR = RS_PIN_MASK; } // Set RS to high for write mode



static inline void LCD_RS_Mode_Send_Data(void){ RS_GPIO->PCOR = RS_PIN_MASK; } // Set RS to low for command mode
