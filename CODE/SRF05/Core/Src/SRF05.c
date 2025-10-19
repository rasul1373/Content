/*
 * Project   : SRF05
 * File      : SRF05.c
 * Author    : Zagros Electronic
 * Date      : 1404-06-30
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */
   
#include "srf05.h"

  static TIM_HandleTypeDef *htim_srf05;
  static uint32_t ic_val1 = 0;
  static uint32_t ic_val2 = 0;
  static uint8_t is_first_captured = 0;
  static uint32_t distance = 0;

void SRF05_Init(TIM_HandleTypeDef *htim)
{
    htim_srf05 = htim;
    HAL_TIM_IC_Start_IT(htim_srf05, TIM_CHANNEL_1);
}

void SRF05_Trigger(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    HAL_Delay(1); // حدود 10µs کافیه، اینجا کمی بیشتر گذاشتیم
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
}

uint32_t SRF05_GetDistance(void)
{
    return distance;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim_srf05->Instance)
    {
        if (is_first_captured == 0)
        {
            ic_val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

            // تغییر قطبیت به FALLING
            HAL_TIM_IC_Stop_IT(htim, TIM_CHANNEL_1);

            TIM_IC_InitTypeDef sConfigIC = {0};
            sConfigIC.ICPolarity  = TIM_INPUTCHANNELPOLARITY_FALLING;
            sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
            sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
            sConfigIC.ICFilter    = 0;
            HAL_TIM_IC_ConfigChannel(htim, &sConfigIC, TIM_CHANNEL_1);

            HAL_TIM_IC_Start_IT(htim, TIM_CHANNEL_1);

            is_first_captured = 1;
        }
        else
        {
            ic_val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

            uint32_t diff;
            if (ic_val2 >= ic_val1)
                diff = ic_val2 - ic_val1;
            else
                diff = (0xFFFF - ic_val1) + ic_val2;

            distance = diff / 58; // فاصله بر حسب سانتی‌متر

            // برگردوندن قطبیت به RISING
            HAL_TIM_IC_Stop_IT(htim, TIM_CHANNEL_1);

            TIM_IC_InitTypeDef sConfigIC = {0};
            sConfigIC.ICPolarity  = TIM_INPUTCHANNELPOLARITY_RISING;
            sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
            sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
            sConfigIC.ICFilter    = 0;
            HAL_TIM_IC_ConfigChannel(htim, &sConfigIC, TIM_CHANNEL_1);

            HAL_TIM_IC_Start_IT(htim, TIM_CHANNEL_1);

            is_first_captured = 0;
        }
    }
}
