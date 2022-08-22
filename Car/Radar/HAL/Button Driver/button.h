

#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO Driver/dio.h"

#define BUTTON_HIGH 1
#define BUTTON_LOW 0


/* Initialization the button
input : take port and pin of button
return OK or ERROR */
extern EN_ERRORSTATE_t BUTTON_init(uint8_t buttonPort, uint8_t buttonPin);

/* READ the button
input : take port and pin of button
output : the value on the pin
return OK or ERROR */
extern EN_ERRORSTATE_t BUTTON_read(uint8_t buttonPort, uint8_t buttonPin, uint8_t *value);
 
 

#endif /* BUTTON_H_ */