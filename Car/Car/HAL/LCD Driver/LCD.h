/**
 * 
 * @file LCD.h
 * @author Ahmed Elgharib
 * @date 2021-08-20
 * 
 */

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 8000000UL
#include "../../Utilites/DataTypes.h"
#include "../../Utilites/BitMath.h"
#include "../../Utilites/Memmap.h"
#include "../../MCAL/DIO Driver/DIO.h"
#include "LCD_cnfg.h"
#include <util/delay.h>

void LCD_Init(void);
void LCD_sendCommand(u8_t command);
void LCD_writeData(u8_t data);
void LCD_writeChar(u8_t ch);
void LCD_writeString(u8_t *str);
void LCD_writeNumber(u64_t num);
void LCD_GOTO(u8_t raw, u8_t col);

#endif