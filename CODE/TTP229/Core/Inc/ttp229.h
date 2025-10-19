/*
 * Project   : TTP229
 * File      : TTP229.h
 * Author    : Zagros Electronic
 * Date      : 1404-07-20
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */
   
     
#ifndef __TTP229_MOD_H
#define __TTP229_MOD_H

#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include "main.h"  

extern uint8_t singleKey8;
extern uint8_t multiKeys8;
extern uint8_t singleKey16;
extern uint16_t multiKeys16;

uint8_t fetchKey8(void);
uint8_t peekKey8(void);
uint8_t fetchKeys8(void);
uint8_t peekKeys8(void);
uint8_t fetchKey16(void);
uint8_t peekKey16(void);
uint16_t fetchKeys16(void);
uint16_t peekKeys16(void);

void clkControl(GPIO_PinState state);  
GPIO_PinState readDataPin(void);       

void scanSingle8(void);       
void scanMultiple8(void);     
void scanSingle16(void);      
void scanMultiple16(void);    

bool readBit(void);           
bool detectTouch(void);       
void waitForPress(void);      

#endif 
