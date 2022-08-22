
#include "button.h"



EN_ERRORSTATE_t BUTTON_init(uint8_t buttonPort, uint8_t buttonPin)
{
	if(DIO_setPinDirection(buttonPort, buttonPin, HIGH) == 0)
	{
		return E_OK;
	}
	return E_ERROR;
}

EN_ERRORSTATE_t BUTTON_read(uint8_t buttonPort, uint8_t buttonPin, uint8_t *value)
{
	*value = DIO_getPin(buttonPort, buttonPin);
	return E_OK;
}


