#ifndef __MEMORY_H
#define __MEMORY_H

#include "main.h"

#define FLASH_USER_START_ADDR   0x800f000   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     0x8010000   /* End @ of user Flash area */

#define FLASH_DATA_LENGTH				92

typedef struct{
	uint8_t bootFlag;
	
	char date[30];					//��������
	
	float co;
	
	uint32_t useTimeCnt;		//�ۻ�ʹ��ʱ��
	
	uint32_t voltageErr;		//�ο���ѹ����
	uint32_t gain;					//�Ŵ���
	uint32_t sens;					//�¶Ȳ���
	
	uint32_t ch1Value;
	uint32_t ch2Value;	
	
	/*��������*/
	uint32_t waringE1Cnt;							//�������βɼ���COŨ�ȳ���250PPM
	uint32_t waringE2Cnt;							//COŨ�ȴ���800PPM
	uint32_t waringE3Cnt;							//10min����ƽ��COŨ��ֵ�ﵽ400PPM
	uint32_t waringE4Cnt;							//������������������5S�ڼ�⵽�������������
	uint32_t waringE5Cnt;							//
	uint32_t waringE6Cnt;							//
	uint32_t waringE7Cnt;							//
	uint32_t waringE8Cnt;							//
	uint32_t waringE9Cnt;							//����
	uint32_t waringE10Cnt;						//����
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

