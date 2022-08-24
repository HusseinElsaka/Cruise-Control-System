#include "Application.h"

u8_t current_mode = CONTROL_ULTRA_SONIC_MODE;

u8_t BRAIKE_MODE_button = 0;

void app_init(void)
{
	BUTTON_start();
	Ultrasonic_init();
	TIMER1_5secDelay_Config(&Timer1App);
	Enable_INT2(INT_RISING);
	sei();
}


void app_start(void)
{
	if (current_mode == BRAIKE_MODE)
	{
		u8_t tickTime;
		TIMER1_Get_Ticktime(&tickTime);
		if(BRAIKE_MODE_button >= 2 && tickTime < ONE_SECOND_T1)
		{
			current_mode = CONTROL_ULTRA_SONIC_MODE;
			Motor_Speed(MOTOR_START_SPEED);
			BRAIKE_MODE_button = 0;
		}
		else if(tickTime > ONE_SECOND_T1)
		{
			BRAIKE_MODE_button = 0;
			TIMER1_start(&Timer1App,FIVE_SECOND_T1);
		}
	}
	else
	{
			Button_check();
			Motor_SendData();
			Ultrasonic_getReading();
	}
}

void Button_check(void)
{
	u8_t dec_read = LOW,inc_read = LOW,tickTime = 0;
	TIMER1_Get_Ticktime(&tickTime);
	BUTTON_read(PORT_speed,BUTTON_INC,&inc_read);
	BUTTON_read(PORT_speed,BUTTON_DEC,&dec_read);
	if (dec_read == LOW && inc_read == HIGH)
	{
		if((current_mode == CONTROL_DECREMENT_MODE && tickTime > ONE_HALF_SECOND_T1) || (current_mode != CONTROL_DECREMENT_MODE))
		{
			current_mode = CONTROL_INCREMENT_MODE;
			TIMER1_start(&Timer1App,FIVE_SECOND_T1);
			Motor_Speed(Actual_MotorSpeed + MOTOR_INCREASE_SPEED);
		}
	}
	else if (dec_read == HIGH && inc_read == LOW)
	{
		if((current_mode == CONTROL_INCREMENT_MODE && tickTime > ONE_SECOND_T1) || (current_mode != CONTROL_INCREMENT_MODE))
		{
			current_mode = CONTROL_DECREMENT_MODE;
			TIMER1_start(&Timer1App,FIVE_SECOND_T1);
			Motor_Speed(Actual_MotorSpeed - MOTOR_DECREASE_SPEED);
		}
	}

}

ISR(TIMER1_COMPA)
{
	if(current_mode != BRAIKE_MODE)
	{
		current_mode = CONTROL_ULTRA_SONIC_MODE;
		Ultrasonic_CarSpeed(distance);
	}
	TIMER1_Flag_Reset(&Timer1App);
	TIMER1_stop();
}

ISR(EXT_INT_2)
{
	current_mode = BRAIKE_MODE;
	Motor_Speed(Actual_MotorSpeed - MOTOR_DECREASE_SPEED);
	if (BRAIKE_MODE_button == 0)
		TIMER1_start(&Timer1App,FIVE_SECOND_T1);
	BRAIKE_MODE_button ++;
}
