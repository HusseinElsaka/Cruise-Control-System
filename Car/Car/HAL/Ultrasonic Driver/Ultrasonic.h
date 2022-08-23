

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "../../MCAL/DIO Driver/DIO.h"
#include "../../MCAL/Timers Drivers/Timer2 Driver/timer2.h"
#include "../../Utilites/BitMath.h"
#include "../../Utilites/DataTypes.h"
#include "../../MCAL/Interrupt Driver/INTERRUPT.h"
#include "../../MCAL/USART/USART.h"

#define ULTRASONIC_PORT PORT_D
#define ULTRASONIC_TRIGGER_PIN PIN7
#define ULTRASONIC_ECHO_PIN PIN3

#define F_CPU 8000000UL

/*
Function to initialization the Ultrasonic
Input : void
return ERROR or OK
*/
EN_ERRORSTATE_t Ultrasonic_init(void);


/*
Function to get reading of Ultrasonic "Distance
Input : void
output : reading value
return ERROR or OK
*/
EN_ERRORSTATE_t Ultrasonic_getReading(void);


/*
Function to Data send UART to LCD as string
Input : void
output : String
return ERROR or OK
*/

extern EN_ERRORSTATE_t Ultrasonic_CarSpeed(u32_t Distance);


/*
Function to Return Distance to send to LCD
Input : void
output : Distance
return ERROR or OK
*/
extern EN_ERRORSTATE_t Ultrasonic_DataSend(void);


#endif /* ULTRASONIC_H_ */