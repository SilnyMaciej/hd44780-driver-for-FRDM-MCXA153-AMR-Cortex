/*
 * hd44780_no_RW.h
 *
 *  Created on: 11 maj 2026
 *      Author: silnymaciej
 */

#ifndef HD44780_NO_RW_H_
#define HD44780_NO_RW_H_

#include "board.h"
#include "pin_mux.h"
#include "delay_us.h"
#include <stdlib.h>

/*
 *
 * Choose mode for your LCD configuration
 *
 *
 */


#define LCD_MODE_4_BIT
//#define LCD_MODE_8_BIT




/*
 *
 *
 *
 * Ports definitions
 *
 *
 */

#define RS_GPIO					BOARD_INIT_4BITMODE_2X16_LCD_RS_GPIO

#define RS_PIN_MASK 					BOARD_INIT_4BITMODE_2X16_LCD_RS_GPIO_PIN_MASK

#define E_GPIO					BOARD_INIT_4BITMODE_2X16_LCD_E_GPIO

#define E_PIN_MASK  				BOARD_INIT_4BITMODE_2X16_LCD_E_GPIO_PIN_MASK

#ifdef LCD_MODE_8_BIT
	#define D0_GPIO

	#define D1_GPIO

	#define D2_GPIO

	#define D3_GPIO
#endif


#define D4_GPIO				BOARD_INIT_4BITMODE_2X16_LCD_D4_GPIO

#define D4_PIN_MASK				BOARD_INIT_4BITMODE_2X16_LCD_D4_GPIO_PIN_MASK

#define D5_GPIO        		BOARD_INIT_4BITMODE_2X16_LCD_D5_GPIO

#define D5_PIN_MASK				BOARD_INIT_4BITMODE_2X16_LCD_D5_GPIO_PIN_MASK

#define D6_GPIO				BOARD_INIT_4BITMODE_2X16_LCD_D6_GPIO

#define D6_PIN_MASK				BOARD_INIT_4BITMODE_2X16_LCD_D6_GPIO_PIN_MASK

#define D7_GPIO				BOARD_INIT_4BITMODE_2X16_LCD_D7_GPIO

#define D7_PIN_MASK     		BOARD_INIT_4BITMODE_2X16_LCD_D7_GPIO_PIN_MASK

/*
 *
 * Available functions for user
 *
 *
 */


void LCD_Init(void); // Initialize LCD (4 bit mode, or 8 bit mode)
void LCD_Set_Position(uint8_t row, uint8_t column); // Setting position of cursor on LCD
void LCD_Send_Data(const char* buffer); // Sending string or char data to the LCD
void LCD_Clear(void); // Clearing LCD screen and going to the '0,0' position (clearing command takes 2ms)
void LCD_Send_Int(int val); // Sending converted integer value to the char tab and displaying on LCD



#endif /* HD44780_NO_RW_H_ */
