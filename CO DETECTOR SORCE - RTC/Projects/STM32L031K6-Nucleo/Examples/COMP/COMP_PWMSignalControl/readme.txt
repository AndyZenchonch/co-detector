/**
  @page COMP_PWMSignalControl COMP PWM Signal control example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    COMP/COMP_PWMSignalControl/readme.txt
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    25-November-2016
  * @brief   Description of the COMP PWM Signal Control example.
  ******************************************************************************
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
  @endverbatim

@par Example Description 

This example shows how to configure COMP peripheral to automatically hold
TIMER PWM output on safe state (low level) as soon as comparator output is set
at high level.

  - COMP2 is configured as follows:
     - Inverting input is internally connected to VREFINT = 1.22V
     - Non Inverting input is connected to pin PB.05 (Arduino D11)
     - Output is internally connected to TIM22 TIM_CHANNEL_2 OCRef clear input.

  - TIM22 counter is used for PWM signal generation.
     - Timer frequency is set to 1kHz, PWM duty cycle 25%. Frequency can be tuned using defined label "TIMER_FREQUENCY_HZ" (unit: Hz).
     - TIM22 channel TIM_CHANNEL_2 is configured in PWM output mode, connected to pin PA.7 (Arduino A6).

  - While PB.05 (Arduino D11) is lower than VREFINT, PWM signal is displayed on PA.7 (Arduino A6).
  - While PB.05 (Arduino D11) is higher than VREFINT, PA.7 (Arduino A6) is in low level.


Board settings:
  - STM32L031K6-Nucleo Set-up
      @note This example runs in stand alone mode.
    - Set voltage level on pin PB.05 (Arduino D11) (comparator input): above or below Vrefint (1.22V).
      Note: to avoid the need of a power supply, possibility to connect a wire between this pin to a pin of the board: 
	  Vdda pin (3.3V) or ground pin (0V).
    - Watch waveform on pin PA.7 (Arduino A6) (timer PWM output) with an oscilloscope, 
	  or watch average value with a multimeter (Vdda=3.3v and duty cycle 25% should give an average voltage of 0.825V)

    
STM32L031K6-Nucleo board's LED is used to monitor the program execution status:
 - Error: In case of error, LED3 is toggling at a frequency of 2Hz.
 

@note To have a precise value of the pulse, HSI as a source of clock system should be 
calibrated or use an external clock.


@note Care must be taken when using HAL_Delay(), this function provides 
      accurate delay (in milliseconds) based on variable incremented in SysTick ISR. 
      This implies that if HAL_Delay() is called from a peripheral ISR process, then 
      the SysTick interrupt must have higher priority (numerically lower) than the 
      peripheral interrupt. Otherwise the caller ISR process will be blocked. 
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set 
      to 1 millisecond to have correct HAL operation.

@par Directory contents 

  - COMP/COMP_PWMSignalControl/Inc/stm32l0xx_hal_conf.h    HAL configuration file
  - COMP/COMP_PWMSignalControl/Inc/stm32l0xx_it.h          COMP interrupt handlers header file
  - COMP/COMP_PWMSignalControl/Inc/main.h                  Header for main.c module
  - COMP/COMP_PWMSignalControl/Src/stm32l0xx_it.c          COMP interrupt handlers
  - COMP/COMP_PWMSignalControl/Src/main.c                  Main program
  - COMP/COMP_PWMSignalControl/Src/stm32l0xx_hal_msp.c     HAL MSP file 
  - COMP/COMP_PWMSignalControl/Src/system_stm32l0xx.c      STM32L0xx system source file


@par Hardware and Software environment 

  - This example runs on STM32L031xx devices.
  - In this example, the clock is set to 2 MHz.

  - This example has been tested with STM32L031K6-Nucleo board and can be
    easily tailored to any other supported device and development board.
    
  
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */