#include "Application.h"





void app_init(void)
{
	Ultrasonic_init();
}


void app_start(void)
{
	Ultrasonic_getReading();
}
