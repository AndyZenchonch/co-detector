#include "memory.h"
#include "string.h"

systemConfig_Typedef systemConfig;

uint32_t FirstPage = 0, NbOfPages = 0, Address = 0;
uint32_t PageError = 0;
__IO uint32_t data32 = 0 , MemoryProgramStatus = 0;
static FLASH_EraseInitTypeDef EraseInitStruct;


void flashWriteMoreData(uint8_t *str){
	int32_t j;
	uint32_t RamSource;
	uint32_t FlashDestination;
	
	HAL_FLASH_Unlock();
   /* Get the number of sector to erase from 1st sector*/
  NbOfPages = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR + 1) >> 7;

  /* Fill EraseInit structure*/
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;
  EraseInitStruct.NbPages = NbOfPages;
	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
	
  FlashDestination = FLASH_USER_START_ADDR;
	RamSource = (uint32_t)str;

	for(j = 0; j < FLASH_DATA_LENGTH; j+=4){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FlashDestination, *(uint32_t*)RamSource);
		FlashDestination += 4;
		RamSource += 4;
	}
	
	HAL_FLASH_Lock(); 
}

static uint32_t FLASH_ReadWord(uint32_t address){
	return *(__IO uint32_t*)address;
}

void flashReadMoreData(uint8_t *str){
	int32_t j;
	uint32_t RamSource;	
	uint32_t FlashDestination;
	
	FlashDestination = FLASH_USER_START_ADDR;

	RamSource = (uint32_t)str;
	for(j = 0; j < FLASH_DATA_LENGTH; j+=4){
		*(uint32_t*)RamSource = FLASH_ReadWord(FlashDestination);
		FlashDestination += 4;
		RamSource += 4;			
	}	
}

void putSensorDataToFlash(void){
	uint8_t str[FLASH_DATA_LENGTH] = {'\0'};
	memcpy(str, systemConfig.buffer, FLASH_DATA_LENGTH);
	
	flashWriteMoreData(str);
}

void getSensorDataFromFlash(void){
	uint8_t str[FLASH_DATA_LENGTH] = {'\0'};
	flashReadMoreData(str);
	memcpy(systemConfig.buffer, str, FLASH_DATA_LENGTH);
}

#include "hal_driver.h"

void sensorConfigDataInit(void){
	systemConfig.sensor.bootFlag = 0x55;
	systemConfig.sensor.co = 0.0;
	memset(systemConfig.sensor.date, 0, 30);
	memcpy(systemConfig.sensor.date, "2019-08-16 17:46:00", sizeof("2019-08-16 17:46:00") - 1);
	systemConfig.sensor.gain = 58740;
	systemConfig.sensor.sens = 2180;
	systemConfig.sensor.useTimeCnt = 0;
	systemConfig.sensor.voltageErr = 0;
	systemConfig.sensor.waringE1Cnt = 0;
	systemConfig.sensor.waringE2Cnt = 0;
	systemConfig.sensor.waringE3Cnt = 0;
	systemConfig.sensor.waringE4Cnt = 0;
	systemConfig.sensor.waringE5Cnt = 0;
	systemConfig.sensor.waringE6Cnt = 0;
	systemConfig.sensor.waringE7Cnt = 0;
	systemConfig.sensor.waringE8Cnt = 0;
	systemConfig.sensor.waringE9Cnt = 0;
	systemConfig.sensor.waringE10Cnt = 0;
	//refVoltageCalibration();
	putSensorDataToFlash();
}






