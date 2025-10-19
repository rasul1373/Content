/*
 * Project   : GY30
 * File      : GY30.h
 * Author    : Zagros Electronic
 * Date      : 1404-07-27
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */
   
#ifndef INC_GY30_H_
#define INC_GY30_H_

#include "stm32f1xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

#define GY30_ADDR          0x23 << 1  

// BH1750
#define POWER_DOWN         0x00
#define POWER_ON           0x01
#define RESET_SENSOR       0x07
#define CONT_H_RES_MODE    0x10
#define CONT_H_RES_MODE2   0x11
#define CONT_L_RES_MODE    0x13
#define ONE_TIME_H_RES     0x20
#define ONE_TIME_H_RES2    0x21
#define ONE_TIME_L_RES     0x23

void GY30_Init(void);
uint8_t GY30_ReadLight(float *lux);

#endif /* INC_GY30_H_ */
