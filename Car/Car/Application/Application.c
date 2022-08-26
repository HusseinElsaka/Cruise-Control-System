#include "Application.h"

u8_t current_mode = INITIALIZATION_MODE;
u8_t BRAIKE_MODE_button = 0;

void app_init(void)
{
	BUTTON_start();
	Ultrasonic_init();
	TIMER1_5secDelay_Config(&Timer1App);
	Enable_INT2(INT_RISING);
	sei();
	u8_t readingInitButton = LOW;
	while (readingInitButton == LOW)
	{
		BUTTON_read(PORT_speed,BUTTON_START,&readingInitButton);
	}
	current_mode = CONTROL_ULTRA_SONIC_MODE;
	Motor_Speed(Actual_MotorSpeed);
}


void app_start(void)
{
	if (current_mode == BRAIKE_MODE)
	{
		u32_t tickTime;
		TIMER1_Get_Ticktime(&tickTime);
		if(BRAIKE_MODE_button >= 2 && tickTime < ONE_SECOND_T1)
		{
			current_mode = CONTROL_ULTRA_SONIC_MODE;
			TIMER1_stop();
			BRAIKE_MODE_button = 0;
		}
		else if(tickTime > ONE_SECOND_T1)
		{
			BRAIKE_MODE_button = 0;
		}
	}
	else if (current_mode == CONTROL_DECREMENT_MODE || current_mode == CONTROL_INCREMENT_MODE)
	{
		Button_check();
	}
	else
	{
		Button_check();
		Ultrasonic_getReading();
		Ultrasonic_CarSpeed(distance);
	}
	Motor_SendData();
}

void Button_check(void)
{
	u8_t dec_read = LOW,inc_read = LOW;
	u32_t tickTime = 0;
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
	}
	TIMER1_Flag_Reset(&Timer1App);
	TIMER1_Reset();
	TIMER1_stop();
}

ISR(EXT_INT_2)
{
	if(current_mode != INITIALIZATION_MODE)
	{
		current_mode = BRAIKE_MODE;
		Motor_Speed(Actual_MotorSpeed - MOTOR_DECREASE_SPEED);
		if (BRAIKE_MODE_button == 0)
		{
			TIMER1_start(&Timer1App,FIVE_SECOND_T1);
			TIMER1_Reset();
		}
		BRAIKE_MODE_button ++;
	}
}
