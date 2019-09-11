/**
  ******************************************************************************
  * @file    Examples_LL/TIM/TIM_DMA/Src/main.c
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    25-November-2016
  * @brief   This example describes how to use DMA with TIM2 Update request to
  *          transfer Data from memory to TIM2 Capture Compare Register 3 (CCR3)
  *          using the STM32L0xx TIM LL API.
  *          Peripheral initialization done using LL unitary services functions.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32L0xx_LL_Examples
  * @{
  */

/** @addtogroup TIM_DMA
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CC_VALUE_NB       3

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Capture Compare buffer */
static uint32_t aCCValue[CC_VALUE_NB] = {0};

/* Private function prototypes -----------------------------------------------*/
__STATIC_INLINE void     SystemClock_Config(void);
__STATIC_INLINE void     Configure_DMA(void);
__STATIC_INLINE void     Configure_TIM(void);
__STATIC_INLINE void     LED_Init(void);
__STATIC_INLINE void     LED_Blinking(uint32_t Period);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Configure the system clock to 80 MHz */
  SystemClock_Config();

  /* Initialize LED2 */
  LED_Init();

  /* Configure DMA transfer */  
  Configure_DMA();
  
  /* Configure timer instance */
  Configure_TIM();

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  This function enables the peripheral clock for the DMA,
  *         configures the DMA transfer, configures the NVIC for DMA and
  *         enables the DMA.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void  Configure_DMA(void)
{  
  /******************************************************/
  /* Configure NVIC for DMA transfer related interrupts */
  /******************************************************/
  NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0);
  NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

  /*****************************/
  /* Peripheral clock enabling */
  /*****************************/
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  /******************************/
  /* DMA transfer Configuration */
  /******************************/
  LL_DMA_ConfigTransfer(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_MEMORY_TO_PERIPH |
                                                LL_DMA_PRIORITY_HIGH              |
                                                LL_DMA_MODE_CIRCULAR              |
                                                LL_DMA_PERIPH_NOINCREMENT         |
                                                LL_DMA_MEMORY_INCREMENT           |
                                                LL_DMA_PDATAALIGN_WORD            |
                                                LL_DMA_MDATAALIGN_WORD);
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMA_REQUEST_8);
  LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2, (uint32_t)&aCCValue, (uint32_t)&TIM2->CCR3, LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2));
  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, CC_VALUE_NB);
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
  LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_2);
    
  /***************************/
  /* Enable the DMA transfer */
  /***************************/
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
}


/**
  * @brief  This function configures TIM2 channel 3 to generate a PWM edge
  *         aligned signal with a frequency equal to 17.57 KHz and a variable
  *         duty cycle that is changed by the DMA after each DMA requests. 
  * @note   Peripheral configuration is minimal configuration from reset values.
  *         Thus, some useless LL unitary functions calls below are provided as
  *         commented examples - setting is default configuration from reset.
  * @retval None
  */
__STATIC_INLINE void  Configure_TIM(void)
{  
  /*************************/
  /* GPIO AF configuration */
  /*************************/
  /* Enable the peripheral clock of GPIOs */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

  /* GPIO TIM2_CH3 configuration */
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_10, LL_GPIO_PULL_DOWN);
  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_10, LL_GPIO_AF_2);

  /******************************************************/
  /* Configure the NVIC to handle TIM2 update interrupt */
  /******************************************************/
  NVIC_SetPriority(TIM2_IRQn, 0);
  NVIC_EnableIRQ(TIM2_IRQn);
  
  /******************************/
  /* Peripheral clocks enabling */
  /******************************/
  /* Enable the peripheral clock of TIM2 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
  
  /***************************/
  /* Time base configuration */
  /***************************/
  /* Set counter mode */
  /* Reset value is LL_TIM_COUNTERMODE_UP */
  //LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);
  
  /* Set the TIM2 auto-reload register to get a PWM frequency at 17.57 KHz */
  /* Note that the timer pre-scaler isn't used, therefore the timer counter   */
  /* clock frequency is equal to the timer frequency.                        */
    /* In this example TIM2 input clock (TIM2CLK) frequency is set to APB1 clock*/
  /*  (PCLK1), since APB1 pre-scaler is equal to 1.                                     */
  /*    TIM2CLK = PCLK1                                                       */
  /*    PCLK1 = HCLK                                                          */
  /*    => TIM2CLK = HCLK = SystemCoreClock (2 Mhz)                           */
  LL_TIM_SetAutoReload(TIM2, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_COUNTERMODE_UP, 17570));
  
  
  /*********************************/
  /* Output waveform configuration */
  /*********************************/
  /* Set output channel 3 in PWM1 mode */
  LL_TIM_OC_SetMode(TIM2,  LL_TIM_CHANNEL_CH3,  LL_TIM_OCMODE_PWM1);

  /* TIM2 channel 3 configuration:    */
  LL_TIM_OC_ConfigOutput(TIM2, LL_TIM_CHANNEL_CH3, LL_TIM_OCPOLARITY_HIGH);

  /* Compute compare value to generate a duty cycle at 75% */
  aCCValue[0] = (uint32_t)(((uint32_t) 75 * (LL_TIM_GetAutoReload(TIM2) - 1)) / 100);
  /* Compute compare value to generate a duty cycle at 50% */
  aCCValue[1] = (uint32_t)(((uint32_t) 50 * (LL_TIM_GetAutoReload(TIM2) - 1)) / 100);
  /* Compute compare value to generate a duty cycle at 25% */
  aCCValue[2] = (uint32_t)(((uint32_t) 25 * (LL_TIM_GetAutoReload(TIM2) - 1)) / 100);

  /* Set PWM duty cycle  for TIM2 channel 3*/
  LL_TIM_OC_SetCompareCH3(TIM2, aCCValue[0]);
  
  /* Enable register preload for TIM2 channel 3 */
  LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH3);
  
  /****************************/
  /* TIM2 DMA requests set-up */
  /****************************/
  /* Enable DMA request on update event */
  LL_TIM_EnableDMAReq_UPDATE(TIM2);

  /**************************/
  /* TIM2 interrupts set-up */
  /**************************/
  /* Enable the update interrupt */
  LL_TIM_EnableIT_UPDATE(TIM2);
  
  /**********************************/
  /* Start output signal generation */
  /**********************************/
  /* Enable TIM2 channel 3 */
  LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH3);
  
  
  /* Enable counter */
  LL_TIM_EnableCounter(TIM2);
  
  /* Force update generation */
  LL_TIM_GenerateEvent_UPDATE(TIM2);
}

/**
  * @brief  Initialize LED2.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void LED_Init(void)
{
  /* Enable the LED2 Clock */
  LED2_GPIO_CLK_ENABLE();

  /* Configure IO in output push-pull mode to drive external LED2 */
  LL_GPIO_SetPinMode(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinOutputType(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinSpeed(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinPull(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_PULL_NO);
}

/**
  * @brief  Set LED2 to Blinking mode for an infinite loop (toggle period based on value provided as input parameter).
  * @param  Period : Period of time (in ms) between each toggling of LED
  *   This parameter can be user defined values. Pre-defined values used in that example are :
  *     @arg LED_BLINK_FAST : Fast Blinking
  *     @arg LED_BLINK_SLOW : Slow Blinking
  *     @arg LED_BLINK_ERROR : Error specific Blinking
  * @retval None
  */
__STATIC_INLINE void LED_Blinking(uint32_t Period)
{
  /* Toggle IO in an infinite loop */
  while (1)
  {
    LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);  
    LL_mDelay(Period);
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = MSI
  *            SYSCLK(Hz)                     = 2097000
  *            HCLK(Hz)                       = 2097000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            Flash Latency(WS)              = 0
  *            Main regulator output voltage  = Scale3 mode
  * @retval None
  */
void SystemClock_Config(void)
{
  /* MSI configuration and activation */
  LL_RCC_PLL_Disable();
  /* Set new latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

  LL_RCC_MSI_Enable();
  while(LL_RCC_MSI_IsReady() != 1) 
  {
  };
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_5);  
  LL_RCC_MSI_SetCalibTrimming(0x0);

  /* Sysclk activation  */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_MSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_MSI) 
  {
  };
  
  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 2MHz */
  LL_Init1msTick(2097000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(2097000);  

  /* Enable Power Control clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE3);
  /* Disable Power Control clock */
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_PWR);
}


/******************************************************************************/
/*   USER IRQ HANDLER TREATMENT                                               */
/******************************************************************************/
/**
  * @brief  Timer update interrupt processing
  * @param  None
  * @retval None
  */
void TimerUpdate_Callback(void)
{
  static uint32_t UpdateEventCnt = 0;

  /* At every update event the CCR3 register is updated with a new value */
  /* which is DMA transferred from aCCValue[].                           */
  /* Note that the update event (UEV) is generated after upcounting is   */
  /* repeated for the number of times programmed in the repetition       */
  /* counter register (TIM1_RCR) + 1                                     */
  if (LL_TIM_OC_GetCompareCH3(TIM2) != aCCValue[UpdateEventCnt])
  {
    LED_Blinking(LED_BLINK_ERROR);
  }
  else
  {
    UpdateEventCnt = (UpdateEventCnt+1) % CC_VALUE_NB;
  }
}

/**
  * @brief  DMA transfer complete callback
  * @note   This function is executed when the transfer complete interrupt
  *         is generated after DMA transfer
  * @retval None
  */
void TransferComplete_Callback()
{
  /* Once the DMA transfer is completed the CCR3 value must match */
  /* the value of the last element of aCCValue[].                 */
  if (LL_TIM_OC_GetCompareCH3(TIM2) != aCCValue[CC_VALUE_NB-1])
  {
    LED_Blinking(LED_BLINK_ERROR);
  }
}

/**
  * @brief  DMA transfer error callback
  * @note   This function is executed when the transfer error interrupt
  *         is generated during DMA transfer
  * @retval None
  */
void TransferError_Callback()
{
  LED_Blinking(LED_BLINK_ERROR);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
