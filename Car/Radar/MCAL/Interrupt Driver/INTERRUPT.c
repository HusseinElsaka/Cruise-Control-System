#include "INTERRUPT.h"


EN_ERRORSTATE_t Enable_INT(void)
{
	SET_BIT(SREG,INT_EN);
	return E_OK;
}



/* Bit 1, 0 – ISC01, ISC00: Interrupt Sense Control 0 Bit 1 and Bit 0
The External Interrupt 0 is activated by the external pin INT0 if the SREG I-flag and the
corresponding interrupt mask are set. The level and edges on the external INT0 pin that
activate the interrupt are defined in Table 35. The value on the INT0 pin is sampled
before detecting edges. If edge or toggle interrupt is selected, pulses that last longer
than one clock period will generate an interrupt. Shorter pulses are not guaranteed to
generate an interrupt. If low level interrupt is selected, the low level must be held until
the completion of the currently executing instruction to generate an interrupt

 Interrupt 0 Sense Control
ISC01 ISC00 Description
0 		0	The low level of INT0 generates an interrupt request.
0 		1 	Any logical change on INT0 generates an interrupt request.
1 		0 	The falling edge of INT0 generates an interrupt request.
1 		1 	The rising edge of INT0 generates an interrupt request
 */
EN_ERRORSTATE_t Enable_INT0(u8_t INT_STATE)
{
	SET_BIT(SREG,INT_EN);
	SET_BIT(GICR,INT0);
	if(INT_STATE == INT_FAILING)
	{
		SET_BIT(MCUCR,ISC01);
		CLR_BIT(MCUCR,ISC00);
	}
	else if(INT_STATE == INT_RISING)
	{
		SET_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);
	}
	else
	{
		return E_ERROR;
	}

	return E_OK;

}

/* Bit 3, 2 – ISC11, ISC10: Interrupt Sense Control 1 Bit 1 and Bit 0
The External Interrupt 1 is activated by the external pin INT1 if the SREG I-bit and the
corresponding interrupt mask in the GICR are set. The level and edges on the external
INT1 pin that activate the interrupt are defined in Table 34. The value on the INT1 pin is
sampled before detecting edges. If edge or toggle interrupt is selected, pulses that last
longer than one clock period will generate an interrupt. Shorter pulses are not guaranteed to generate an interrupt. If low level interrupt is selected, the low level must be held
until the completion of the currently executing instruction to generate an interrupt.
Bit 7 6 5 4 3 2 1 0
SE SM2 SM1 SM0 ISC11 ISC10 ISC01 ISC00 MCUCR
Read/Write R/W R/W R/W R/W R/W R/W R/W R/W
Initial Value 0 0 0 0 0 0 0 0
Table 34. Interrupt 1 Sense Control
ISC11 ISC10 Description
0 		0 	The low level of INT1 generates an interrupt request.
0 		1 	Any logical change on INT1 generates an interrupt request.
1 		0 	The falling edge of INT1 generates an interrupt request.
1 		1 	The rising edge of INT1 generates an interrupt request*/
EN_ERRORSTATE_t Enable_INT1(u8_t INT_STATE)
{
	SET_BIT(SREG,INT_EN);
	SET_BIT(GICR,INT1);
	if(INT_STATE == INT_FAILING)
	{
		CLR_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);
	}
	else if(INT_STATE == INT_RISING)
	{
		SET_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);
	}
	else if (INT_STATE == INT_LOGIC_CHANGE)
	{
		SET_BIT(MCUCR,ISC10);
		CLR_BIT(MCUCR,ISC11);
	}
	else
	{
		return E_ERROR;
	}
	return E_OK;
}

/*Interrupt Sense Control 2
The Asynchronous External Interrupt 2 is activated by the external pin INT2 if the SREG
I-bit and the corresponding interrupt mask in GICR are set. If ISC2 is written to zero, a
falling edge on INT2 activates the interrupt. If ISC2 is written to one, a rising edge on
INT2 activates the interrupt. Edges on INT2 are registered asynchronously. Pulses on
INT2 wider than the minimum pulse width given in Table 36 will generate an interrupt.
Shorter pulses are not guaranteed to generate an interrupt. When changing the ISC2
bit, an interrupt can occur. Therefore, it is recommended to first disable INT2 by clearing
its Interrupt Enable bit in the GICR Register. Then, the ISC2 bit can be changed. Finally,
the INT2 Interrupt Flag should be cleared by writing a logical one to its Interrupt Flag bit
(INTF2) in the GIFR Register before the interrupt is re-enabled*/
EN_ERRORSTATE_t Enable_INT2(u8_t INT_STATE)
{
	SET_BIT(SREG,INT_EN);
	SET_BIT(GICR,INT2);
	if(INT_STATE == INT_FAILING)
	{
		CLR_BIT(MCUCSR,ISC2);
	}
	else if(INT_STATE == INT_RISING)
	{
		SET_BIT(MCUCSR,ISC2);
	}
	else
	{
		return E_ERROR;
	}
	return E_OK;

}



