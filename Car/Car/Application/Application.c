#include "Application.h"





void app_init(void)
{
	/* Initialization */
	Ultrasonic_init();
	
}


void app_start(void)
{
	Ultrasonic_getReading();
}

