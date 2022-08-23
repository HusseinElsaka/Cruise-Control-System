/*
 * USART.h
 *
 *  Created on: Aug 22, 2022
 *      Author: PClaptop
 */

#ifndef MCAL_USART_USART_H_
#define MCAL_USART_USART_H_

#include "../../Utilites/BitMath.h"
#include "../../Utilites/Memmap.h"
#include "../../Utilites/Datatypes.h"

#define F_CPU 8000000UL			// Define frequency here its 8MHz
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


void UART_init();
void UART_TxChar( u8_t ch);
u8_t UART_RxChar();
void UART_SendString(char *str);
#endif /* MCAL_USART_USART_H_ */
