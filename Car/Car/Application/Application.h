

#ifndef APPLICATION_H_
#define APPLICATION_H_



#include "../HAL/Ultrasonic Driver/Ultrasonic.h"
#include "../MCAL/Timers Drivers/Timer1 Driver/timer1.h"
#include "../HAL/Button Driver/button.h"

#define BRAIKE_MODE				 0
#define CONTROL_INCREMENT_MODE	 1
#define CONTROL_DECREMENT_MODE	 2
#define CONTROL_ULTRA_SONIC_MODE 3
#define INITIALIZATION_MODE		 4

extern u8_t current_mode;
Str_Timer1Configuration_t Timer1App;

void Button_check(void);


void app_init(void);
void app_start(void);



#endif /* APPLICATION_H_ */