

#ifndef APPLICATION_H_
#define APPLICATION_H_

#define F_CPU 8000000UL

#include "../HAL/LCD Driver/LCD.h"
#include "../MCAL/USART/USART.h"
#include "../MCAL/Timers Drivers/Timer1 Driver/timer1.h"


void app_init(void);
void app_start(void);



#endif /* APPLICATION_H_ */