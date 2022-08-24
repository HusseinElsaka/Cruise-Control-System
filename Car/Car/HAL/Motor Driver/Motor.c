#include "Motor.h"

#include <stdlib.h>
#include <string.h>

u32_t Actual_MotorSpeed = MOTOR_START_SPEED;
/*
Function to Initialization MOTOR Pins
Input : void
return ERROR or OK
*/

EN_ERRORSTATE_t Motor_Init(void)
{
	// UART initialization
	UART_init();
	
	DIO_setPinDirection(MOTOR_A_PORT,MOTOR_A_PIN,HIGH);
	DIO_setPinDirection(MOTOR_B_PORT,MOTOR_B_PIN,HIGH);
	TIMER0_PWM_init(&Timer0App);
	return E_OK;
}

/*
Function to Give the OCR0 the PWM to MOTOR
Input : The Speed to motor
return ERROR or OK
*/

EN_ERRORSTATE_t Motor_Speed(u32_t Speed)
{
	if (Speed >= MOTOR_MAX_SPEED)
	{
		Actual_MotorSpeed = MOTOR_MAX_SPEED;
	}
	else if (Speed < MOTOR_START_SPEED)
	{
	}
	else
	{
		Actual_MotorSpeed = Speed;
	}
	TIMER0_start(&Timer0App,Actual_MotorSpeed);
	return E_OK;
}

/*
Function to Send Motor Speed to LCD
Input : Void
return ERROR or OK
*/

EN_ERRORSTATE_t Motor_SendData(void)
{
	u8_t Speed_str[10];
	itoa(Actual_MotorSpeed,Speed_str,10);
	strcat(Speed_str," Km");
	UART_SendString(Speed_str);
	
}