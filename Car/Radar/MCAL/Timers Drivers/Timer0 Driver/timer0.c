#include "timer0.h"

/*
initial TIMER0 with its configurations
Input : Configuration
output : ERROR or OK

	  WGM01		WGM00
		0		0		Normal 
		0		1		PWM,Phase Correct
		1		0		CTC
		1		1		Fast PWM 
*/
extern EN_ERRORSTATE_t TIMER0_init(Str_Timer0Configuration_t *Config_t)
{
	
	switch(Config_t->Ticks_Mode)
	{
		case NORMAL_MODE:
		{
			CLR_BIT(TCCR0,WGM00);CLR_BIT(TCCR0,WGM01);
			if(Config_t->Interrupt_Mode == INTERRUPT)
			{
				TIMSK |= (1 << TOIE0);
			}
			break;
		}
		case CTC_MODE:
		{
			TCCR0 |= (1 << WGM01);
			if(Config_t->Interrupt_Mode == INTERRUPT)
			{
				TIMSK |= (1 << OCIE0);
			}
			break;
		}
		case FAST_PWM_MODE:
		{
			TCCR0 |= (1 << WGM01) | (1<< WGM00);
			if(Config_t->PWM_Mode == PWM_NORMAL)
			{
				CLR_BIT(TCCR0,COM00);
				CLR_BIT(TCCR0,COM01);
				break;
			}
			else if(Config_t->PWM_Mode == NON_INVERTED)
			{
				TCCR0 |= (1<<COM01);
				break;
			}
			else if(Config_t->PWM_Mode == INVERTED)
			{
				TCCR0 |= (1<<COM01) | (1 << COM00);
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
			TCCR0  |=(1<< WGM00);
			
			if (Config_t->PWM_Mode == PWM_NORMAL)
			{
				CLR_BIT(TCCR0,COM00);
				CLR_BIT(TCCR0,COM01);
				break;
			}
			else if (Config_t->PWM_Mode == NON_INVERTED)
			{
				TCCR0 |= (1<<COM01);
				break;
			}
			else if (Config_t->PWM_Mode == INVERTED)
			{
				TCCR0 |= (1<<COM01) | (1 << COM00);
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
Start TIMER0 with its configurations
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_start(Str_Timer0Configuration_t *Config_t, u8_t Ntick)
{
	/*Calculate the needing Tick to start*/
	if (Config_t->Ticks_Mode == NORMAL_MODE)
	{
		TCNT0 = TIMER0_OVERFLOW - Ntick;
	}
	else if (Config_t->Ticks_Mode == CTC_MODE)
	{
		TCNT0 = 0;
		OCR0 = Ntick;
	}
	else if(Config_t->Ticks_Mode == PHASE_CORRECT_PWM_MODE)
	{
		OCR0 = Ntick;
	}
	else if (Config_t->Ticks_Mode == FAST_PWM_MODE)
	{
		OCR0 = Ntick;
	}
	else
	{
		return E_ERROR;
	}
	/*PRESCALER TO START*/
	/*
	CS02	CS01	CS00	Description
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
		case NO_CLOCK_TIMER_0:
		CLR_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		case F_CPU_CLOCK_TIMER_0:
		TCCR0 |= (1 << CS00);
		break;
		case F_CPU_CLOCK_8_TIMER_0:
		TCCR0 |= (1 << CS01);
		break;
		case F_CPU_CLOCK_64_TIMER_0:
		TCCR0 |= (1 << CS01) | (1 << CS00);
		break;
		case F_CPU_CLOCK_256_TIMER_0:
		TCCR0 |= (1 << CS02);
		break;
		case F_CPU_CLOCK_1024_TIMER_0:
		TCCR0 |= (1 << CS02) | (1 << CS00);
		break;
		case F_EXTERNAL_CLOCK_FALLING_TIMER_0:
		TCCR0 |= (1 << CS02) | (1 << CS01);
		break;
		case F_EXTERNAL_CLOCK_RISING_TIMER_0:
		TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
		break;
	}
	return E_OK;
}

/*
stop TIMER0
Input : --
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_stop(void)
{
	TCCR0 &= ~(0<<CS00) & ~(0<<CS01) & ~(0<<CS02);
	return E_OK;
}

/*
get TIMER0 flag state
Input : Configuration and pointer to address to get into the flag value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_Get_FlagStatus(Str_Timer0Configuration_t *Config_t, u8_t *PTR_Flag)
{
	if (Config_t->Ticks_Mode == NORMAL_MODE)
	{
		*PTR_Flag = GET_BIT(TIFR,TOV0);
	}
	else if (Config_t->Ticks_Mode == CTC_MODE)
	{
		*PTR_Flag = GET_BIT(TIFR,OCF0);
	}
	else
	{
		return E_ERROR;
	}
	return E_OK;
}

/*
reset TIMER0 flag state
Input : Configuration and value to set
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_Flag_Reset(Str_Timer0Configuration_t *Config_t)
{
	if (Config_t->Ticks_Mode == NORMAL_MODE)
	{
		TIFR |= (1 << TOV0);
	}
	else if (Config_t->Ticks_Mode == CTC_MODE)
	{
		TIFR |= (1 << OCF0);
	}
	else
	{
		return E_ERROR;
	}
	return E_OK;
}

/*
get TIMER0 Ticktime
Input : pointer to address to get into the ticktime value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_Get_Ticktime(uint8_t *PTR_ticktime)
{
	*PTR_ticktime = TCNT0;
	return E_OK;
}

/*
Reset TIMER0 TCNT0
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_Reset(void)
{
	TCNT0 = 0x00;
	return E_OK;
}

/*
function to generate 0.26112 sec using CPU at 8M hz
input : the timer0 config
output : make the timer0 configuration for the 0.03264 = (1024/80000000)*255 so wenn need it as overflow
*/
extern EN_ERRORSTATE_t TIMER0_SecDelay_config(Str_Timer0Configuration_t *Config_t)
{
	Config_t->Mode = TIMER_MODE;
	Config_t->Ticks_Mode = NORMAL_MODE;
	Config_t->Timer_Psc = F_CPU_CLOCK_1024_TIMER_0;
	Config_t->Interrupt_Mode = INTERRUPT;
	Config_t->PWM_Mode = PWM_NORMAL;
	return E_OK;
}

extern EN_ERRORSTATE_t TIMER0_SecDelay(Str_Timer0Configuration_t *Config_t)
{
	TIMER0_init(Config_t);
	for(u8_t i = 0; i < 32; i++)
	{
		TIMER0_start(Config_t,255);
		u8_t FLAG = 0;
		while(FLAG == 0)
		{
			TIMER0_Get_FlagStatus(Config_t,&FLAG);
		}
		TIMER0_Reset();
		TIMER0_Flag_Reset(Config_t);
	}	
	return E_OK;
}
