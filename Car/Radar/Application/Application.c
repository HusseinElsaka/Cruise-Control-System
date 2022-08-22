#include "Application.h"

u8_t flag = 0;

 
 
void app_init(void)
{
	/* Initialization */
	DIO_setPortDirection(PORT_A,0x00);
	DIO_setPortDirection(PORT_C,0xFF);
	DIO_setPortDirection(PORT_D,0xFB);
	
	LCD_Init();
	
	
	TIMER0_SecDelay_config(&timer0app);
	TIMER0_init(&timer0app);
	TIMER0_start(&timer0app,TIMER0_OVERFLOW);
	
	str_ADC_config_t adc = {INTERNAL_VREF_2_56_EXTERNAL_INTERNAL, LEFT_ADJUSTMENT, CHANNEL_ADC0, ADC_PRESCALER_64, ADC_AUTO_TRIGGER_MODE, ADC_AUTO_TRIGGER_MODE_TIMER0_OVF};
	ADC_Init(&adc);
	
	Enable_INT();
	
}


void app_start(void)
{
	LCD_GOTO(0,0);
	LCD_writeString("Temp :   \0");
	LCD_writeNumber((gu8_ADC_reading)/4);
	if (flag >= 32)
	{
		ADC_readChannel(CHANNEL_ADC0);
		flag = 0;
	}

}


ISR(TIMER0_OVF)
{
	flag ++;
	TIMER0_Flag_Reset(&timer0app);
	TIMER0_start(&timer0app,TIMER0_OVERFLOW);
}