/*
 * Project   : AM2302
 * File      : AM2302.c
 * Author    : Zagros Electronic
 * Date      : 1404-07-20
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */


#include "AM2302.h"

extern uint8_t RH1, RH2, TC1, TC2, SUM, CHECK;
extern  uint32_t pMillis, cMillis;

float AM2302_TemperatureC = 0;
float AM2302_TemperatureF = 0;
float AM2302_Humidity = 0;

static void microDelay(uint16_t delay)
{
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    while (__HAL_TIM_GET_COUNTER(&htim1) < delay);
}

void AM2302_Init(void)
{
    HAL_TIM_Base_Start(&htim1);  
}

uint8_t AM2302_Start(void)
{
    uint8_t Response = 0;
    GPIO_InitTypeDef GPIO_InitStructPrivate = {0};

    
    GPIO_InitStructPrivate.Pin = AM2302_PIN;
    GPIO_InitStructPrivate.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructPrivate.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructPrivate.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(AM2302_PORT, &GPIO_InitStructPrivate);

    HAL_GPIO_WritePin(AM2302_PORT, AM2302_PIN, GPIO_PIN_RESET);   
    microDelay(1300); // 1.3ms
    HAL_GPIO_WritePin(AM2302_PORT, AM2302_PIN, GPIO_PIN_SET);  
    microDelay(30);

    
    GPIO_InitStructPrivate.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructPrivate.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(AM2302_PORT, &GPIO_InitStructPrivate);

    microDelay(40);
    if (!(HAL_GPIO_ReadPin(AM2302_PORT, AM2302_PIN)))
    {
        microDelay(80);
        if ((HAL_GPIO_ReadPin(AM2302_PORT, AM2302_PIN))) Response = 1;
    }

    pMillis = HAL_GetTick();
    cMillis = HAL_GetTick();
    while ((HAL_GPIO_ReadPin(AM2302_PORT, AM2302_PIN)) && pMillis + 2 > cMillis)
    {
        cMillis = HAL_GetTick();
    }

    return Response;
}

uint8_t AM2302_ReadByte(void)
{
    uint8_t a, b=0;
    for (a=0; a<8; a++)
    {
        pMillis = HAL_GetTick();
        cMillis = HAL_GetTick();
        while (!(HAL_GPIO_ReadPin(AM2302_PORT, AM2302_PIN)) && pMillis + 2 > cMillis)
        {
            cMillis = HAL_GetTick();
        }
        microDelay(40);
        if (!(HAL_GPIO_ReadPin(AM2302_PORT, AM2302_PIN)))
            b &= ~(1<<(7-a));
        else
            b |= (1<<(7-a));

        pMillis = HAL_GetTick();
        cMillis = HAL_GetTick();
        while ((HAL_GPIO_ReadPin(AM2302_PORT, AM2302_PIN)) && pMillis + 2 > cMillis)
        {
            cMillis = HAL_GetTick();
        }
    }
    return b;
}
