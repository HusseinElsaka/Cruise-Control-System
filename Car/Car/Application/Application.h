

#ifndef APPLICATION_H_
#define APPLICATION_H_

#define F_CPU 8000000UL

#include "../MCAL/ADC Driver/adc.h"



Str_Timer0Configuration_t timer0app;


void app_init(void);
void app_start(void);



#endif /* APPLICATION_H_ */