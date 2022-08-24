#include "../../Utilites/BitMath.h"
#include "DIO.h"

EN_ERRORSTATE_t DIO_setPin(EN_portType_t portNum, u8_t pinNum, u8_t pinValue)
{
    EN_ERRORSTATE_t state;
    state = E_OK;

    if (pinValue == LOW)
    {
        switch (portNum)
        {
        case PORT_A:
            CLR_BIT(PORTA, pinNum);
            break;
        case PORT_B:
            CLR_BIT(PORTB, pinNum);
            break;
        case PORT_C:
            CLR_BIT(PORTC, pinNum);
            break;
        case PORT_D:
            CLR_BIT(PORTD, pinNum);
            break;
        default:
            state = E_ERROR;
            break;
        }
    }
    else if (pinValue == HIGH)
    {
        switch (portNum)
        {
        case PORT_A:
            SET_BIT(PORTA, pinNum);
            break;
        case PORT_B:
            SET_BIT(PORTB, pinNum);
            break;
        case PORT_C:
            SET_BIT(PORTC, pinNum);
            break;
        case PORT_D:
            SET_BIT(PORTD, pinNum);
            break;
        default:
            state = E_ERROR;
            break;
        }
    }
    return state;
}

EN_ERRORSTATE_t DIO_setPinDirection(EN_portType_t portNum, u8_t pinNum, u8_t pinDirection)
{
    EN_ERRORSTATE_t state;
    state = E_OK;

    if (pinDirection == LOW)
    {
        switch (portNum)
        {
        case PORT_A:
            CLR_BIT(DDRA, pinNum);
            break;
        case PORT_B:
            CLR_BIT(DDRB, pinNum);
            break;
        case PORT_C:
            CLR_BIT(DDRC, pinNum);
            break;
        case PORT_D:
            CLR_BIT(DDRD, pinNum);
            break;
        default:
            state = E_ERROR;
            break;
        }
    }
    else if (pinDirection == HIGH)
    {
        switch (portNum)
        {
        case PORT_A:
            SET_BIT(DDRA, pinNum);
            break;
        case PORT_B:
            SET_BIT(DDRB, pinNum);
            break;
        case PORT_C:
            SET_BIT(DDRC, pinNum);
            break;
        case PORT_D:
            SET_BIT(DDRD, pinNum);
            break;
        default:
            state = E_ERROR;
            break;
        }
    }
    return state;
}

EN_ERRORSTATE_t DIO_getPin(EN_portType_t portNum, u8_t pinNum)
{
    u8_t pinVal = 0;
    switch (portNum)
    {
    case PORT_A:
        pinVal = GET_BIT(PINA, pinNum);
        break;
    case PORT_B:
        pinVal = GET_BIT(PINB, pinNum);
        break;
    case PORT_C:
        pinVal = GET_BIT(PINC, pinNum);
        break;
    case PORT_D:
        pinVal = GET_BIT(PIND, pinNum);
        break;
    }
    return pinVal;
}

EN_ERRORSTATE_t DIO_toglePin(EN_portType_t portNum, u8_t pinNum)
{
    EN_ERRORSTATE_t state;
    state = E_OK;

    switch (portNum)
    {
    case PORT_A:
        TGL_BIT(PORTA, pinNum);
        break;
    case PORT_B:
        TGL_BIT(PORTB, pinNum);
        break;
    case PORT_C:
        TGL_BIT(PORTC, pinNum);
        break;
    case PORT_D:
        TGL_BIT(PORTD, pinNum);
        break;
    default:
        state = E_ERROR;
        break;
    }
    return state;
}

EN_ERRORSTATE_t DIO_setPortDirection(EN_portType_t portNum, u8_t portDirection)
{
    EN_ERRORSTATE_t state;
    state = E_OK;

    switch (portNum)
    {
    case PORT_A:
        DDRA = portDirection;
        break;
    case PORT_B:
        DDRB = portDirection;
        break;
    case PORT_C:
        DDRC = portDirection;
        break;
    case PORT_D:
        DDRD = portDirection;
        break;
    default:
        state = E_ERROR;
        break;
    }
    return state;
}

EN_ERRORSTATE_t DIO_setPortValue(EN_portType_t portNum, u8_t portValue)
{
    EN_ERRORSTATE_t state;
    state = E_OK;

    switch (portNum)
    {
    case PORT_A:
        PORTA = portNum;
        break;
    case PORT_B:
        PORTB = portNum;
        break;
    case PORT_C:
        PORTC = portNum;
        break;
    case PORT_D:
        PORTD = portNum;
        break;
    default:
        state = E_ERROR;
        break;
    }
    return state;
}

EN_ERRORSTATE_t DIO_pullUp(EN_portType_t portNum, u8_t pinNum)
{
    EN_ERRORSTATE_t state;
    state = E_OK;

    switch (portNum)
    {
    case PORT_A:
        CLR_BIT(DDRA, pinNum);
        SET_BIT(PORTA, pinNum);
        break;
    case PORT_B:
        CLR_BIT(DDRB, pinNum);
        SET_BIT(PORTB, pinNum);
        break;
    case PORT_C:
        CLR_BIT(DDRC, pinNum);
        SET_BIT(PORTC, pinNum);
        break;
    case PORT_D:
        CLR_BIT(DDRD, pinNum);
        SET_BIT(PORTD, pinNum);
        break;
    default:
        state = E_ERROR;
        break;
    }
    return state;
}

