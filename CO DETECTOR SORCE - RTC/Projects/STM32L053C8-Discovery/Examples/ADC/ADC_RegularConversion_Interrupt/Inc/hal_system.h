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
	uint8_t enable;											//ʹ��
	uint8_t times;											//������������
	uint32_t timeoutThreshold;					//��ʱʱ�䣬����ʱ�󣬽�����Ӧ���ж�
	uint32_t timeStemp;									//ʱ���
	float gasValueCnt;									//�ۼ�ֵ
	float gasValue;											//��õ�����
}alarmRegister_Typedef;

typedef struct{
	uint8_t index;											//������������
	float coMax;												//���������е����ֵ
	float coMin;												//���������е���Сֵ
	float coCnt;												//���������еļ�Ȩֵ
}co_Filter_Typedef;

extern co_Filter_Typedef coFilter;

typedef struct{
	uint8_t reset;
	uint32_t engineRunningTimes;											//����������ʱ�䣬���ڼ�ⷢ����������5s��û�м�⵽���������岨��
}engineRun_Typedef;

extern engineRun_Typedef engineErr;

extern RTC_HandleTypeDef RTCHandle;

extern void systemInitConfig(void);

extern void SystemClock_Config(void);

extern void mainRun(void);
#endif

