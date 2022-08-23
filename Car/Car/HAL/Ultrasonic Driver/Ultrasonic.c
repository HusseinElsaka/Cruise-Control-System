#include "Ultrasonic.h"

#include <util/delay.h>
#include <stdlib.h>
#include <string.h>


Str_Timer2Configuration_t COUNTER2;

u8_t sensor_working=0;
static u8_t rising_edge=0;
u32_t timer_counter=0;
u32_t distance;
u8_t distance_str[10] = {0};

/*
Function to initialization the Ultrasonic pins and Timer2 and external interrupt
Input : void
return ERROR or OK
*/

EN_ERRORSTATE_t Ultrasonic_init(void)
{
	
	
	// UART initialization
	UART_init();
	
	
	// Pins for Ultrasonic --
	DIO_setPinDirection(ULTRASONIC_PORT,ULTRASONIC_TRIGGER_PIN,HIGH);
	DIO_setPinDirection(ULTRASONIC_PORT,ULTRASONIC_ECHO_PIN,LOW);
	DIO_pullUp(ULTRASONIC_PORT,ULTRASONIC_ECHO_PIN);
	
	// Timer 2 Initial
	TIMER2_Counter_config(&COUNTER2);
	
	// Enable External Interrupt
	Enable_INT1(INT_LOGIC_CHANGE);
	
	return E_OK;
}


/*
Function to get reading of Ultrasonic "Distance
Input : void
output : reading value
return ERROR or OK
*/

EN_ERRORSTATE_t Ultrasonic_getReading(void)
{
	if(!sensor_working)
	{
		/* Give 10us trigger pulse on trig. pin to HC-SR04 */
		DIO_setPin(ULTRASONIC_PORT,ULTRASONIC_TRIGGER_PIN,HIGH);
		_delay_us(15);
		DIO_setPin(ULTRASONIC_PORT,ULTRASONIC_TRIGGER_PIN,LOW);
		sensor_working=1;
	}
	
	return E_OK;
}


/*
Function to car Speed of Ultrasonic depend on the Distance
Input : void
output : Speed of Car
return ERROR or OK
*/

EN_ERRORSTATE_t Ultrasonic_CarSpeed(u32_t Distance)
{
	if (Distance >= 80)
	{
		//100% speed

	}
	else if (Distance >= 50)
	{
		//75% speed

	}
	else if (Distance >= 20)
	{
		// 50% speed

	}
	else if (Distance >= 5)
	{
		// 5% speed
	}
	else
	{
		// 0% speed
	}
	return E_OK;
}


/*
Function to Return Distance to send to LCD
Input : void
output : Distance
return ERROR or OK
*/
extern EN_ERRORSTATE_t Ultrasonic_DataSend(void)
{
	UART_SendString(distance_str);
	return E_OK;
}



/*
Sound velocity = 343.00 m/s = 34300 cm/s

Distance of Object (in cm) = (Sound velocity * TIMER Value) / 2
Distance of Object (in cm) = (34300 * TIMER Value) / 2
Distance of Object (in cm) = 17150  * Timer Value

we have selected internal 8 MHz oscillator frequency for ATmega32,
with No-presale for timer frequency.
Then time to execute 1 instruction is 0.125 us So,
timer gets incremented after 0.125 us time elapse.

Distance of Object (in cm) = 17150 x (TIMER value) x 0.125 x 10^-6 cm

Distance of Object (in cm) = 0.125 x (TIMER value)/58.30 cm

Distance of Object (in cm) = (TIMER value) / 466.47 cm

*/

ISR(EXT_INT_1)
{
	if(sensor_working==1)
	{
		if(rising_edge==0)
		{
			TIMER2_Reset();
			rising_edge=1;
			timer_counter=0;
		}
		else
		{
			distance=(timer_counter*256+TCNT0)/466;
			itoa(distance,distance_str,10);
			strcat(distance_str," Cm");
			Ultrasonic_DataSend();
			Ultrasonic_CarSpeed(distance);
			_delay_ms(40);

			timer_counter=0;
			rising_edge=0;
		}
	}
}

ISR(TIMER2_OVF)
{
	timer_counter++;
	if(timer_counter >730)
	{
		TIMER2_Reset();
		sensor_working=0;
		//rising_edge=0;
		timer_counter=0;
	}
	TIMER2_Flag_Reset(&COUNTER2);
	TIMER2_Reset();
	
}