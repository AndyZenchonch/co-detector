#include "hal_led.h"

/*
*	PB3--->RED
*	PB4--->GREEN
* 高电平驱动
*/
void ledConfig(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_RESET); 
	
}

void opPowerConfig(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
}

void halLEDOnOff(uint8_t led, uint8_t en){
	if(led == LED_RED){
		if(en == 1)
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET); 
		else
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET); 
	}else{
		if(en == 1)
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); 
		else
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); 
	}
}

