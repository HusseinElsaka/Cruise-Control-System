#include "Application.h"

u8_t flag = 0;

 
 
void app_init(void)
{
	/* Initialization */
	
}


void app_start(void)
{

}


ISR(TIMER0_OVF)
{
	flag ++;
	TIMER0_Flag_Reset(&timer0app);
	TIMER0_start(&timer0app,TIMER0_OVERFLOW);
}