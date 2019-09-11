#include "hal_driver.h"
#include "memory.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ADC handle declaration */
ADC_HandleTypeDef             AdcHandle;

/* ADC channel configuration structure declaration */
ADC_ChannelConfTypeDef        sConfig;

UART_HandleTypeDef UartHandle;

__IO uint32_t uwADCxConvertedValue = 0;
__IO ITStatus UartTxReady = RESET;
__IO ITStatus UartRxReady = RESET;
__IO ITStatus adcReady = RESET;


static void Error_Handler(void){
  /* Infinite loop */
  while(1){
  }
}


static uint16_t NUCLEO_ANALOG_PIN[] = {GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,GPIO_PIN_4,GPIO_PIN_5};
static uint32_t NUCLEO_ANALOG_ADC_CHANNEL[] = {ADC_CHANNEL_0,ADC_CHANNEL_1,ADC_CHANNEL_2,ADC_CHANNEL_3,ADC_CHANNEL_TEMPSENSOR,ADC_CHANNEL_VREFINT};
static const float TEMP_COMPENSATION[61]={0.6745, 0.6854, 0.6963, 0.7072, 0.7181, 0.7290, 0.7399, 0.7508, 0.7617, 0.7726, 0.7835, 0.7944, 0.8053, 0.8162, 0.8271, 0.8380, 0.8489, 0.8598, 0.8707, 0.8816, 0.8925, 0.9034, 0.9143, 0.9252, 0.9361, 0.9470, 0.9579, 0.9688, 0.9797, 0.9906, 1.0000, 1.0075, 1.0150, 1.0225, 1.0300, 1.0375, 1.0450, 1.0525, 1.0600, 1.0675, 1.0750, 1.0825, 1.0900, 1.0975, 1.1050, 1.1125, 1.1200, 1.1275, 1.1350, 1.1425, 1.1500, 1.1575, 1.1650, 1.1725, 1.1800, 1.1875, 1.1950, 1.2025, 1.2100, 1.2175, 1.2250};

	
	
/**
   * @brief  Initializes gpio peripheral, and activates ADC clock
   * @param hadc pointer to ADC handle 
   */
static void ADCx_MspInit_Analog(ADC_HandleTypeDef *hadc,uint8_t input)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  
	HAL_GPIO_DeInit(GPIOA,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
  /*** Configure the GPIOs ***/  
  /* Enable GPIO clock */
  __GPIOA_CLK_ENABLE();
  
  /* Configure the selected ADC Channel as analog input */
  GPIO_InitStruct.Pin = NUCLEO_ANALOG_PIN[input];
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /*** Configure the ADC peripheral ***/ 
  /* Enable ADC clock */
  __HAL_RCC_ADC1_CLK_ENABLE(); 
}

/*
*		ADC³õÊ¼»¯
*/
void adcChannelConfig(uint8_t ch){
  if(HAL_ADC_GetState(&AdcHandle) == HAL_ADC_STATE_RESET){	
		AdcHandle.Instance = ADC1;
		AdcHandle.Init.OversamplingMode      = DISABLE;
		AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV1;
		AdcHandle.Init.LowPowerAutoPowerOff  = DISABLE;
		AdcHandle.Init.LowPowerFrequencyMode = ENABLE;
		AdcHandle.Init.LowPowerAutoWait      = DISABLE;
		AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;
		AdcHandle.Init.SamplingTime          = ADC_SAMPLETIME_1CYCLE_5;
		AdcHandle.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;
		AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
		AdcHandle.Init.ContinuousConvMode    = ENABLE;
		AdcHandle.Init.DiscontinuousConvMode = DISABLE;
		AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
		AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
		AdcHandle.Init.DMAContinuousRequests = DISABLE;
	}
	
	ADCx_MspInit_Analog(&AdcHandle, ch);
	
  /* Initialize ADC peripheral according to the passed parameters */
  if (HAL_ADC_Init(&AdcHandle, ch) != HAL_OK){
    Error_Handler();
  }
  
  /* ### - 2 - Start calibration ############################################ */
  if (HAL_ADCEx_Calibration_Start(&AdcHandle, ADC_SINGLE_ENDED) != HAL_OK){
    Error_Handler();
  }

	AdcHandle.Instance->CHSELR = NUCLEO_ANALOG_ADC_CHANNEL[ch];	
}


uint32_t getAdcValue(uint8_t ch){	
	if (HAL_ADC_Start_IT(&AdcHandle) != HAL_OK){
		Error_Handler();
	}		
	while(adcReady == RESET);
	adcReady = RESET;	
	
	return uwADCxConvertedValue;
}

uint32_t getAdcChannelValue(uint8_t ch){
	adcChannelConfig(ch);
	return getAdcValue(ch);
}

float vccVoltageValue = 0.0;
uint32_t channel3Value = 0;

float getGasConcentration(float gain, float sens){
	systemConfig.sensor.ch1Value = getAdcChannelValue(__CO_CHANNEL);
	systemConfig.sensor.ch2Value = getAdcChannelValue(__SEN_CHANNEL); //+ systemConfig.sensor.voltageErr;

	if(systemConfig.sensor.ch1Value < systemConfig.sensor.ch2Value)
		systemConfig.sensor.ch1Value = systemConfig.sensor.ch2Value;
	
	gasVolValue = systemConfig.sensor.ch1Value * 3.3 / 4096;
	vccVoltageValue = systemConfig.sensor.ch2Value * 0.006177;
	
	return ((float)systemConfig.sensor.ch1Value- systemConfig.sensor.ch2Value) * 805664 / gain / sens;
}

#include "math.h"
#include "temperature.h"

const float Rp=10000.0; //10K
const float T2 = (273.15+25.0);//T2
const float Bx = 3950.0;//B
const float Ka = 273.15;
float Get_Temp(float NTC_Res){
	float Rt;
	float temp;
	Rt = NTC_Res;
	
	//like this R=5000, T2=273.15+25,B=3470, RT=5000*EXP(3470*(1/T1-1/(273.15+25)),
	temp = Rt/Rp;
	temp = log(temp);//ln(Rt/Rp)
	temp/=Bx;//ln(Rt/Rp)/B
	temp+=(1/T2);
	temp = 1/(temp);
	temp-=Ka;
	return temp;
}

float getRegisterValue(unsigned int adcValue){
	float Ry, Rx;

	Rx = adcValue;

	Ry = (12 * 4096 / Rx - 12) * 1000.0;

	return Ry;
}

float Get_Temperature(void){
	channel3Value = getAdcChannelValue(__TEM_CHANNEL);
	
	return Get_Temp(getRegisterValue(channel3Value));//(sqrt(2196200 + (1.8639 - 3.0 * channel3Value /4096 ) / 3.88 * 1000000) - 1481.96);
}

float getCompGasConcentration(float gasPpm, int8_t temp){
	if(temp + COMP_SHIFT >= LOOKUP_LENGTH){
		temp = LOOKUP_LENGTH - 1;
	}else if(temp + COMP_SHIFT < 0){
		temp = 0;
	}else{
		temp = temp + COMP_SHIFT;
	}
	
	return gasPpm / TEMP_COMPENSATION[temp];
}

void refVoltageCalibration(void){
	uint32_t index = 0;
	uint32_t channel1Value = 0;
	uint32_t channel2Value = 0;
	
	systemConfig.sensor.voltageErr = 0;
	
	for(;;){
		channel1Value = getAdcChannelValue(1);
		channel2Value = getAdcChannelValue(2);
		if(channel1Value > channel2Value)
			systemConfig.sensor.voltageErr++;
		else
			systemConfig.sensor.voltageErr--;
		for(index = 0; index < 100; index++ ){
			channel1Value = getAdcChannelValue(1);
			channel2Value = getAdcChannelValue(2);			
			if(channel1Value > (channel2Value + systemConfig.sensor.voltageErr))
				break;
			HAL_Delay(20);
		}
		if(index == 100)
			break;
	}
}






