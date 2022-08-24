#include "Application.h"

#include "../MCAL/Interrupt Driver/INTERRUPT.h"

Str_Timer1Configuration_t Timer1APP;
u8_t Distance [10];
u8_t counterRx = 0;

void app_init(void)
{
	
	UART_init();
	LCD_Init();
	TIMER1_3secDelay(&Timer1APP);
	sei();
}


void app_start(void)
{
}

ISR(TIMER1_COMPA)
{
	LCD_sendCommand(LCD_COM_CLEAR);
	LCD_GOTO(0,0);
	LCD_writeString("Distance : ");
	LCD_GOTO(1,0);
	for(u8_t i = 0; i < 9; i++)
	{
		if(Distance[i] == 'm')
		{
			LCD_writeChar(Distance[i]);
			break;
		}
		LCD_writeChar(Distance[i]);
		
	}
	TIMER1_Reset();
	TIMER1_Flag_Reset(&Timer1APP);
	TIMER1_start(&Timer1APP,23438);
}

ISR(USART_RXC)
{
	Distance[counterRx] = UDR;
	counterRx ++;
	if(counterRx > 9 || Distance[counterRx - 1] == 'm')
	counterRx = 0;
	
}