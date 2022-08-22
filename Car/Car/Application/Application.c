#include "Application.h"

u8_t flag = 0;

 


void app_init(void)
{
	/* Initialization */
	DIO_setPortDirection(PORT_A,0xFF);
	Ultrasonic_init();
}


void app_start(void)
{
	Ultrasonic_getReading();
}