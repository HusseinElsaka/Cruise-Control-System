/**
 * @file DataTypes.h
 * @author Elgharib
 * @brief 
 * @version 0.1
 * @date 2021-07-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _DATATYPES_H_ // if not define
#define _DATATYPES_H_

#include <stdint.h>

typedef unsigned char           u8_t;
typedef signed char             s8_t;
typedef unsigned short int      u16_t;
typedef signed short int        s16_t;
typedef unsigned long int       u32_t;
typedef signed long int         s32_t;
typedef unsigned long long int  u64_t;
typedef signed long long int    s64_t;
typedef unsigned char			uint8_t;


#define NULLPTR (void*)0

typedef enum
{
    E_ERROR,
    E_OK
}EN_ERRORSTATE_t;

#endif
