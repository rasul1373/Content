/*
 * Project   : L298
 * File      : L298.c
 * Author    : Zagros Electronic
 * Date      : 1404-05-21
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */

#ifndef L298_H
#define L298_H
   
#include "main.h"
   
#define  INC_PIN    HAL_GPIO_ReadPin(GPIOA,inc_Pin) 
#define  DEC_PIN    HAL_GPIO_ReadPin(GPIOA,dec_Pin)
#define  SELECT_PIN HAL_GPIO_ReadPin(GPIOA,select_Pin) 
   
void m1_right(void);
void m2_right(void);
void m1_left(void);
void m2_left(void);
   
// Function prototypes here

#endif /* L298_H */
