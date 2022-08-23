#ifndef MOTOR_H_
#define MOTOR_H_

#include "../../MCAL/DIO Driver/dio.h"

#define C0	2
// motor pin
#define MOTOR C0
// motor port
#define PORT_motor PORT_C

/* Initialization the motor
input : take port and pin of motor
return OK or ERROR */
extern EN_ERRORSTATE_t MOTOR_init(uint8_t motorPort, uint8_t motorPin);

/* READ the motor
input : take port and pin of motor
output : the value on the pin
return OK or ERROR */
extern EN_ERRORSTATE_t MOTOR_read(uint8_t motorPort, uint8_t motorPin, uint8_t *value);

/* init the motor pins
input : no input
return OK or ERROR */
extern EN_ERRORSTATE_t MOTOR_start();

#endif /* MOTOR_H_ */