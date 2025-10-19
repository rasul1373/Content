/*
 * Project   : ADXL345
 * File      : ADXL345.c
 * Author    : Zagros Electronic
 * Date      : 1404-06-30
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */

#ifndef __ADXL345_H
#define __ADXL345_H

#include "stm32f1xx_hal.h"


#define ADXL345_ADDR        (0x53 << 1)


#define REG_DEVID           0x00
#define REG_POWER_CTL       0x2D
#define REG_DATA_FORMAT     0x31
#define REG_DATAX0          0x32
#define REG_DATAY0          0x34
#define REG_DATAZ0          0x36
#define REG_BW_RATE         0x2C
#define REG_INT_ENABLE      0x2E
#define REG_INT_MAP         0x2F
#define REG_INT_SOURCE      0x30
#define REG_THRESH_TAP      0x1D
#define REG_DUR             0x21
#define REG_LATENT          0x22
#define REG_WINDOW          0x23
#define REG_THRESH_ACT      0x24
#define REG_THRESH_INACT    0x25
#define REG_TIME_INACT      0x26
#define REG_ACT_INACT_CTL   0x27
#define REG_THRESH_FF       0x28
#define REG_TIME_FF         0x29

#define MEASURE_MODE        0x08
#define RANGE_2G            0x00
#define RANGE_4G            0x01
#define RANGE_8G            0x02
#define RANGE_16G           0x03

typedef struct {
    int16_t X;
    int16_t Y;
    int16_t Z;
    uint8_t DataReady;
    uint8_t SingleTap;
    uint8_t DoubleTap;
    uint8_t FreeFall;
    uint8_t Activity;
    uint8_t Inactivity;
} ADXL345_Data_t;



void ADXL345_Init(I2C_HandleTypeDef *hi2c);
void ADXL345_SetRange(I2C_HandleTypeDef *hi2c, uint8_t range);
void ADXL345_SetDataRate(I2C_HandleTypeDef *hi2c, uint8_t rate);
void ADXL345_ReadXYZ(I2C_HandleTypeDef *hi2c, ADXL345_Data_t *data);
void ADXL345_EnableInterrupts(I2C_HandleTypeDef *hi2c);

#endif
