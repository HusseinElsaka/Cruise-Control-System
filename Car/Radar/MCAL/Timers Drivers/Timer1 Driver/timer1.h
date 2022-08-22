
#ifndef TIMER1_H_
#define TIMER1_H_


#include "../../../Utilites/BitMath.h"
#include "../../../Utilites/Memmap.h"
#include "../../../Utilites/Datatypes.h"



/* TIMER1 Bits macros */

/* Timer/Counter1 Control Register A � TCCR1A */
#define WGM10 0
#define WGM11 1
#define FOC1B 2
#define FOC1A 3
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7

/* Timer/Counter1 Control Register B � TCCR1B */
#define CS10 0
#define CS11 1
#define CS12 2
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7

// TIMSK
#define TOIE1 2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5

// TIFR
#define TOV1 2
#define OCF1B 3
#define OCF1A 4
#define ICF1 5

/* TIMER1  Configuration struct */
typedef struct
{
	u8_t Mode;			/* timer or counter */
	u8_t Ticks_Mode;    /* normal Mode or CTC Mode */
	u8_t Timer_Psc;     /*Timer Prescaler Based on DataSheet No prescaler or /8 or /64 or .....*/
	u8_t Interrupt_Mode; /*Timer Overflow Mode Interrupt or polling */
	u8_t PWM_Mode;		/* Inverted or non inverted mode */
}Str_Timer1Configuration_t;


/******************************************************************/
/*                        MODE                                    */
/******************************************************************/
#define TIMER_MODE 0
#define COUNTER_MODE 1

/******************************************************************/
/*                       Normal MODE or CTC Mode                  */
/******************************************************************/
#define NORMAL_MODE 0
#define CTC_MODE 1
#define FAST_PWM_MODE 2
#define PHASE_CORRECT_PWM_MODE 3

/******************************************************************/
/*                       Timer1 Prescaler                         */
/******************************************************************/
#define NO_CLOCK_TIMER_1     					0
#define F_CPU_CLOCK_TIMER_1   					1
#define F_CPU_CLOCK_8_TIMER_1 					2
#define F_CPU_CLOCK_64_TIMER_1					3
#define F_CPU_CLOCK_256_TIMER_1					4
#define F_CPU_CLOCK_1024_TIMER_1				5
#define F_EXTERNAL_CLOCK_FALLING_TIMER_1		6
#define F_EXTERNAL_CLOCK_RISING_TIMER_1			7

/******************************************************************/
/*                        OverFlow Mode                           */
/******************************************************************/

#define POLLING      0
#define INTERRUPT    1

/******************************************************************/
/*                        PWM Modes                                */
/*******************************************************************/
#define PWM_NORMAL 0
#define NON_INVERTED 1
#define INVERTED 1

#define TIMER1_OVERFLOW 65536
#define TIMER1_CTC_5SEC_Ntick 19,532


/*
initial TIMER1 with its configurations
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_init(Str_Timer1Configuration_t *Config_t);

/*
Start TIMER1 with its configurations
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_start(Str_Timer1Configuration_t *Config_t, u32_t tick);

/*
stop TIMER1
Input : --
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_stop(void);

/*
get TIMER1 flag state
Input : Configuration and pointer to address to get into the flag value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_Get_FlagStatus(Str_Timer1Configuration_t *Config_t, u8_t *PTR_Flag);

/*
Reset TIMER1 flag state
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_Flag_Reset(Str_Timer1Configuration_t *Config_t);

/*
Reset TIMER1 TCNT1
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_Reset(void);
/*
get TIMER1 Ticktime
Input : pointer to address to get into the ticktime value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER1_Get_Ticktime(u8_t *PTR_ticktime);



#endif /* TIMER1_H_ */
