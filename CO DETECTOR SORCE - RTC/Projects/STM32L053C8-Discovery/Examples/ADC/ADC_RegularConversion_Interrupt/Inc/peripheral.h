#ifndef __PERIPHERAL_H
#define __PERIPHERAL_H

#include "main.h"

extern uint8_t setGainExe(char *cmd);
extern uint8_t setOffsetExe(char *cmd);
extern uint8_t setDateExe(char *cmd);
extern uint8_t queryExe(char *cmd);

extern void serialCommandHandle(void);

#endif

