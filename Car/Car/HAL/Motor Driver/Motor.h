

#ifndef MOTOR_H_
#define MOTOR_H_

#include "../../MCAL/DIO Driver/dio.h"
#include "../../MCAL/Timers Drivers/Timer0 Driver/timer0.h"
#include "../../MCAL/USART/USART.h"

/* Motor Pins */
#define MOTOR_A_PORT PORT_B
#define MOTOR_A_PIN	PIN3
#define MOTOR_B_PORT PORT_D
#define MOTOR_B_PIN PIN7

/* Motor Speeds */
#define MOTOR_STOP_SPEED 0
#define MOTOR_START_SPEED 10
#define MOTOR_5_SPEED 5
#define MOTOR_50_SPEED 50
#define MOTOR_75_SPEED 75
#define MOTOR_INCREASE_SPEED 25
#define MOTOR_DECREASE_SPEED 25	
#define MOTOR_MAX_SPEED 100


extern u32_t Actual_MotorSpeed;
Str_Timer0Configuration_t Timer0App;

/*
Function to Initialization MOTOR Pins
Input : void
return ERROR or OK
*/

EN_ERRORSTATE_t Motor_Init(void);

/*
Function to Give the OCR0 the PWM to MOTOR 
Input : The Speed to motor and Direction
return ERROR or OK
*/

EN_ERRORSTATE_t Motor_Speed(u32_t Speed);

/*
Function to Send Motor Speed to LCD
Input : Void
return ERROR or OK
*/

EN_ERRORSTATE_t Motor_SendData(void);


/*
Function to Give the OCR0 the 0 to MOTOR
Input : The Speed to motor
return ERROR or OK
*/

EN_ERRORSTATE_t Motor_Stop(void);

#endif /* MOTOR_H_ */