/*
 * Project   : AM2302
 * File      : AM2302.h
 * Author    : Zagros Electronic
 * Date      : 1404-07-20
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */


#ifndef AM2302
#define AM2302

#include "stm32f1xx_hal.h"

#define AM2302_PORT GPIOB
#define AM2302_PIN  GPIO_PIN_9

extern TIM_HandleTypeDef htim1; // ????? ?? ?? CubeMX ?????

void AM2302_Init(void);
uint8_t AM2302_Start(void);
uint8_t AM2302_ReadByte(void);

extern float AM2302_TemperatureC;
extern float AM2302_TemperatureF;
extern float AM2302_Humidity;

#endif /* AM2302 */
