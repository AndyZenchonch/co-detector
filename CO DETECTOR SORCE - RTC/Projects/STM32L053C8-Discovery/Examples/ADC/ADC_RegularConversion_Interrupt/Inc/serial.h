#ifndef __SERIAL_H
#define __SERIAL_H

#include "main.h"


#define SERIAL_RX				0
#define SERIAL_TX				1

extern uint8_t aRxBuffer[RXBUFFERSIZE];

extern void uartInit(void);

extern void serialConfig(uint8_t mode);
extern void serialPrintStr(uint8_t *str);

#endif

