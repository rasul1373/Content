/*
 * Project   : ADXL345
 * File      : ADXL345.c
 * Author    : Zagros Electronic
 * Date      : 1404-06-30
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */


#include "ADXL345.h"

void ADXL345_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t data;

    // Measure
    data = MEASURE_MODE;
    HAL_I2C_Mem_Write(hi2c, ADXL345_ADDR, REG_POWER_CTL, 1, &data, 1, 100);

    //  ±2g
    ADXL345_SetRange(hi2c, RANGE_2G);

    //  100Hz
    ADXL345_SetDataRate(hi2c, 0x0A);
}

void ADXL345_SetRange(I2C_HandleTypeDef *hi2c, uint8_t range)
{
    uint8_t format;
    HAL_I2C_Mem_Read(hi2c, ADXL345_ADDR, REG_DATA_FORMAT, 1, &format, 1, 100);
    format &= ~0x0F;
    format |= range;
    format |= 0x08; // Full Resolution
    HAL_I2C_Mem_Write(hi2c, ADXL345_ADDR, REG_DATA_FORMAT, 1, &format, 1, 100);
}

void ADXL345_SetDataRate(I2C_HandleTypeDef *hi2c, uint8_t rate)
{
    HAL_I2C_Mem_Write(hi2c, ADXL345_ADDR, REG_BW_RATE, 1, &rate, 1, 100);
}

void ADXL345_ReadXYZ(I2C_HandleTypeDef *hi2c, ADXL345_Data_t *data)
{
    uint8_t buf[6];
    HAL_I2C_Mem_Read(hi2c, ADXL345_ADDR, REG_DATAX0, 1, buf, 6, 100);
    data->X = (int16_t)((buf[1] << 8) | buf[0]);
    data->Y = (int16_t)((buf[3] << 8) | buf[2]);
    data->Z = (int16_t)((buf[5] << 8) | buf[4]);
}

void ADXL345_EnableInterrupts(I2C_HandleTypeDef *hi2c)
{
    uint8_t data;

    //  Data Ready + Tap + FreeFall + Activity + Inactivity
    data = 0x2F;
    HAL_I2C_Mem_Write(hi2c, ADXL345_ADDR, REG_INT_ENABLE, 1, &data, 1, 100);

    //  INT1
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, ADXL345_ADDR, REG_INT_MAP, 1, &data, 1, 100);
}
