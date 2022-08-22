

#ifndef TIMER2_H_
#define TIMER2_H_

#include "../../../Utilites/BitMath.h"
#include "../../../Utilites/Memmap.h"
#include "../../../Utilites/Datatypes.h"



/* TIMER2 Bits macros */
// TCCR2
#define CS20 0
#define CS21 1
#define CS22 2
#define WGM21 3
#define COM20 4
#define COM21 5
#define WGM20 6
#define FOC2 7

// TIMSK
#define TOIE2 6
#define OCIE2 7

// TIFR
#define TOV2 6
#define OCF2 7


/* TIMER2  Configuration struct */
typedef struct
{
	uint8_t Mode;			/* timer or counter */
	uint8_t Ticks_Mode;    /* normal Mode or CTC Mode */
	uint8_t Timer_Psc;     /*Timer Prescaler Based on DataSheet No prescaler or /8 or /64 or .....*/
	uint8_t Interrupt_Mode; /*Timer Overflow Mode Interrupt or polling */
	uint8_t PWM_Mode;		/* Inverted or non inverted mode */
}Str_Timer2Configuration_t;


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
/*                       Timer2 Prescaler                         */
/******************************************************************/
#define NO_CLOCK_TIMER_2     					0
#define F_CPU_CLOCK_TIMER_2   					1
#define F_CPU_CLOCK_8_TIMER_2 					2
#define F_CPU_CLOCK_32_TIMER_2					3
#define F_CPU_CLOCK_64_TIMER_2					4
#define F_CPU_CLOCK_128_TIMER_2					5
#define F_CPU_CLOCK_256_TIMER_2		 			6
#define F_CPU_CLOCK_1024_TIMER_2				7

/******************************************************************/
/*                        OverFlow Mode                           */
/******************************************************************/

#define POLLING      0
#define INTERRUPT    1

/****************************	**************************************/
/*                        PWM Modes                                */
/*******************************************************************/
#define PWM_NORMAL 0
#define NON_INVERTED 1
#define INVERTED 1

#define TIMER2_OVERFLOW 255
/*
initial TIMER2 with its configurations
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_init(Str_Timer2Configuration_t *Config_t);

/*
Start TIMER2 with its configurations
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_start(Str_Timer2Configuration_t *Config_t, uint8_t tick);

/*
stop TIMER2
Input : --
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_stop(void);

/*
get TIMER2 flag state
Input : Configuration and pointer to address to get into the flag value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_Get_FlagStatus(Str_Timer2Configuration_t *Config_t, uint8_t *PTR_Flag);

/*
reset TIMER2 flag state
Input : Configuration
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_Flag_Reset(Str_Timer2Configuration_t *Config_t);


/*
reset TIMER2 TCNT2
Input : Configuration and value to set
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_Reset(Str_Timer2Configuration_t *Config_t);

/*
get TIMER2 Ticktime
Input : pointer to address to get into the ticktime value
output : ERROR or OK
*/
extern EN_ERRORSTATE_t TIMER2_Get_Ticktime(uint8_t *PTR_ticktime);




#endif /* TIMER2_H_ */