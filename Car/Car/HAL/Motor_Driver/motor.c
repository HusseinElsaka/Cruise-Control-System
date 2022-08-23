#include "motor.h"

EN_ERRORSTATE_t MOTOR_init(uint8_t motorPort, uint8_t motorPin)
{
	if(DIO_setPinDirection(motorPort, motorPin,HIGH) == 0)
	{
		return E_OK;
	}
	return E_ERROR;
}

EN_ERRORSTATE_t MOTOR_read(uint8_t motorPort, uint8_t motorPin, uint8_t *value)
{
	*value = DIO_getPin(motorPort, motorPin);
	return E_OK;
}


EN_ERRORSTATE_t MOTOR_start()
{
	MOTOR_init(PORT_motor,MOTOR);

	return E_OK;
}

EN_ERRORSTATE_t speed_up()
{
	return E_OK;
}

EN_ERRORSTATE_t speed_down()
{
	return E_OK;
}

EN_ERRORSTATE_t speed_down_by_5()
{
	return E_OK;
}

EN_ERRORSTATE_t Max_speed()
{
	return E_OK;
}

EN_ERRORSTATE_t Zero_speed()
{
	return E_OK;
}

EN_ERRORSTATE_t half_of_speed()
{
	return E_OK;
}

EN_ERRORSTATE_t per_75_speed()
{
	return E_OK;
}
