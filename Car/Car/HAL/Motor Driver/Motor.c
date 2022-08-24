#include "Motor.h"

u32_t Actual_MotorSpeed;
/*
Function to Initialization MOTOR Pins
Input : void
return ERROR or OK
*/

EN_ERRORSTATE_t Motor_Init(void)
{
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

