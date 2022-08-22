/*
 * adc.c
 *
 * Created: 17-Aug-22 3:21:47 PM
 *  Author: sonat
 */ 
#include "adc.h"
uint8_t isLeftAdjustment = 0;
uint8_t isPolling = 0;
uint16_t gu8_ADC_reading = 0;

EN_ERRORSTATE_t ADC_Init(str_ADC_config_t*confg_s)
{
	/*
	in register --> ADMUX 
	Voltage Reference Selections for ADC
	REFS1	REFS0		Voltage Reference Selection
		0		0		AREF, Internal Vref turned off
		0		1		AVCC with external capacitor at AREF pin
		1		0		Reserved
		1		1		Internal 2.56V Voltage Reference with external capacitor at AREF pin
	*/
	switch(confg_s->u8_voltage)
	{
		case INTERNAL_VREF_OFF:
		CLR_BIT(ADMUX, REFS1);CLR_BIT(ADMUX, REFS0);
		break;
		case INTERNAL_VREF_2_56_EXTERNAL_INTERNAL:
		ADMUX |= (1 << REFS0) | (1 << REFS1);
		break;
		case AVCC_EXTERNAL_CAPACITOR_AREF_PIN:
		ADMUX |= (1 << REFS0);
		break;
		default:
		return E_ERROR;
	}
	
	/*
	in register --> ADMUX 
	 ADLAR: ADC Left Adjust Result
	 --> 1 --> ADCH + last two bits in ADCL --> LEFT_ADJUSTMENT
	 --> 0 --> first two bits in ADCH + ADCL --> RIGHT_ADJUSTMENT
	*/
	switch(confg_s->u8_ADC_Adjustment)
	{
		case LEFT_ADJUSTMENT:
		isLeftAdjustment = LEFT_ADJUSTMENT;
		ADMUX |= (1 << ADLAR);
		break;
		case RIGHT_ADJUSTMENT:
		isLeftAdjustment = RIGHT_ADJUSTMENT;
		CLR_BIT(ADMUX,ADLAR);
		break;
		default:
		return E_ERROR;
	}
	
	/*
	 Input Channel and Gain Selections
	 MUX4..0	SingleEndedInput	PositiveDifferentialInput	NegativeDifferentialInput Gain
	 00000		ADC0
	 00001		ADC1
	 00010		ADC2
	 00011		ADC3							N/A
	 00100		ADC4
	 00101		ADC5
	 00110		ADC6
	 00111		ADC7
	 01000								ADC0						ADC0					10x
	 01001								ADC1						ADC0					10x
	 01010(1)							ADC0						ADC0					200x
	 01011(1)							ADC1						ADC0					200x
	 01100								ADC2						ADC2					10x
	 01101								ADC3						ADC2					10x
	 01110(1)							ADC2						ADC2					200x
	 01111(1)							ADC3						ADC2					200x
	 10000								ADC0						ADC1					1x
	 10001								ADC1						ADC1					1x
	 10010								ADC2						ADC1					1x
	 10011								ADC3						ADC1					1x
	 10100								ADC4						ADC1					1x
	 10101								ADC5						ADC1					1x
	 10110								ADC6						ADC1					1x
	 10111								ADC7						ADC1					1x
	 11000								ADC0						ADC2					1x
	 11001								ADC1						ADC2					1x
	 11010								ADC2						ADC2					1x
	 11011								ADC3						ADC2					1x
	 11100								ADC4						ADC2					1x 
	*/
	switch(confg_s->u8_ADC_Channel)
	{
		case CHANNEL_ADC0:
		CLR_BIT(ADMUX,MUX0);CLR_BIT(ADMUX,MUX1);CLR_BIT(ADMUX,MUX2);CLR_BIT(ADMUX,MUX3);CLR_BIT(ADMUX,MUX4);
		break;
		case CHANNEL_ADC1:
		ADMUX |= (1 << MUX0);
		break;
		case CHANNEL_ADC2:
		ADMUX |= (1 << MUX1);
		break;
		case CHANNEL_ADC3:
		ADMUX |= (1 << MUX1) || (1 << MUX0);
		break;
		case CHANNEL_ADC4:
		ADMUX |= (1 << MUX2);
		break;
		case CHANNEL_ADC5:
		ADMUX |= (1 << MUX2) | (1 << MUX0);
		break;
		case CHANNEL_ADC6:
		ADMUX |= (1 << MUX2) | (1 << MUX1);
		break;
		case CHANNEL_ADC7:
		ADMUX |= (1 << MUX2) | (1 << MUX1) |(1 << MUX0);
		break;
		default:
		return E_ERROR;
	}
	/*
	in ADCSRA register
	– ADPS2:0: ADC Prescaler Select Bits
	ADPS2 ADPS1 ADPS0	DivisionFactor
	0		0		0		2
	0		0		1		2
	0		1		0		4
	0		1		1		8
	1		0		0		16
	1		0		1		32
	1		1		0		64
	1		1		1		12
	*/
	switch (confg_s->u8_ADC_prescaler)
	{
		case ADC_PRESCALER_0:
		CLR_BIT(ADCSRA,ADPS2);CLR_BIT(ADCSRA,ADPS1);CLR_BIT(ADCSRA,ADPS0);
		break;
		case ADC_PRESCALER_2:
		ADCSRA |= (1 << ADPS0);
		break;
		case ADC_PRESCALER_4:
		ADCSRA |= (1 << ADPS1);
		break;
		case ADC_PRESCALER_8:
		ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
		break;
		case ADC_PRESCALER_16:
		ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
		break;
		case ADC_PRESCALER_32:
		ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
		break;
		case ADC_PRESCALER_64:
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
		break;
		case ADC_PRESCALER_128:
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
		break;
		default:
		return E_ERROR;
	}
	/*
	in ADCSRA register
	• Bit 3 – ADIE: ADC Interrupt Enable
	• Bit 5 – ADATE: ADC Auto Trigger Enable
	• Bit 6 – ADSC: ADC Start Conversion
	*/
	switch(confg_s->u8_ADC_Mode)
	{
		
		case ADC_INTERRUPT_MODE:
		isPolling = ADC_INTERRUPT_MODE;
		ADCSRA |= (1 << ADIE);
		ADCSRA |= (1 << ADSC);
		break;
		case ADC_POLLING_MODE:
		isPolling = ADC_POLLING_MODE;
		ADCSRA |= (1 << ADSC);
		break;
		case ADC_AUTO_TRIGGER_MODE:
		{
			ADCSRA |= (1 << ADATE);
			/*
			in register SFIOR
			ADC Auto Trigger Source Selections
			ADTS2	ADTS1 ADTS0		Trigger Source
			0		0		0		Free Running mode
			0		0		1		Analog Comparator
			0		1		0		External Interrupt Request 0
			0		1		1		Timer/Counter0 Compare Match
			1		0		0		Timer/Counter0 Overflow
			1		0		1		Timer/Counter Compare Match B
			1		1		0		Timer/Counter1 Overflow
			1		1		1		Timer/Counter1 Capture Event
			*/
			switch(confg_s->u8_ADC_triiger_mode)
			{
				case ADC_AUTO_TRIGGER_MODE_FREE_RUNNING:
				CLR_BIT(SFIOR,ADTS2);CLR_BIT(ADCSRA,ADTS1);CLR_BIT(ADCSRA,ADTS0);
				break;
				case ADC_AUTO_TRIGGER_MODE_EXT_INT0:
				SFIOR |= (1 << ADTS1);
				break;
				case ADC_AUTO_TRIGGER_MODE_TIMER0_CMP:
				SFIOR |= (1 << ADTS1) | (1 << ADTS0);
				break;
				case ADC_AUTO_TRIGGER_MODE_TIMER0_OVF:
				SFIOR |= (1 << ADTS2);
				break;
				case ADC_AUTO_TRIGGER_MODE_TIMER0_ICU:
				SFIOR |= (1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0);
				break;
				default:
				return E_ERROR;
			}
			break;
		}
		default:
		return E_ERROR;
	}
	ADCSRA |= (1 << ADEN);
	return E_OK;
}

void ADC_readChannel(u8_t channel_num)
{
	ADMUX |= (channel_num & 0x0f);
		
	if (isPolling == ADC_POLLING_MODE)
	{
		ADCSRA |= (1 << ADSC);
		while((ADCSRA&(1<<ADIF))==0);
	}
	
	if(isLeftAdjustment == LEFT_ADJUSTMENT)
	{
		gu8_ADC_reading = (ADC >> 6);
	}
	else if(isLeftAdjustment == RIGHT_ADJUSTMENT)
	{
		gu8_ADC_reading = ADC;
	}
	
	if (isPolling == ADC_INTERRUPT_MODE)
	{
		ADCSRA |= (1 << ADSC);
	}
}