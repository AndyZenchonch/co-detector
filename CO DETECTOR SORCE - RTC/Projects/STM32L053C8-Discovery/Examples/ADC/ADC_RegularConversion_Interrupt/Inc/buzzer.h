#ifndef __BUZZER_H
#define __BUZZER_H

#include "main.h"

#define __BUZZER_ON			1
#define __BUZZER_OFF		0

extern void buzzerConfig(void);
extern void halBuzzerOnOff(uint8_t en);

#endif

