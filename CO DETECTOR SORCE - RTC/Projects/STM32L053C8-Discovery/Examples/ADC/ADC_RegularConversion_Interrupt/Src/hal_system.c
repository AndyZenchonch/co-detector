#include "hal_system.h"
#include "memory.h"
#include "hal_led.h"
#include "buzzer.h"
#include "string.h"
#include "hal_driver.h"
#include "ignitionDriver.h"
#include "serial.h"
#include "peripheral.h"
#include "memory.h"

uint8_t serialConfigFlag = 0;

__IO uint32_t ignitionPulseCnt = 0;
__IO uint32_t systemRunTimeStamp = 0;											//系统运行时间戳，单位：ms

ALARM_TYPEDEF alType = IDLE;

RTC_HandleTypeDef RTCHandle;

static uint8_t systemRestartFlag = 0;											//系统重启标志位，即重新进行开机

alarmRegister_Typedef threeConsecutiverTimes = {
	.enable = 1
};

alarmRegister_Typedef tenMinutesStart = {
	.enable = 1
};

engineRun_Typedef engineErr = {
	.reset = 0
};

co_Filter_Typedef coFilter;

static void Error_Handler(void){
  /* Infinite loop */
  while(1){
  }
}

/**
  * @brief  Configures system clock after wake-up from STOP: enable HSI, PLL
  *         and select PLL as system clock source.
  * @param  None
  * @retval None
  */
static void SystemClockConfig_STOP(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Get the Oscillators configuration according to the internal RCC registers */
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

  /* After wake-up from STOP reconfigure the system clock: Enable HSI and PLL */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV2;
  RCC_OscInitStruct.HSICalibrationValue = 0x10;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

static void SystemPower_Config(void){
  GPIO_InitTypeDef GPIO_InitStructure;
	
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); 	

  /* Enable Ultra low power mode */
  HAL_PWREx_EnableUltraLowPower();
  
  /* Enable the fast wake up from Ultra low power mode */
  HAL_PWREx_EnableFastWakeUp();

  /* Select HSI as system clock source after Wake Up from Stop mode */
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);
  
  /* Enable GPIOs clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /* Configure all GPIO port pins in Analog Input mode (floating input trigger OFF) */
  GPIO_InitStructure.Pin = GPIO_PIN_All;
  GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure); 
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
  HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
  HAL_GPIO_Init(GPIOH, &GPIO_InitStructure);

  /* Disable GPIOs clock */
  __HAL_RCC_GPIOA_CLK_DISABLE();
  __HAL_RCC_GPIOB_CLK_DISABLE();
  __HAL_RCC_GPIOC_CLK_DISABLE();
  __HAL_RCC_GPIOD_CLK_DISABLE();
  __HAL_RCC_GPIOH_CLK_DISABLE();

  /* Configure RTC */
  RTCHandle.Instance = RTC;
  /* Set the RTC time base to 1s */
  /* Configure RTC prescaler and RTC data registers as follow:
  - Hour Format = Format 24
  - Asynch Prediv = Value according to source clock
  - Synch Prediv = Value according to source clock
  - OutPut = Output Disable
  - OutPutPolarity = High Polarity
  - OutPutType = Open Drain */
  RTCHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  RTCHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
  RTCHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
  RTCHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  RTCHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RTCHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if(HAL_RTC_Init(&RTCHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }	
}

/**
  * @brief  System Power Configuration
  *         The system Power is configured as follow : 
  *            + Regulator in LP mode
  *            + VREFINT OFF, with fast wakeup enabled
  *            + HSI as SysClk after Wake Up
  *            + No IWDG
  *            + Wakeup using EXTI Line (Key Button PC.13)
  * @param  None
  * @retval None
  */
static void SystemStopPower_Config(void){
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable Ultra low power mode */
  HAL_PWREx_EnableUltraLowPower();
  
  /* Enable the fast wake up from Ultra low power mode */
  HAL_PWREx_EnableFastWakeUp();

  /* Select HSI as system clock source after Wake Up from Stop mode */
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);
  
  /* Enable GPIOs clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /* Configure all GPIO port pins in Analog Input mode (floating input trigger OFF) */
  GPIO_InitStructure.Pin = GPIO_PIN_All;
  GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure); 
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
  HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
  HAL_GPIO_Init(GPIOH, &GPIO_InitStructure);

  /* Disable GPIOs clock */
  __HAL_RCC_GPIOA_CLK_DISABLE();
  __HAL_RCC_GPIOB_CLK_DISABLE();
  __HAL_RCC_GPIOC_CLK_DISABLE();
  __HAL_RCC_GPIOD_CLK_DISABLE();
  __HAL_RCC_GPIOH_CLK_DISABLE();
}



void SystemClock_Config(void)
{
	#if 0
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable MSI Oscillator */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.MSICalibrationValue=0x00;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){
    Error_Handler();/* Initialization Error */
  }
    
  /* Select MSI as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
	#else
	  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSI Oscillator and activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV2;
  RCC_OscInitStruct.HSICalibrationValue = 0x10;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
	#endif
}

/*
*	系统配置
*/
void systemInitConfig(void){
	opPowerConfig();
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET){
		if(serialConfigFlag == 0){
			uartInit();
			serialConfig(SERIAL_RX);
		}
		serialConfigFlag = 1;
	}
	ledConfig();
  buzzerConfig();
	ignitionConfig();
	ignitionWakeupPinConfig(__MODE_EXIT);
}

void gotoRtcStandbyMode(void){
	SystemPower_Config();
  
	/* Check and handle if the system was resumed from StandBy mode */ 
  if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET){
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB); 						  /* Clear Standby flag */
  }	
	 
  HAL_RTCEx_DeactivateWakeUpTimer(&RTCHandle); 			/* Disable Wakeup Counter */
	HAL_RTCEx_SetWakeUpTimer_IT(&RTCHandle, 0x0987, RTC_WAKEUPCLOCK_RTCCLK_DIV16);		//1s钟醒一次0x0987

	/* Enter Stop Mode */
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

	/* Configures system clock after wake-up from STOP: enable HSI, PLL and select
	PLL as system clock source (HSI and PLL are disabled automatically in STOP mode) */
	SystemClockConfig_STOP();
}

void gotoStopMode(void){
	SystemStopPower_Config();
	
	ignitionWakeupPinConfig(__MODE_EXIT);
	
	/* Enter Stop Mode */
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

	/* Configures system clock after wake-up from STOP: enable HSE, PLL and select
	PLL as system clock source (HSE and PLL are disabled in STOP mode) */
	SystemClockConfig_STOP();
}

uint8_t waringExe(ALARM_TYPEDEF wr){
	uint16_t i = 0;
	
	if(wr == IDLE)
		return 0;
	
	alType = IDLE;
	
	/*一旦报警，就做一次数据存储*/
	//do flash memory
	putSensorDataToFlash();
	
shutDown:
	/*10s熄火过程*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); 
	for(i = 0; i < 5; i++){
		if(wr == OVER_STANDARD_WARING){
			halLEDOnOff(LED_GREEN, LED_ON);
			HAL_Delay(1000);
			halLEDOnOff(LED_GREEN, LED_OFF);
			HAL_Delay(1000);
		}else{
			halLEDOnOff(LED_RED, LED_ON);
			HAL_Delay(1000);
			halLEDOnOff(LED_RED, LED_OFF);
			HAL_Delay(1000);			
		}
	}
	ignitionPulseCnt = 0; 
	HAL_Delay(2000);
	
	/*检测点火脉冲是否真正熄火*/
	if(ignitionPulseCnt != 0){							
		goto shutDown;
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); 
	
	/*熄火后，继续报警5min，如果中途有点火脉冲，则进入正常工作模式*/
	for(i = 0; i < 150; i++){
		ignitionPulseCnt = 0;
		if(wr == OVER_STANDARD_WARING){
			halLEDOnOff(LED_GREEN, LED_ON);
			halBuzzerOnOff(__BUZZER_ON);
			HAL_Delay(1000);
			halLEDOnOff(LED_GREEN, LED_OFF);
			halBuzzerOnOff(__BUZZER_OFF);
			HAL_Delay(1000);
		}else{
			halLEDOnOff(LED_RED, LED_ON);
			HAL_Delay(1000);
			halLEDOnOff(LED_RED, LED_OFF);
			HAL_Delay(1000);			
		}	
		if(ignitionPulseCnt != 0){
			systemRestartFlag = 1;
			ignitionPulseCnt = 0;
			tenMinutesStart.enable = 1;				//重新启动了
			engineErr.reset = 0;
			engineErr.engineRunningTimes = 0;	
			halBuzzerOnOff(__BUZZER_OFF);
			return 1;
		}
	}
	
	halBuzzerOnOff(__BUZZER_OFF);
	
	systemRestartFlag = 0;
	ignitionPulseCnt = 0;
	tenMinutesStart.enable = 0;						//重新启动了
	engineErr.reset = 0;
	engineErr.engineRunningTimes = 0;				
	
	return 0;
}

float gas_value_ppm = 0; 								//传感器实时测试的CO浓度

#include <math.h>   
void __coDebug(void){
	float temperature = 0;
	systemRunTimeStamp = HAL_GetTick();											//获取当前系统时间
	
	while(1){
		if((HAL_GetTick() - systemRunTimeStamp) > 999){				//每1000ms进行一次数据采样
			gas_value_ppm = getGasConcentration(systemConfig.sensor.gain, (float)systemConfig.sensor.sens / 1000);
			temperature = Get_Temperature(); 
			systemConfig.sensor.co = getCompGasConcentration(gas_value_ppm, (int8_t)round(temperature));
			systemRunTimeStamp = HAL_GetTick();
		}	
	}
}

/*
 * 计算CO实时浓度采集
*/
static float __coConcentCalculate(void){
	//systemConfig.sensor.gain = 58740;
	//systemConfig.sensor.sens = 2180;	
	//float temperature = 0;
	gas_value_ppm = getGasConcentration(systemConfig.sensor.gain, (float)systemConfig.sensor.sens / 1000);
	//temperature = Get_Temperature(); 

	return getCompGasConcentration(gas_value_ppm, (int8_t)round(25));
}

void __coConcentFilter(void){
	float concent = 0.0;

	coFilter.coMax = coFilter.coMin = 0.0;
	for(coFilter.index = 0; coFilter.index < 10; coFilter.index++){
		concent = __coConcentCalculate();
		if(coFilter.coMax < concent)
			coFilter.coMax = concent;
		if(coFilter.coMin > concent)
			coFilter.coMin = concent;
		coFilter.coCnt += concent;		
	}
	coFilter.coCnt = coFilter.coCnt - coFilter.coMax - coFilter.coMin;
	coFilter.coMax = coFilter.coMin = 0.0;
	systemConfig.sensor.co = coFilter.coCnt / 8;
	coFilter.coCnt = 0.0;
	coFilter.index = 0;	
}

/*
* 如果检测到系统启动，则进入该函数，知道机器关机
*/
static char buffer[100] = {'\0'};
void mainRun(void){
//	uint32_t systemRunTimeSeconds = 0;
	systemRestartFlag = 0;

	//__coDebug();

	systemRestartFlag = 1;
	systemRunTimeStamp = 0;//HAL_GetTick();											//获取当前系统时间
	
	systemConfig.sensor.co = 0.0;
	threeConsecutiverTimes.enable = 1;
	tenMinutesStart.enable = 1;
	
	for(;;){
		__coConcentFilter();
		memset(buffer, 0, 100);
		sprintf(buffer, "%d,%d,%.1f\r\n", systemConfig.sensor.ch1Value, systemConfig.sensor.ch2Value, systemConfig.sensor.co);
		serialPrintStr((uint8_t *)buffer);		
		HAL_Delay(1000);
	}
	
	for(;;){				
		if(systemRestartFlag == 1){
			systemInitConfig();
			__coConcentFilter();
							
			/*连续三次采样，CO浓度高于250PPM*/
			if(threeConsecutiverTimes.enable == 1){
				if(systemConfig.sensor.co > __CO_3TIMES_THRESHOLD){
					if((systemRunTimeStamp - threeConsecutiverTimes.timeStemp) < 2){											//判断是否连续的
						threeConsecutiverTimes.times++;
					}else{
						threeConsecutiverTimes.times = 0;
					}
					if(threeConsecutiverTimes.times == 0){
						threeConsecutiverTimes.timeStemp = systemRunTimeStamp;
					}
				}
				if(threeConsecutiverTimes.times > 2){
					threeConsecutiverTimes.times = 0;
					systemConfig.sensor.waringE1Cnt++;
					alType = OVER_STANDARD_WARING;
				}
			}	
	
			/*单次CO浓度超过800PPM*/
			if(systemConfig.sensor.co > __CO_REALTIME_THRESHOLD){
				systemConfig.sensor.waringE2Cnt++;
				alType = OVER_STANDARD_WARING;				
			}
				
			/*重启后，前10min滚动平均值*/
			if(tenMinutesStart.enable == 1){
				tenMinutesStart.gasValueCnt += systemConfig.sensor.co;
				tenMinutesStart.times++;
				if(tenMinutesStart.times > 14){
					tenMinutesStart.gasValue = tenMinutesStart.gasValueCnt / 15;
					if(tenMinutesStart.gasValue > __CO_10MIN_THRESHOLD){
						systemConfig.sensor.waringE3Cnt++;
						alType = OVER_STANDARD_WARING;							
					}else{
						tenMinutesStart.times = 0;
					}
					tenMinutesStart.gasValueCnt = 0.0;
				}
				
				tenMinutesStart.timeStemp++;
				
				if(tenMinutesStart.timeStemp > 600){																									//十分钟
					tenMinutesStart.enable = 0;
				}
			}

			ignitionPulseCnt = 0;
		
			waringExe(alType);											//进入报警	
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET){
				HAL_Delay(1000);
			}else{
				serialConfigFlag = 0;
				//gotoRtcStandbyMode();										//进入睡眠模式
			}
			systemRunTimeStamp++;	
			systemConfig.sensor.useTimeCnt++;
		}
		/*需要判断是否有开机中断信号*/
		else{
			serialConfigFlag = 0;
			//gotoStopMode();
			if(ignitionPulseCnt > 0){
				systemRestartFlag = 1;
				tenMinutesStart.enable = 1;
			}			
		}	
	}
}




