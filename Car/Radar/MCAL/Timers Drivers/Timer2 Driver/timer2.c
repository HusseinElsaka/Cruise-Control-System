#include "timer2.h"

/*
initial TIMER2 with its configurations
Input : Configuration
output : ERROR or OK

	  WGM21		WGM20
		0		0		Normal 
		0		1		PWM,Phase Correct
		1		0		CTC
		1		1		Fast PWM 
*/
extern EN_ERRORSTATE_t TIMER2_init(Str_Timer2Configuration_t *Config_t)
{
	
	switch(Config_t->Ticks_Mode)
	{
		case NORMAL_MODE:
		{
			CLR_BIT(TCCR2,WGM20);CLR_BIT(TCCR2,WGM21);
			if(Config_t->Interrupt_Mode == INTERRUPT)
			{
				TIMSK |= (1 << TOIE2);
			}
			break;
		}
		case CTC_MODE:
		{
			TCCR2 |= (1 << WGM21);
			if(Config_t->Interrupt_Mode == INTERRUPT)
			{
				TIMSK |= (1 << OCIE2);
			}
			break;
		}
		case FAST_PWM_MODE:
		{
			TCCR2 |= (1 << WGM21) | (1<< WGM20);
			if(Config_t->PWM_Mode == PWM_NORMAL)
			{
				CLR_BIT(TCCR2,COM20);
				CLR_BIT(TCCR2,COM21);
				break;
			}
			else if(Config_t->PWM_Mode == NON_INVERTED)
			{
				TCCR2 |= (1<<COM21);
				break;
			}
			else if(Config_t->PWM_Mode == INVERTED)
			{
				TCCR2 |= (1<<COM21) | (1 << COM20);
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
			TCCR2  |=(1<< WGM20);
			
			if (Config_t->PWM_Mode == PWM_NORMAL)
			{
				CLR_BIT(TCCR2,COM20);
				CLR_BIT(TCCR2,COM21);
				break;
			}
			else if (Config_t->PWM_Mode == NON_INVERTED)
			{
				TCCR2 |= (1<<COM21);
				break;
			}
			else if (Config_t->PWM_Mode == INVERTED)
			{
				TCCR2 |= (1<<COM21) | (1 << COM20);
				break;
			}
			else
			{
				return E_ERROR;
			}
			
			break;
			default:
			return E_ERROR;
			break;
		}
	}
	return E_OK;
}

/*
Start TIMER2 with its configurations
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_start(Str_Timer2Configuration_t *Config_t, uint8_t Ntick)
{
	/*Calculate the needing Tick to start*/
	if (Config_t->Ticks_Mode == NORMAL_MODE)
	{
		TCNT2 = TIMER2_OVERFLOW - Ntick;
	}
	else if (Config_t->Ticks_Mode == CTC_MODE)
	{
		TCNT2 = 0;
		OCR2 = Ntick;
	}
	else if(Config_t->Ticks_Mode == PHASE_CORRECT_PWM_MODE)
	{
		OCR2 = Ntick;
	}
	else if (Config_t->Ticks_Mode == FAST_PWM_MODE)
	{
		OCR2 = Ntick;
	}
	else
	{
		return E_ERROR;
	}
	/*PRESCALER TO START*/
	/*
	CS22	CS21	CS20	Description
	0		0		0		No clock source (Timer/Counter stopped).
	0		0		1		clkI/O/(No prescaling)
	0		1		0		clkI/O/8 (From prescaler)
	0		1		1		clkT2S/32 (From prescaler)
	1		0		0		clkI/O/64 (From prescaler)
	1		0		1		clkT2S/128 (From prescaler)
	1		1		0		clkI/O/256 (From prescaler)
	1		1		1		clkI/O/1024 (From prescaler)
	*/
	switch(Config_t->Timer_Psc)
	{
		case NO_CLOCK_TIMER_2:
		CLR_BIT(TCCR2,CS20);
		CLR_BIT(TCCR2,CS21);
		CLR_BIT(TCCR2,CS22);
		break;
		case F_CPU_CLOCK_TIMER_2:
		TCCR2 |= (1 << CS20);
		break;
		case F_CPU_CLOCK_8_TIMER_2:
		TCCR2 |= (1 << CS21);
		break;
		case F_CPU_CLOCK_32_TIMER_2:
		TCCR2 |= (1 << CS21) | (1 << CS20);
		break;
		case F_CPU_CLOCK_64_TIMER_2:
		TCCR2 |= (1 << CS22);
		break;
		case F_CPU_CLOCK_128_TIMER_2:
		TCCR2 |= (1 << CS22) | (1 << CS20);
		break;
		case F_CPU_CLOCK_256_TIMER_2:
		TCCR2 |= (1 << CS22) | (1 << CS21);
		break;
		case F_CPU_CLOCK_1024_TIMER_2:
		TCCR2 |= (1 << CS22) | (1 << CS21) | (1 << CS20);
		break;
		default:
		return E_ERROR;
		break;
	}
	return E_OK;
}

/*
stop TIMER2
Input : --
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_stop(void)
{
	TCCR2 &= ~(0<<CS20) & ~(0<<CS21) & ~(0<<CS22);
	return E_OK;
}

/*
get TIMER2 flag state
Input : Configuration and pointer to address to get into the flag value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_Get_FlagStatus(Str_Timer2Configuration_t *Config_t, uint8_t *PTR_Flag)
{
	if (Config_t->Ticks_Mode == NORMAL_MODE)
	{
		*PTR_Flag = GET_BIT(TIFR,TOV2);
	}
	else if (Config_t->Ticks_Mode == CTC_MODE)
	{
		*PTR_Flag = GET_BIT(TIFR,OCF2);
	}
	else
	{
		return E_ERROR;
	}
	return E_OK;
}

/*
reset TIMER2 flag state
Input : Configuration and value to set
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_Flag_Reset(Str_Timer2Configuration_t *Config_t)
{
	if (Config_t->Ticks_Mode == NORMAL_MODE)
	{
		TIFR |= (1 << TOV2);
	}
	else if (Config_t->Ticks_Mode == CTC_MODE)
	{
		TIFR |= (1 << OCF2);
	}
	else
	{
		return E_ERROR;
	}
	return E_OK;
}


/*
reset TIMER2 TCNT2
Input : Configuration and value to set
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_Reset()
{
	TCNT2 = 0;
	return E_OK;
}

/*
get TIMER2 Ticktime
Input : pointer to address to get into the ticktime value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_Get_Ticktime(uint8_t *PTR_ticktime)
{
	*PTR_ticktime = TCNT2;
	return E_OK;
}
 
/*
Congif for counter interrupt no prescaler
Input : struct config
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_Counter_config(Str_Timer2Configuration_t *Config_t)
{
	Config_t->Mode = COUNTER_MODE;
	Config_t->Ticks_Mode = NORMAL_MODE;
	Config_t->Timer_Psc = F_CPU_CLOCK_TIMER_2;
	Config_t->Interrupt_Mode = INTERRUPT;
	TIMER2_Reset(Config_t);
	TIMER2_init(Config_t);
	TIMER2_start(Config_t,TIMER2_OVERFLOW);
	return E_OK;
}
