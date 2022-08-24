#include "Application.h"





void app_init(void)
{
	/* Initialization */
<<<<<<< HEAD
	//DIO_setPortDirection(PORT_A,0xFF);
	BUTTON_start();
	Ultrasonic_init();
	MOTOR_start();
	UART_init();
=======
	Ultrasonic_init();
	
>>>>>>> main
}


void app_start(void)
{
	Ultrasonic_getReading();
}
<<<<<<< HEAD
=======

>>>>>>> main
