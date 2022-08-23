
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "../../Utilites/BitMath.h"
#include "../../Utilites/Memmap.h"
#include "../../Utilites/DataTypes.h"


/************************************************************************/
/* Interrupt Vector                                                     */
/************************************************************************/

/* External Interrupt Vector */
/* External Interrupt Request 0 */
#define EXT_INT_0 __vector_1
/* External Interrupt Request 1 */
#define EXT_INT_1 __vector_2
/* External Interrupt Request 2 */
#define EXT_INT_2 __vector_3

/* Timer Interrupt Vector */

/*Timer 2*/
/* Timer/Counter2 Compare Match */
#define TIMER2_COMP __vector_4
/* Timer/Counter2 Overflow */
#define TIMER2_OVF __vector_5

/*Timer 1*/
/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT __vector_6
/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA __vector_7
/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB __vector_8
/* Timer/Counter1 Overflow */
#define TIMER1_OVF __vector_9

/*Timer 0*/
/* Timer/Counter0 Compare Match */
#define TIMER0_COMP __vector_10
/* Timer/Counter0 Overflow */
#define TIMER0_OVF __vector_11

#define USART_RXC __vector_13

#define ADC_VECT __vector_16

/* Set Global Interrupt, Set the I-bit in status register to 1 */
#define sei() __asm__ __volatile__ ("sei" ::: "memory")

/* Clear Global Interrupt, Set the I-bit in status register to 0 */
#define cli() __asm__ __volatile__ ("cli" ::: "memory")

/* ISR definition */
#define ISR(INT_VECT)void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)

#define INT_EN 7
#define INT_FAILING 0
#define INT_RISING 1
#define INT_LOGIC_CHANGE 2

/* Brief : Using this function to enable Interrupt
 * INTUPT : //
 * RETURN OK OR ERROR OF EXCUTE */
EN_ERRORSTATE_t Enable_INT(void);

/* Brief : Using this function to enable Interrupt 1
 * INTUPT : u8 --> FAILING OR RISING
 * RETURN OK OR ERROR OF EXCUTE */
EN_ERRORSTATE_t Enable_INT0 (u8_t INT_STATE);

/* Brief : Using this function to enable Interrupt 1
 * INTUPT : u8 --> FAILING OR RISING
 * RETURN OK OR ERROR OF EXCUTE */
EN_ERRORSTATE_t Enable_INT1 (u8_t INT_STATE);

/* Brief : Using this function to enable Interrupt 1
 * INTUPT : u8 --> FAILING OR RISING
 * RETURN OK OR ERROR OF EXCUTE */
EN_ERRORSTATE_t Enable_INT2 (u8_t INT_STATE);



#endif /* INTERRUPT_H_ */

