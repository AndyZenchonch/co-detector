#ifndef __MEMORY_H
#define __MEMORY_H

#include "main.h"

#define FLASH_USER_START_ADDR   0x800f000   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     0x8010000   /* End @ of user Flash area */

#define FLASH_DATA_LENGTH				92

typedef struct{
	uint8_t bootFlag;
	
	char date[30];					//出厂日期
	
	float co;
	
	uint32_t useTimeCnt;		//累积使用时间
	
	uint32_t voltageErr;		//参考电压修正
	uint32_t gain;					//放大倍数
	uint32_t sens;					//温度补偿
	
	uint32_t ch1Value;
	uint32_t ch2Value;	
	
	/*报警次数*/
	uint32_t waringE1Cnt;							//连续三次采集，CO浓度超过250PPM
	uint32_t waringE2Cnt;							//CO浓度大于800PPM
	uint32_t waringE3Cnt;							//10min滚动平均CO浓度值达到400PPM
	uint32_t waringE4Cnt;							//发动机启动后，运行中5S内检测到发动机点火脉冲
	uint32_t waringE5Cnt;							//
	uint32_t waringE6Cnt;							//
	uint32_t waringE7Cnt;							//
	uint32_t waringE8Cnt;							//
	uint32_t waringE9Cnt;							//备用
	uint32_t waringE10Cnt;						//备用
}memory_Typedef;

typedef union{
	memory_Typedef sensor;
	uint8_t buffer[FLASH_DATA_LENGTH];
}systemConfig_Typedef;

extern systemConfig_Typedef systemConfig;

extern void putSensorDataToFlash(void);

extern void getSensorDataFromFlash(void);

extern void sensorConfigDataInit(void);

#endif

