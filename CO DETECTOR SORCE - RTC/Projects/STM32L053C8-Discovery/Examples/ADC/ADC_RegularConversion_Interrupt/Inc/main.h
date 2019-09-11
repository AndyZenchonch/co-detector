/**
  ******************************************************************************
  * @file    ADC/ADC_DMA_Transfer/Inc/main.h 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    25-November-2016
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "hal_system.h"



#define TIMx                         TIM6
#define TIMx_CLK_ENABLE              __HAL_RCC_TIM6_CLK_ENABLE

/* Definition for TIMx's NVIC */
#define TIMx_IRQn                    TIM6_DAC_IRQn
#define TIMx_IRQHandler              TIM6_DAC_IRQHandler

#define RTC_CLOCK_SOURCE_LSI   /* LSI used as RTC source clock. The RTC Clock
                                      may varies due to LSI frequency dispersion. */

#ifdef RTC_CLOCK_SOURCE_LSI
  #define RTC_ASYNCH_PREDIV    0x7C
  #define RTC_SYNCH_PREDIV     0x0127
#endif

#ifdef RTC_CLOCK_SOURCE_LSE
  #define RTC_ASYNCH_PREDIV  0x7F
  #define RTC_SYNCH_PREDIV   0x00FF
#endif

#define USARTx                           USART1
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE() 

#define USARTx_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_9
#define USARTx_TX_GPIO_PORT              GPIOA  
#define USARTx_TX_AF                     GPIO_AF4_USART1
#define USARTx_RX_PIN                    GPIO_PIN_10
#define USARTx_RX_GPIO_PORT              GPIOA 
#define USARTx_RX_AF                     GPIO_AF4_USART1

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART1_IRQn
#define USARTx_IRQHandler                USART1_IRQHandler

/* Size of Trasmission buffer */
#define TXBUFFERSIZE                      100
/* Size of Reception buffer */
#define RXBUFFERSIZE                      30

#define HAL_ON		1
#define HAL_OFF		0
  
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern ADC_HandleTypeDef             AdcHandle;
extern ADC_ChannelConfTypeDef        sConfig;
extern UART_HandleTypeDef UartHandle;
extern float gasVolValue;

extern TIM_HandleTypeDef    TimHandle;

extern RTC_HandleTypeDef RTCHandle;

extern __IO uint32_t uwADCxConvertedValue;
extern __IO ITStatus UartTxReady;
extern __IO ITStatus UartRxReady;
extern __IO ITStatus adcReady;

extern __IO uint32_t ignitionPulseCnt;


void HAL_SystemDelay(uint32_t cnt);

#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()

#define USARTx_TX_DMA_CHANNEL             DMA1_Channel2
#define USARTx_TX_DMA_REQUEST             DMA_REQUEST_3
#define USARTx_RX_DMA_CHANNEL             DMA1_Channel3
#define USARTx_RX_DMA_REQUEST             DMA_REQUEST_3

#define USARTx_DMA_TX_IRQn                DMA1_Channel2_3_IRQn
#define USARTx_DMA_RX_IRQn                DMA1_Channel2_3_IRQn
#define USARTx_DMA_TX_IRQHandler          DMA1_Channel2_3_IRQHandler
#define USARTx_DMA_RX_IRQHandler          DMA1_Channel2_3_IRQHandler

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
