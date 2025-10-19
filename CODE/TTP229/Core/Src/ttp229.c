/*
 * Project   : TTP229
 * File      : TTP229.c
 * Author    : Zagros Electronic
 * Date      : 1404-07-20
 * IAR version : 9.10.2
 * STM32CubeMX version : 6.15.0
 * STM32Cube package version : 1.8.6
 */


#include "main.h"
#include "ttp229.h"

uint8_t singleKey8 = 0, multiKeys8 = 0, singleKey16 = 0;
uint16_t multiKeys16 = 0;

uint8_t lastSingleKey8 = 0;
uint8_t lastMultiKeys8 = 0;
uint8_t lastSingleKey16 = 0;
uint16_t lastMultiKeys16 = 0;


void clkControl(GPIO_PinState state)
{
    HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, state);
}

GPIO_PinState readDataPin(void)
{
    return HAL_GPIO_ReadPin(SDO_GPIO_Port, SDO_Pin);
}

bool readBit(void)
{
    clkControl(GPIO_PIN_RESET);
    __NOP();                        
    bool result = !readDataPin();
    clkControl(GPIO_PIN_SET);
    return result;
}

bool detectTouch(void)
{
    uint16_t counter = 300;         
    while (readDataPin())
        if (--counter == 0) return false;

    counter = 300;
    while (!readDataPin())
        if (--counter == 0) return false;

    return true;
}

void waitForPress(void)
{
    while (readDataPin());
    while (!readDataPin());
}


uint8_t fetchKey8(void)
{
    waitForPress();
    scanSingle8();
    return singleKey8;
}

uint8_t peekKey8(void)
{
    if (detectTouch()) scanSingle8();
    return singleKey8;
}

uint8_t fetchKeys8(void)
{
    waitForPress();
    scanMultiple8();
    return multiKeys8;
}

uint8_t peekKeys8(void)
{
    if (detectTouch()) scanMultiple8();
    return multiKeys8;
}

uint8_t fetchKey16(void)
{
    waitForPress();
    scanSingle16();
    return singleKey16;
}

uint8_t peekKey16(void)
{
    if (detectTouch()) scanSingle16();
    return singleKey16;
}

uint16_t fetchKeys16(void)
{
    waitForPress();
    scanMultiple16();
    return multiKeys16;
}

uint16_t peekKeys16(void)
{
    if (detectTouch()) scanMultiple16();
    return multiKeys16;
}

//---------------------- Internal Scanning ----------------------

void scanSingle8(void)
{
    uint8_t key = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (readBit()) key = i + 1;
    }
    if (key != 0) lastSingleKey8 = key;
    singleKey8 = (key != 0) ? key : lastSingleKey8;
}

void scanMultiple8(void)
{
    uint8_t keys = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (readBit()) keys |= 1 << i;
    }
    if (keys != 0) lastMultiKeys8 = keys;
    multiKeys8 = (keys != 0) ? keys : lastMultiKeys8;
}

void scanSingle16(void)
{
    uint8_t key = 0;
    for (uint8_t i = 0; i < 16; i++)
    {
        if (readBit()) key = i + 1;
    }
    if (key != 0) lastSingleKey16 = key;
    singleKey16 = (key != 0) ? key : lastSingleKey16;
}

void scanMultiple16(void)
{
    uint16_t keys = 0;
    for (uint8_t i = 0; i < 16; i++)
    {
        if (readBit()) keys |= 1 << i;
    }
    if (keys != 0) lastMultiKeys16 = keys;
    multiKeys16 = (keys != 0) ? keys : lastMultiKeys16;
}
