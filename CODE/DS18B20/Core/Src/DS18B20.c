/*
 * Project   : DS18B20
 * File      : DS18B20.c
 * Author    : Zagros Electronic
 * Date      : 1404-06-20
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */


#include "ds18b20.h"
#include "main.h"


extern TIM_HandleTypeDef htim2;
void delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (__HAL_TIM_GET_COUNTER(&htim2) < us);
}


void DS18B20_SetPinOutput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DS18B20_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);
}

void DS18B20_SetPinInput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DS18B20_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);
}


uint8_t DS18B20_Reset(void)
{
    uint8_t response = 0;
    DS18B20_SetPinOutput();
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    delay_us(480);
    DS18B20_SetPinInput();
    delay_us(60);
    if (!HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN)) response = 1;
    delay_us(420);
    return response;
}


void DS18B20_WriteBit(uint8_t bit)
{
    DS18B20_SetPinOutput();
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    if(bit)
    {
        delay_us(1);
        DS18B20_SetPinInput();
        delay_us(60);
    }
    else
    {
        delay_us(60);
        DS18B20_SetPinInput();
    }
}


uint8_t DS18B20_ReadBit(void)
{
    uint8_t value = 0;
    DS18B20_SetPinOutput();
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    delay_us(2);
    DS18B20_SetPinInput();
    delay_us(10);
    if(HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN)) value = 1;
    delay_us(50);
    return value;
}


void DS18B20_WriteByte(uint8_t data)
{
    for(int i=0; i<8; i++)
    {
        DS18B20_WriteBit(data & 0x01);
        data >>= 1;
    }
}


uint8_t DS18B20_ReadByte(void)
{
    uint8_t value = 0;
    for(int i=0; i<8; i++)
    {
        value >>= 1;
        if(DS18B20_ReadBit()) value |= 0x80;
    }
    return value;
}


float DS18B20_GetTemp(void)
{
    uint8_t temp_l, temp_h;
    int16_t temp;
    float temperature = 0;

    DS18B20_Reset();
    DS18B20_WriteByte(0xCC); // Skip ROM
    DS18B20_WriteByte(0x44); // Convert 
    HAL_Delay(750);          

    DS18B20_Reset();
    DS18B20_WriteByte(0xCC); // Skip ROM
    DS18B20_WriteByte(0xBE); // Read Scratchpad

    temp_l = DS18B20_ReadByte();
    temp_h = DS18B20_ReadByte();
    temp = (temp_h << 8) | temp_l;
    temperature = (float)temp / 16.0;

    return temperature;
}
