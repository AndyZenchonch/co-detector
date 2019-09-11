#ifndef __HAL_LED_H
#define __HAL_LED_H

#include "main.h"
#include "stm32l0xx_hal_gpio.h"

#define 	LED_RED			0
#define		LED_GREEN		1

#define 	LED_ON			1
#define 	LED_OFF			0

extern void ledConfig(void);
extern void halLEDOnOff(uint8_t led, uint8_t en);

extern void opPowerConfig(void);

#endif
