#include "peripheral.h"
#include "string.h"
#include "serial.h"
#include "memory.h"
#include "stdlib.h"

typedef uint8_t (*interfaceCmdCB_t)(char *cmd);

typedef struct{
	char *cmdStr;
	interfaceCmdCB_t executeCMD;
}cmdParser_t;

const cmdParser_t cmdArray[] = {
	{"GAIN=", setGainExe},
	{"OFFSET=", setOffsetExe},
	{"DATE=", setDateExe},
	{"QUERY", queryExe}
};

static char cmdStrBuf[200] = {'\0'};
static char buffer[100] = {'\0'};


//GAIN=000001；
uint8_t setGainExe(char *cmd){
	uint8_t i = 0, j = 0;
	
	memset(buffer, 0, 100);
	
	for(i = 5; (cmd[i] >= '0' ) && (cmd[i]) <= '9'; i++ ){
		buffer[j++] = cmd[i];
	}
	
	systemConfig.sensor.gain = atof(buffer);
	
	putSensorDataToFlash();
	
	serialPrintStr((uint8_t *)"OK\r\n");
	return 0;
}

//OFFSET=1280
uint8_t setOffsetExe(char *cmd){
	uint8_t i = 0, j = 0;
	
	memset(buffer, 0, 100);
	
	for(i = 7; (cmd[i] >= '0' ) && (cmd[i]) <= '9'; i++ ){
		buffer[j++] = cmd[i];
	}
	
	systemConfig.sensor.sens = atof(buffer);

	putSensorDataToFlash();
	
	serialPrintStr((uint8_t *)"OK\r\n");
	return 0;
}

//DATE=2019-08-16 17:46:00
uint8_t setDateExe(char *cmd){
	uint8_t i = 0, j = 0;
	
	memset(systemConfig.sensor.date, 0, 30);
	
	for(i = 5; cmd[i] != '\0' && cmd[i] != '*'; i++){
		systemConfig.sensor.date[j] = cmd[i];
		j++;
	}
	putSensorDataToFlash();
	serialPrintStr((uint8_t *)"OK\r\n");
	return 0;
}


uint8_t queryExe(char *cmd){
	memset(buffer, 0, 100);

#if 0	
	sprintf(buffer, "Offset=%d;Date=%s;Runtime=%d;Gain=%d;CO=%.1f;E1=%d;E2=%d;E3=%d;E4=%d;\r\n",
				systemConfig.sensor.sens,
				systemConfig.sensor.date,
				systemConfig.sensor.useTimeCnt/3600,
				systemConfig.sensor.gain,
				systemConfig.sensor.co,
				systemConfig.sensor.waringE1Cnt,
				systemConfig.sensor.waringE2Cnt,
				systemConfig.sensor.waringE3Cnt,
				systemConfig.sensor.waringE4Cnt);
#endif

	sprintf(buffer, "ch1Value=%d,ch2Value=%d, CO=%.1f\r\n", systemConfig.sensor.ch1Value, systemConfig.sensor.ch2Value, systemConfig.sensor.co);
	serialPrintStr((uint8_t *)buffer);
	
	return 0;
}

void serialCommandHandle(void){
	uint8_t i = 0;
	
	if(UartRxReady == SET){											//接收到串口数据包
		memset(cmdStrBuf, 0, 200);
		memcpy(cmdStrBuf, aRxBuffer, strlen((char *)aRxBuffer));
		for(i = 0; i < (sizeof(cmdArray)/(sizeof(cmdParser_t))); i++){
			if(memcmp((char *)cmdArray[i].cmdStr, cmdStrBuf, strlen(cmdArray[i].cmdStr) )== 0){
				if(cmdArray[i].executeCMD != NULL){
					cmdArray[i].executeCMD(cmdStrBuf);
					break;
				}
			}
		}	
		
		memset(aRxBuffer, 0, TXBUFFERSIZE);
		UartRxReady = RESET;
	}
}
