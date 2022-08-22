/**
 * 
 * @file LCD.h
 * @author Ahmed Elgharib
 * @date 2021-08-20
 * 
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


#define LCD_RS_PIN          PIN5
#define LCD_RS_PORT         PORT_D
#define LCD_RW_PIN			PIN6
#define LCD_RW_PORT			PORT_D
#define LCD_E_PIN           PIN7
#define LCD_E_PORT          PORT_D

#define LCD_4BITS_PIN1      PIN4
#define LCD_4BITS_PIN2      PIN5
#define LCD_4BITS_PIN3      PIN6
#define LCD_4BITS_PIN4      PIN7


#define LCD_4BITS_PORT            PORT_C
#define LCD_8BITS_DATA_PORT       PORT_C


#define LCD_8BITS_MODE       0
#define LCD_4BITS_MODE       1

/* LCD_4BITS_MODE - LCD_8BITS_MODE */
#define LCD_CURRENT_MODE     LCD_4BITS_MODE

#define ROW       0
#define COL       0


#define LCD_COM_CLEAR					(uint8_t)(0x01)
#define LCD_COM_HOME					(uint8_t)(0x02)
#define LCD_COM_ENTRYMODE				(uint8_t)(0x06)
#define LCD_COM_DISPLAY_OFF				(uint8_t)(0x08)
#define LCD_COM_DISPLAY_ON				(uint8_t)(0x0C)
#define LCD_COM_DISPLAY_ON_CURSOR_BLINK	(uint8_t)(0x0D)
#define LCD_COM_CURSOR_SHIFT_LEFT		(uint8_t)(0x10)
#define LCD_COM_CURSOR_SHIFT_RIGHT		(uint8_t)(0x14)
#define LCD_COM_DISPLAY_SHIFT_LEFT		(uint8_t)(0x18)
#define LCD_COM_DISPLAY_SHIFT_RIGHT		(uint8_t)(0x1C)
#define LCD_COM_FUNCTION_RESET			(uint8_t)(0x30)
#define LCD_COM_FUNCTION_SET_8BIT		(uint8_t)(0x38)
#define LCD_COM_SET_CURSOR_FIRST_LINE	(uint8_t)(0x80)
#define LCD_COM_SET_CURSOR_SECOND_LINE	(uint8_t)(0xc0)
#define LCD_FIRST_LINE_BASE_ADDRESS		(uint8_t)(0x00)
#define LCD_SECOND_LINE_BASE_ADDRESS	(uint8_t)(0x40)
#define TWO_LINE_LCD_Four_BIT_MODE      (uint8_t)(0x28)
#define LCD_MAX_CHAR_PER_LINE			(uint8_t)(16)
#define Eight_Bit_Mode 					(uint8_t)(0)
#define Four_Bit_Mode 					(uint8_t)(0x02)
#define LCD_MAX_ASCII_CODE 				(uint8_t)(127)
#define CURSOR_ON                       (uint8_t)(0x0E)

#endif /* LCD_CONFIG_H_ */