#include "timer1.h"
/*
initial TIMER1 with its configurations
Input : Configuration
output : ERROR or OK

Mode	WGM13	WGM12	WGM11	WGM10	Timer/Counter Mode of Operation		TOP
0		0		0		0		0		Normal								0xFFFF 
1		0		0		0		1		PWM, Phase Correct, 8-bit			0x00FF 
2		0		0		1		0		PWM, Phase Correct, 9-bit			0x01FF 
3		0		0		1		1		PWM, Phase Correct, 10-bit			0x03FF
4		0		1		0		0		CTC									OCR1A 
5		0		1		0		1		Fast PWM, 8-bit						0x00FF 
6		0		1		1		0		Fast PWM, 9-bit						0x01FF 
7		0		1		1		1		Fast PWM, 10-bit					0x03FF
8		1		0		0		0		PWM, Phase and Frequency Correct	ICR1
9		1		0		0		1		PWM, Phase and Frequency Correct	OCR1A
10		1		0		1		0		PWM, Phase Correct					ICR1 
11		1		0		1		1		PWM, Phase Correct					OCR1A 
12		1		1		0		0		CTC									ICR1 
13		1		1		0		1		Reserved							�
14		1		1		1		0		Fast PWM							ICR1
15		1		1		1		1		Fast PWM							OCR1A

*/
extern EN_ERRORSTATE_t TIMER1_init(Str_Timer1Configuration_t *Config_t)
{
	
	switch(Config_t->Ticks_Mode)
	{
		case NORMAL_MODE:
		{
			CLR_BIT(TCCR1A,WGM10);CLR_BIT(TCCR1A,WGM11);CLR_BIT(TCCR1B,WGM12);CLR_BIT(TCCR1B,WGM13);
			if(Config_t->Interrupt_Mode == INTERRUPT)
			{
				TIMSK |= (1 << TICIE1);
			}
			break;
		}
		case CTC_MODE:
		{
			TCCR1B |= (1 << WGM12);
			if(Config_t->Interrupt_Mode == INTERRUPT)
			{
				TIMSK |= (1 << OCIE1A);
			}
			break;
		}
		case FAST_PWM_MODE:
		{
			TCCR1A |= (1 << WGM10) | (1<< WGM11) | (1 << WGM12) | (1<< WGM13);
			if(Config_t->PWM_Mode == PWM_NORMAL)
			{
				CLR_BIT(TCCR1A,COM1B0);CLR_BIT(TCCR1A,COM1B1);CLR_BIT(TCCR1A,COM1A0);CLR_BIT(TCCR1A,COM1A1);
				break;
			}
			else if(Config_t->PWM_Mode == NON_INVERTED)
			{
				TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
				break;
			}
			else if(Config_t->PWM_Mode == INVERTED)
			{
				TCCR1A |= (1 << COM1A1) | (1 << COM1A0) |(1 << COM1B1) | (1 << COM1B0);
				break;
			}
			else
			{
				return E_ERROR;
			}
			break;
		}
		case PHASE_CORRECT_PWM_MODE:
		{
			TCCR1A  |=(1<< WGM10) | (1<< WGM11) | (1<< WGM13);
			
			if (Config_t->PWM_Mode == PWM_NORMAL)
			{
				CLR_BIT(TCCR1A,COM1B0);CLR_BIT(TCCR1A,COM1B1);CLR_BIT(TCCR1A,COM1A0);CLR_BIT(TCCR1A,COM1A1);
				break;
			}
			else if (Config_t->PWM_Mode == NON_INVERTED)
			{
				TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
				break;
			}
			else if (Config_t->PWM_Mode == INVERTED)
			{
				TCCR1A |= (1 << COM1A1) | (1 << COM1A0) |(1 << COM1B1) | (1 << COM1B0);
				break;
			}
			else
			{
				return E_ERROR;
			}
			
			break;
		}
	}
	return E_OK;
}

/*
Start TIMER1 with its configurations
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_start(Str_Timer1Configuration_t *Config_t, u32_t Ntick)
{
	/*Calculate the needing Tick to start*/
	if (Config_t->Ticks_Mode == NORMAL_MODE)
	{
		TCNT1H = (((TIMER1_OVERFLOW - Ntick) & 0xFF00) >> 8);
		TCNT1L = ((TIMER1_OVERFLOW - Ntick) & 0x00FF);
	}
	else if (Config_t->Ticks_Mode == CTC_MODE)
	{
		TCNT1H = 0;
		TCNT1L = 0;
		OCR1AH = ((Ntick & 0xFF00) >> 8);
		OCR1BH = ((Ntick & 0xFF00) >> 8);
		ICR1H = ((Ntick & 0xFF00) >> 8);
		OCR1AL = (Ntick & 0x00FF);
		OCR1BL = (Ntick & 0x00FF);
		ICR1L = (Ntick & 0x00FF);
	}
	else if(Config_t->Ticks_Mode == PHASE_CORRECT_PWM_MODE)
	{
		OCR1AH = ((Ntick & 0xFF00) >> 8);
		OCR1BH = ((Ntick & 0xFF00) >> 8);
		OCR1AL = (Ntick & 0x00FF);
		OCR1BL = (Ntick & 0x00FF);
	}
	else if (Config_t->Ticks_Mode == FAST_PWM_MODE)
	{
		OCR1AH = ((Ntick & 0xFF00) >> 8);
		OCR1BH = ((Ntick & 0xFF00) >> 8);
		OCR1AL = (Ntick & 0x00FF);
		OCR1BL = (Ntick & 0x00FF);
	}
	else
	{
		return E_ERROR;
	}
	/*PRESCALER TO START*/
	/*
	CS12	CS11	CS10	Description
	0		0		0		No clock source (Timer/Counter stopped).
	0		0		1		clkI/O/(No prescaling)
	0		1		0		clkI/O/8 (From prescaler)
	0		1		1		clkI/O/64 (From prescaler)
	1		0		0		clkI/O/256 (From prescaler)
	1		0		1		clkI/O/1024 (From prescaler)
	1		1		0		External clock source on T0 pin. Clock on falling edge.
	1		1		1		External clock source on T0 pin. Clock on rising edge
	*/
	switch(Config_t->Timer_Psc)
	{
		case NO_CLOCK_TIMER_1:
		CLR_BIT(TCCR1B,CS10);CLR_BIT(TCCR1B,CS11);CLR_BIT(TCCR1B,CS12);
		break;
		case F_CPU_CLOCK_TIMER_1:
		TCCR1B |= (1 << CS10);
		break;
		case F_CPU_CLOCK_8_TIMER_1:
		TCCR1B |= (1 << CS11);
		break;
		case F_CPU_CLOCK_64_TIMER_1:
		TCCR1B |= (1 << CS11) | (1 << CS10);
		break;
		case F_CPU_CLOCK_256_TIMER_1:
		TCCR1B |= (1 << CS12);
		break;
		case F_CPU_CLOCK_1024_TIMER_1:
		TCCR1B |= (1 << CS12) | (1 << CS10);
		break;
		case F_EXTERNAL_CLOCK_FALLING_TIMER_1:
		TCCR1B |= (1 << CS12) | (1 << CS11);
		break;
		case F_EXTERNAL_CLOCK_RISING_TIMER_1:
		TCCR1B |= (1 << CS12) | (1 << CS11) | (1 << CS10);
		break;
	}
	return E_OK;
}

/*
stop TIMER1
Input : --
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_stop(void)
{
	TCCR1B &= ~(0<<CS10) & ~(0<<CS11) & ~(0<<CS12);
	return E_OK;
}

/*
get TIMER1 flag state
Input : Configuration and pointer to address to get into the flag value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_Get_FlagStatus(Str_Timer1Configuration_t *Config_t, u8_t *PTR_Flag)
{
	if (Config_t->Ticks_Mode == NORMAL_MODE)
	{
		*PTR_Flag = GET_BIT(TIFR,TOV1);
	}
	else if (Config_t->Ticks_Mode == CTC_MODE)
	{
		*PTR_Flag = GET_BIT(TIFR,OCF1A);
	}
	else
	{
		return E_ERROR;
	}
	return E_OK;
}

/*
set TIMER1 flag state
Input : Configuration and value to set
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_Flag_Reset(Str_Timer1Configuration_t *Config_t)
{
	if (Config_t->Ticks_Mode == NORMAL_MODE)
	{
		TIFR |= (1 << TOV1);
	}
	else if (Config_t->Ticks_Mode == CTC_MODE)
	{
		TIFR |= (1 << OCF1A);
	}
	else
	{
		return E_ERROR;
	}
	return E_OK;
}

/*
get TIMER1 Ticktime
Input : pointer to address to get into the ticktime value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_Get_Ticktime(uint8_t *PTR_ticktime)
{
	*PTR_ticktime = (TCNT1H << 8) | TCNT1L;
	return E_OK;
}

/*
Reset TIMER1 TCNT1
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_Reset(void)
{
	TCNT1 = 0x0000;
	return E_OK;
}

/*
function to generate 5sec using CPU at 1M hz
input : the timer1 config
output : make the timer1 configuration for the 5.000192 = (1024/8000000)*39063 so wenn need it as CTC as set OCR = 19,532
*/
extern EN_ERRORSTATE_t TIMER1_5secDelay_Config(Str_Timer1Configuration_t *Config_t)
{
	Config_t->Mode = TIMER_MODE;
	Config_t->Ticks_Mode = CTC_MODE;
	Config_t->Timer_Psc = F_CPU_CLOCK_1024_TIMER_1;
	Config_t->Interrupt_Mode = INTERRUPT;
	Config_t->PWM_Mode = PWM_NORMAL;
	return E_OK;
}
