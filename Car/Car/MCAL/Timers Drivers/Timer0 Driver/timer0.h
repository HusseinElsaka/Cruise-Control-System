

#ifndef TIMER0_H_
#define TIMER0_H_

#include "../../../Utilites/BitMath.h"
#include "../../../Utilites/Memmap.h"
#include "../../../Utilites/Datatypes.h"
// using the avr at 1M hz 

/* TIMER0 Bits macros */
// TCCR0
#define CS00 0
#define CS01 1
#define CS02 2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0 7

// TIMSK
#define TOIE0 0
#define OCIE0 1

// TIFR
#define TOV0 0
#define OCF0 1


/* TIMER0  Configuration struct */
typedef struct
{
	u8_t Mode;			/* timer or counter */
	u8_t Ticks_Mode;    /* normal Mode or CTC Mode */
	u8_t Timer_Psc;     /*Timer Prescaler Based on DataSheet No prescaler or /8 or /64 or .....*/
	u8_t Interrupt_Mode; /*Timer Overflow Mode Interrupt or polling */
	u8_t PWM_Mode;		/* Inverted or non inverted mode */
}Str_Timer0Configuration_t;


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
/*                       Timer0 Prescaler                         */
/******************************************************************/
#define NO_CLOCK_TIMER_0     					0
#define F_CPU_CLOCK_TIMER_0   					1
#define F_CPU_CLOCK_8_TIMER_0 					2
#define F_CPU_CLOCK_64_TIMER_0					3
#define F_CPU_CLOCK_256_TIMER_0					4
#define F_CPU_CLOCK_1024_TIMER_0				5
#define F_EXTERNAL_CLOCK_FALLING_TIMER_0		6
#define F_EXTERNAL_CLOCK_RISING_TIMER_0			7

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

#define TIMER0_OVERFLOW 255
/*
initial TIMER0 with its configurations
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_init(Str_Timer0Configuration_t *Config_t);

/*
Start TIMER0 with its configurations
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_start(Str_Timer0Configuration_t *Config_t, u8_t tick);

/*
stop TIMER0
Input : --
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_stop(void);

/*
get TIMER0 flag state
Input : Configuration and pointer to address to get into the flag value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_Get_FlagStatus(Str_Timer0Configuration_t *Config_t, u8_t *PTR_Flag);


/*
Reset TIMER0 flag
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_Flag_Reset(Str_Timer0Configuration_t *Config_t);

/*
Reset TIMER0 TCNT0
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_Reset(void);
/*
get TIMER0 Ticktime
Input : pointer to address to get into the ticktime value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER0_Get_Ticktime(u8_t *PTR_ticktime);

/*
function to generate 0.26112 sec using CPU at 1M hz
input : the timer0 config
output : make the timer0 configuration for the 0.25112 = (1024/10000000)*255 so wenn need it as overflow
*/
extern EN_ERRORSTATE_t TIMER0_SecDelay_config(Str_Timer0Configuration_t *Config_t);

extern EN_ERRORSTATE_t TIMER0_SecDelay(Str_Timer0Configuration_t *Config_t);

/*
function to generate pwm CPU at 8M hz
input : the timer0 config
output : make the timer0 configuration Dute Cycle = (2*ocr/510) *100
*/
extern EN_ERRORSTATE_t TIMER0_PWM_init(Str_Timer0Configuration_t *Config_t);

#endif /* TIMER0_H_ */
