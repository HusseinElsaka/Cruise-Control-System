#include "motor.h"

EN_ERRORSTATE_t MOTOR_init(uint8_t motorPort, uint8_t motorPin)
{
	if(DIO_setPinDirection(buttonPort, buttonPin,HIGH) == 0)
	{
		return E_OK;
	}
	return E_ERROR;
}

EN_ERRORSTATE_t MOTOR_read(uint8_t motorPort, uint8_t motorPin, uint8_t *value)
{
	*value = DIO_getPin(buttonPort, buttonPin);
	return E_OK;
}


EN_ERRORSTATE_t MOTOR_start()
{
	MOTOR_init(PORT_motor,MOTOR);

	return E_OK;
}
