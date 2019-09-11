#ifndef __HAL_SYSTEM_H
#define __HAL_SYSTEM_H

#include "main.h"

#define __CO_REALTIME_THRESHOLD		800.0
#define __CO_10MIN_THRESHOLD			400.0
#define	__CO_3TIMES_THRESHOLD			250.0

#define __ENGINE_RUN_ERR_TIMEOUT	5000

typedef enum{
	IDLE,
	SYSTEM_FAILURE,
	OVER_STANDARD_WARING
}ALARM_TYPEDEF;

typedef struct{
	uint8_t enable;											//使能
	uint8_t times;											//连续采样次数
	uint32_t timeoutThreshold;					//超时时间，即超时后，进行相应的判断
	uint32_t timeStemp;									//时间戳
	float gasValueCnt;									//累加值
	float gasValue;											//求得的数据
}alarmRegister_Typedef;

typedef struct{
	uint8_t index;											//连续采样次数
	float coMax;												//连续采用中的最大值
	float coMin;												//连续采样中的最小值
	float coCnt;												//连续采用中的加权值
}co_Filter_Typedef;

extern co_Filter_Typedef coFilter;

typedef struct{
	uint8_t reset;
	uint32_t engineRunningTimes;											//发动机运行时间，用于检测发动机启动后，5s内没有检测到发动机脉冲波。
}engineRun_Typedef;

extern engineRun_Typedef engineErr;

extern RTC_HandleTypeDef RTCHandle;

extern void systemInitConfig(void);

extern void SystemClock_Config(void);

extern void mainRun(void);
#endif

