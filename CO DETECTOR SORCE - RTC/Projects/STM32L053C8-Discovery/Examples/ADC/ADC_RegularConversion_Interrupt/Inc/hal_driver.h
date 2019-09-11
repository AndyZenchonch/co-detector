#ifndef __HAL_DRIVER_H
#define __HAL_DRIVER_H

#include "main.h"

#define	__CO_CHANNEL	1
#define __SEN_CHANNEL	2
#define __TEM_CHANNEL	3

#define VREFINT_CAL ((uint16_t*) ((uint32_t) 0x1FF80078))

//Lookup table for temperature compensation (index [0] = -10 deg C)
#define LOOKUP_LENGTH 61	
#define COMP_SHIFT 10 //to be able to compensate in negative temperatures

extern float vccVoltageValue;

extern uint32_t getAdcValue(uint8_t ch);

extern uint32_t getAdcChannelValue(uint8_t ch);

extern float getGasConcentration(float gain, float sens);

extern float getCompGasConcentration(float gasPpm, int8_t temp);
extern float Get_Temperature(void);

extern void refVoltageCalibration(void);

#endif
