/*
 * Project   : L298
 * File      : L298.c
 * Author    : Zagros Electronic
 * Date      : 1404-05-21
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */

#include "L298.h"

// Function implementations here
   
   void m1_right(void)
   {
     HAL_GPIO_WritePin(GPIOB,IN1_Pin,GPIO_PIN_SET);
     HAL_GPIO_WritePin(GPIOB,IN2_Pin,GPIO_PIN_RESET);
   }
   void m2_right(void)
   {
     HAL_GPIO_WritePin(GPIOB,IN3_Pin,GPIO_PIN_SET);
     HAL_GPIO_WritePin(GPIOB,IN4_Pin,GPIO_PIN_RESET);
   }   
   void m1_left(void)
   {
     HAL_GPIO_WritePin(GPIOB,IN1_Pin,GPIO_PIN_RESET);
     HAL_GPIO_WritePin(GPIOB,IN2_Pin,GPIO_PIN_SET);
   }   
   void m2_left(void)
   {
     HAL_GPIO_WritePin(GPIOB,IN3_Pin,GPIO_PIN_RESET);
     HAL_GPIO_WritePin(GPIOB,IN4_Pin,GPIO_PIN_SET);
   }  

/* End of File */


