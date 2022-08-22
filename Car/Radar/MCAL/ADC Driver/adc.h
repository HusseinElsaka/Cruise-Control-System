
#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_
/*****************************************************************************
 *___________________________INCLUDES__________________________________________

 * ***************************************************************************/
#include "../../Utilites/memmap.h"
#include "../../Utilites/DataTypes.h"
#include "../../Utilites/BitMath.h"
#include "../Timers Drivers/Timer0 Driver/timer0.h"
#include "../Timers Drivers/Timer1 Driver/timer1.h"
//#include "adc_ret_val.h"
#include "../Interrupt Driver/INTERRUPT.h"

/******************************************************************************
 *__________________________________TYPEDEF____________________________________

 * ****************************************************************************/

typedef struct
{
	uint8_t u8_voltage;
	uint8_t u8_ADC_Adjustment;
	uint8_t u8_ADC_Channel;
	uint8_t u8_ADC_prescaler;
	uint8_t u8_ADC_Mode;
	uint8_t u8_ADC_triiger_mode;
}str_ADC_config_t;

/***************************************************************************
 * ___________________________EXTERN_______________________________________
 ***************************************************************************/
extern uint16_t gu8_ADC_reading;



/*****************************************************************************
 * _________________________LOCAL_MACROS______________________________________
 *
 ****************************************************************************/
#define INTERNAL_VREF_OFF 0
#define INTERNAL_VREF_2_56_EXTERNAL_INTERNAL 3
#define AVCC_EXTERNAL_CAPACITOR_AREF_PIN 1

#define CHANNEL_ADC0 0
#define CHANNEL_ADC1 1
#define CHANNEL_ADC2 2
#define CHANNEL_ADC3 3
#define CHANNEL_ADC4 4
#define CHANNEL_ADC5 5
#define CHANNEL_ADC6 6
#define CHANNEL_ADC7 7

#define ADC_PRESCALER_0 0
#define ADC_PRESCALER_2 1
#define ADC_PRESCALER_4 2
#define ADC_PRESCALER_8 3
#define ADC_PRESCALER_16 4
#define ADC_PRESCALER_32 5
#define ADC_PRESCALER_64 6
#define ADC_PRESCALER_128 7


#define LEFT_ADJUSTMENT 1
#define RIGHT_ADJUSTMENT 0

#define ADC_INTERRUPT_MODE 0
#define ADC_POLLING_MODE 1
#define ADC_AUTO_TRIGGER_MODE 2

#define ADC_AUTO_TRIGGER_MODE_FREE_RUNNING 0
#define ADC_AUTO_TRIGGER_MODE_EXT_INT0 2
#define ADC_AUTO_TRIGGER_MODE_TIMER0_CMP 3
#define ADC_AUTO_TRIGGER_MODE_TIMER0_OVF 4
#define ADC_AUTO_TRIGGER_MODE_TIMER0_ICU 7

/******************************************************************************
 * _______________________FUNCTION_PROTOTYPES__________________________________
 *
 ******************************************************************************/

EN_ERRORSTATE_t ADC_Init(str_ADC_config_t*confg_s);

void ADC_readChannel(uint8_t channel_num);

#endif /* MCAL_ADC_ADC_H_ */
