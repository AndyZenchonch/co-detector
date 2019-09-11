#ifndef __IGNITIONDRIVER_H
#define __IGNITIONDRIVER_H

#include "main.h"

#define __MODE_GPIO				1				//普通IO口
#define __MODE_EXIT				0				//外部中断

extern void ignitionWakeupPinConfig(uint8_t mode);
extern void ignitionConfig(void);

#endif

