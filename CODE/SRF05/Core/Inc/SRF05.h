/*
 * Project   : SRF05
 * File      : SRF05.c
 * Author    : Zagros Electronic
 * Date      : 1404-06-30
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */

#ifndef SRF0X_H
#define SRF0X_H

#include <stdint.h>
#include "stm32f1xx_hal.h"


void SRF05_Init(TIM_HandleTypeDef *htim);
void SRF05_Trigger(void);
uint32_t SRF05_GetDistance(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);



#endif 