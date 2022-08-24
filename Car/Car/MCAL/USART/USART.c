/*
 * USART.c
 *
 *  Created on: Aug 22, 2022
 *      Author: PClaptop
 */
#include "USART.h"



void UART_init()
{
	

	//Enable transmission and reception by using the UCSRB register.
	SET_BIT(UCSRB,TXEN);//TXEN
	SET_BIT(UCSRB,RXEN);
	//Set data bit size to 8 bit by using the UCSRC register.
	SET_BIT(UCSRC,URSEL);
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);

	//Set baud rate using the UBRR register.
	UBRRL = BAUD_PRESCALE;		/* Load lower 8-bits of the baud rate value */
	UBRRH = (BAUD_PRESCALE >> 8);	/* Load upper 8-bits*/

}

void UART_TxChar(u8_t ch)
{
	while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/
	UDR = ch ;
}

u8_t UART_RxChar()
{
	while (!(UCSRA & (1 << RXC)));/* Wait till data is received */
	return(UDR);		/* Return the byte */
}

void UART_SendString(char *str)
{
	unsigned char j=0;

	while (str[j]!=0)		/* Send string till null */
	{
		UART_TxChar(str[j]);
		j++;
	}
}
