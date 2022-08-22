/**
 *
 * @file LCD.c
 * @author Ahmed Elgharib
 * @date 2021-08-20
 *
 */

#include "LCD.h"



#if (LCD_CURRENT_MODE == LCD_8BITS_MODE)
void LCD_Init(void)
{
    _delay_ms(50);
    LCD_sendCommand(LCD_COM_FUNCTION_SET_8BIT);
    _delay_ms(1);
    LCD_sendCommand(CURSOR_ON);
    _delay_ms(1);
    LCD_sendCommand(LCD_COM_CLEAR);
    _delay_ms(2);
    LCD_sendCommand(LCD_COM_ENTRYMODE);
    _delay_ms(1);
}

static void LCD_sendCommand(u8_t command)
{
    DIO_setPin(LCD_RS_PORT, LCD_RS_PIN, LOW);
    DIO_setPin(LCD_RW_PORT, LCD_RW_PIN, LOW);
    DIO_voidSetPortValue(LCD_8BITS_DATA_PORT, command);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);
}

static void LCD_writeData(u8_t data)
{
    DIO_setPin(LCD_RS_PORT, LCD_RS_PIN, HIGH);
    DIO_setPin(LCD_RW_PORT, LCD_RW_PIN, LOW);
    DIO_voidSetPortValue(LCD_8BITS_DATA_PORT, data);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);
}








#elif (LCD_CURRENT_MODE == LCD_4BITS_MODE)

void LCD_Init(void)
{
    _delay_ms(50);
    LCD_sendCommand(LCD_COM_HOME);
    _delay_ms(1);
    LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
    _delay_ms(1);
    LCD_sendCommand(CURSOR_ON);
    _delay_ms(1);
    LCD_sendCommand(LCD_COM_CLEAR);
    _delay_ms(2);
    LCD_sendCommand(LCD_COM_ENTRYMODE);
    _delay_ms(1);
}

 void LCD_sendCommand(u8_t command)
{
    DIO_setPin(LCD_RS_PORT, LCD_RS_PIN, LOW);
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN1, GET_BIT(command, 4));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN2, GET_BIT(command, 5));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN3, GET_BIT(command, 6));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN4, GET_BIT(command, 7));

    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);

    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN1, GET_BIT(command, 0));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN2, GET_BIT(command, 1));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN3, GET_BIT(command, 2));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN4, GET_BIT(command, 3));

    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);
}

 void LCD_writeData(u8_t data)
{
    DIO_setPin(LCD_RS_PORT, LCD_RS_PIN, HIGH);
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN1, GET_BIT(data, 4));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN2, GET_BIT(data, 5));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN3, GET_BIT(data, 6));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN4, GET_BIT(data, 7));

    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);

    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN1, GET_BIT(data, 0));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN2, GET_BIT(data, 1));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN3, GET_BIT(data, 2));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN4, GET_BIT(data, 3));

    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);
}
#endif

void LCD_writeChar(u8_t ch)
{
    LCD_writeData(ch);
}

void LCD_writeString(u8_t *str)
{
    u8_t counter = 0;
    while (str[counter] != '\0')
    {
        LCD_writeChar(str[counter]);
        counter++;
    }
}

void LCD_writeNumber(u64_t num)
{
    if (num == 0)
    {
        LCD_writeChar('0');
    }
    s8_t i = 0;
    uint8_t str_num[5];
    while (num > 0)
    {
        str_num[i] = num % 10;
        num /= 10;
        i++;
    }
    i--;
    while (i >= 0)
    {
        switch (str_num[i])
        {
        case 0:
            LCD_writeChar('0');
            break;
        case 1:
            LCD_writeChar('1');
            break;
        case 2:
            LCD_writeChar('2');
            break;
        case 3:
            LCD_writeChar('3');
            break;
        case 4:
            LCD_writeChar('4');
            break;
        case 5:
            LCD_writeChar('5');
            break;
        case 6:
            LCD_writeChar('6');
            break;
        case 7:
            LCD_writeChar('7');
            break;
        case 8:
            LCD_writeChar('8');
            break;
        case 9:
            LCD_writeChar('9');
            break;
        }

        i--;
    }
}

void LCD_GOTO(u8_t raw, u8_t col)
{
    switch (raw)
	{
	case 0:
		if ((col < 16) && (col >= 0))
		{
			LCD_sendCommand(LCD_COM_SET_CURSOR_FIRST_LINE + col);
		}
		break;
	case 1:
		if ((col < 16) && (col >= 0))
		{
			LCD_sendCommand(LCD_COM_SET_CURSOR_SECOND_LINE + col);
		}
		break;
	}
}