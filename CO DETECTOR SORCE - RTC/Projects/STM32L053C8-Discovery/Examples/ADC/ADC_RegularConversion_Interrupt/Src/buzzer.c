#include "buzzer.h"

TIM_HandleTypeDef    TimHandle;


void timer6Init(void){
	TimHandle.Instance = TIM6;
	TimHandle.Init.Period = 1100 - 1;
	TimHandle.Init.Prescaler = (uint32_t)((SystemCoreClock / 1000000) - 1);
	TimHandle.Init.ClockDivision = 0;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_TIM_Base_Init(&TimHandle);
	HAL_TIM_Base_Start_IT(&TimHandle);
}

/*
*	PB7--->蜂鸣器
* 高电平驱动
*/
void buzzerConfig(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); 
	
	//timer6Init();
	
	halBuzzerOnOff(__BUZZER_OFF);
}

void halBuzzerOnOff(uint8_t en){
	if(en == 1)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	//__HAL_RCC_TIM6_CLK_ENABLE();
	else{
		//__HAL_RCC_TIM6_CLK_DISABLE();
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	}
}



