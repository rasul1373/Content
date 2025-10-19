/*
 * Project   : DS18B20
 * File      : DS18B20.c
 * Author    : Zagros Electronic
 * Date      : 1404-06-20
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */


#ifndef DS18B20_H
#define DS18B20_H

#include "stm32f1xx_hal.h"


#define DS18B20_PORT GPIOA
#define DS18B20_PIN GPIO_PIN_1

void DS18B20_SetPinOutput(void);
void DS18B20_SetPinInput(void);
uint8_t DS18B20_Reset(void);
void DS18B20_WriteBit(uint8_t bit);
uint8_t DS18B20_ReadBit(void);
void DS18B20_WriteByte(uint8_t data);
uint8_t DS18B20_ReadByte(void);
float DS18B20_GetTemp(void);

#endif
