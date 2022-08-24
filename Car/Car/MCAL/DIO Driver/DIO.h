#ifndef DIO_H_
#define DIO_H_

#include "../../Utilites/Memmap.h"
#include "../../Utilites/DataTypes.h"
#include "../../Utilites/BitMath.h"

typedef enum {
	PORT_A=0,
	PORT_B,
	PORT_C,
	PORT_D
}EN_portType_t;


#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define HIGH 1
#define LOW 0

EN_ERRORSTATE_t DIO_setPin(EN_portType_t portNum, u8_t pinNum, u8_t pinValue);
EN_ERRORSTATE_t DIO_setPinDirection(EN_portType_t portNum, u8_t pinNum, u8_t pinDirection);
EN_ERRORSTATE_t DIO_getPin(EN_portType_t portNum, u8_t pinNum);
EN_ERRORSTATE_t DIO_toglePin(EN_portType_t portNum, u8_t pinNum);
EN_ERRORSTATE_t DIO_setPortDirection(EN_portType_t portNum, u8_t portDirection);
EN_ERRORSTATE_t DIO_setPortValue(EN_portType_t portNum, u8_t portValue);
EN_ERRORSTATE_t DIO_pullUp(EN_portType_t portNum, u8_t pinNum);

#endif
