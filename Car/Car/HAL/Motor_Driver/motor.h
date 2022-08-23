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

/* increase the speed of motor
   by 25% of current speed */
extern EN_ERRORSTATE_t speed_up();

/* decrease the speed of motor
   by 25% of current speed */
extern EN_ERRORSTATE_t speed_down();

/* decrease the speed of motor
   by 5% of current speed */
extern EN_ERRORSTATE_t speed_down_by_5();

/* the max speed of motor */
extern EN_ERRORSTATE_t Max_speed();

/* zero speed of motor */
extern EN_ERRORSTATE_t Zero_speed();

/* 50% of max speed of motor */
extern EN_ERRORSTATE_t half_of_speed();

/* 75% of max speed of motor */
extern EN_ERRORSTATE_t per_75_speed();


#endif /* MOTOR_H_ */
