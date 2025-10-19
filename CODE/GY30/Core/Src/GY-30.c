/*
 * Project   : GY30
 * File      : GY30.c
 * Author    : Zagros Electronic
 * Date      : 1404-07-27
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */
   
#include "GY-30.h"

void GY30_Init(void)
{
    
    uint8_t cmd = POWER_ON;
    HAL_I2C_Master_Transmit(&hi2c1, GY30_ADDR, &cmd, 1, HAL_MAX_DELAY);
    
    
    cmd = RESET_SENSOR;
    HAL_I2C_Master_Transmit(&hi2c1, GY30_ADDR, &cmd, 1, HAL_MAX_DELAY);
    
    //  High-Resolution Continuous
    cmd = CONT_H_RES_MODE;
    HAL_I2C_Master_Transmit(&hi2c1, GY30_ADDR, &cmd, 1, HAL_MAX_DELAY);
}

//  (Lux)
uint8_t GY30_ReadLight(float *lux)
{
    uint8_t buf[2];
    if(HAL_I2C_Master_Receive(&hi2c1, GY30_ADDR, buf, 2, HAL_MAX_DELAY) != HAL_OK)
        return 1; // error
    
    uint16_t raw = (buf[0] << 8) | buf[1];
    *lux = raw / 1.2; // convert Lux
    return 0;
}
