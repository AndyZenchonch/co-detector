/**
  ******************************************************************************
  * @file    menu_res.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    25-November-2016
  * @brief   Main program body
  *          This example code shows how to use the Nucleo BSP Drivers
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
#include <stdint.h>

/** @addtogroup CORE
  * @{
  */

/** @defgroup MENU
  * @brief MENU ressources
  * @{
  */


//#define x_width 72
//#define x_height 172
static uint8_t Background_pic[] = {
0x00, 0x00, 0x00, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xe0, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 
0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 
0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 
0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 
0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
0x00, 0xe8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 
0x00, 0x74, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 
0x00, 0x76, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 
0x00, 0x77, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 
0x80, 0x77, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 
0xc0, 0x77, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 
0xc0, 0x8f, 0xfb, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 
0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 
0xe0, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 
0xf0, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
0xf0, 0xff, 0xf7, 0xff, 0xff, 0x7f, 0xe0, 0xff, 0x00, 
0xf8, 0x07, 0xf0, 0xff, 0xff, 0x3f, 0xc0, 0xff, 0x01, 
0xf8, 0xff, 0xf7, 0xff, 0xff, 0x1f, 0x80, 0xff, 0x01, 
0xfc, 0xff, 0xf7, 0xff, 0xff, 0x0f, 0x80, 0xff, 0x03, 
0xfc, 0xff, 0xf7, 0xff, 0xff, 0x07, 0x80, 0xff, 0x03, 
0xfc, 0xff, 0xff, 0xff, 0xff, 0x03, 0x80, 0xff, 0x03, 
0xfe, 0x07, 0xf0, 0xff, 0xff, 0x01, 0x80, 0xff, 0x07, 
0xfe, 0xff, 0xfd, 0xff, 0xff, 0x00, 0xc0, 0xff, 0x07, 
0xfe, 0x7f, 0xfe, 0x0f, 0xfe, 0x00, 0xc0, 0xff, 0x07, 
0xfe, 0xbf, 0xff, 0x07, 0x70, 0x00, 0xc0, 0xff, 0x07, 
0xff, 0xcf, 0xff, 0x03, 0x00, 0x00, 0xc0, 0xff, 0x07, 
0xff, 0xbf, 0xff, 0x03, 0x00, 0x00, 0xe0, 0xff, 0x0f, 
0xff, 0x7f, 0xfe, 0x01, 0x00, 0x00, 0xe0, 0xff, 0x0f, 
0xff, 0xff, 0xfd, 0x01, 0x00, 0x00, 0xf0, 0xff, 0x0f, 
0xff, 0x07, 0xf0, 0x01, 0x00, 0x00, 0xf0, 0xff, 0x0f, 
0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0xf0, 0xff, 0x0f, 
0xff, 0xef, 0xfb, 0x01, 0x00, 0x00, 0xf8, 0xff, 0x0f, 
0xff, 0xf7, 0xf7, 0x01, 0x00, 0x00, 0xf8, 0xff, 0x0f, 
0xff, 0x77, 0xf7, 0x01, 0x00, 0x00, 0xfc, 0xff, 0x0f, 
0xff, 0x77, 0xf7, 0x03, 0x00, 0x00, 0xfc, 0xff, 0x0f, 
0xff, 0x8f, 0xf8, 0x03, 0x00, 0x00, 0xfe, 0xff, 0x07, 
0xfe, 0xff, 0xff, 0x07, 0x00, 0x00, 0xf0, 0xff, 0x07, 
0xfe, 0xe7, 0xfb, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0x07, 
0xfe, 0xd7, 0xf7, 0x3f, 0x00, 0x00, 0xfc, 0xff, 0x07, 
0xfe, 0xb7, 0xf7, 0xff, 0x01, 0x00, 0xfc, 0xff, 0x07, 
0xfc, 0x77, 0xf7, 0xff, 0x07, 0x00, 0xf0, 0xff, 0x03, 
0xfc, 0xf7, 0xf8, 0xff, 0x00, 0x00, 0xc0, 0xff, 0x03, 
0xfc, 0xff, 0xff, 0x3f, 0x08, 0x00, 0x80, 0xff, 0x03, 
0xf8, 0x07, 0xf0, 0xff, 0x07, 0x00, 0x00, 0xfe, 0x01, 
0xf8, 0xf7, 0xff, 0xff, 0x03, 0x00, 0x00, 0xfc, 0x01, 
0xf8, 0xf7, 0xff, 0xff, 0x01, 0x00, 0x00, 0xf8, 0x00, 
0xf0, 0xf7, 0xff, 0xff, 0x00, 0x00, 0x00, 0xf0, 0x00, 
0xe0, 0xf7, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x60, 0x00, 
0xe0, 0xf7, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x40, 0x00, 
0xc0, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xc0, 0x0f, 0xf8, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x80, 0xf7, 0xf7, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xf7, 0xf7, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xf6, 0xf7, 0x3f, 0x00, 0x60, 0x00, 0x00, 0x00, 
0x00, 0x0e, 0xf8, 0x7f, 0x00, 0xe0, 0x00, 0x00, 0x00, 
0x00, 0xf8, 0xff, 0x7f, 0x00, 0xf0, 0x03, 0x00, 0x00, 
0x00, 0xf0, 0xff, 0xff, 0x00, 0xf0, 0x0f, 0x00, 0x00, 
0x00, 0xe0, 0xff, 0xff, 0x01, 0xf8, 0x7f, 0x00, 0x00, 
0x00, 0xc0, 0xff, 0xff, 0x07, 0xfe, 0x3f, 0x00, 0x00, 
0x00, 0x80, 0xff, 0xff, 0x0f, 0xff, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 
0x00, 0x00, 0xe0, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
}; 


//#define x_width 48
//#define x_height 48
static uint8_t Mouse_pic[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xe0, 0x7f, 0x00, 0x00, 0x00, 
0x00, 0xf0, 0xff, 0x00, 0x00, 0x00, 
0x00, 0xfc, 0xff, 0x03, 0x00, 0x00, 
0x00, 0xfe, 0xff, 0x07, 0x00, 0x00, 
0x00, 0xff, 0xff, 0x0f, 0x00, 0x00, 
0x00, 0xff, 0xff, 0x1f, 0x00, 0x00, 
0x80, 0xff, 0xff, 0x0f, 0x00, 0x00, 
0x80, 0xff, 0xff, 0x07, 0x00, 0x00, 
0x80, 0xff, 0xff, 0xc3, 0x00, 0x00, 
0xc0, 0xff, 0xff, 0xe1, 0x01, 0x00, 
0xc0, 0xff, 0xff, 0xf0, 0x03, 0x00, 
0xc0, 0xff, 0x7f, 0xf8, 0x03, 0x00, 
0xc0, 0xff, 0x3f, 0xfc, 0x07, 0x00, 
0xc0, 0xff, 0x1f, 0xfe, 0x07, 0x00, 
0x80, 0xff, 0x0f, 0xff, 0x0f, 0x00, 
0x80, 0xff, 0x07, 0xff, 0x0f, 0x00, 
0x80, 0xff, 0x03, 0xfe, 0x0f, 0x00, 
0x00, 0xff, 0x21, 0xe0, 0x0f, 0x00, 
0x00, 0xfe, 0x70, 0xc0, 0x0f, 0x00, 
0x00, 0x7e, 0x78, 0x8c, 0x0f, 0x00, 
0x00, 0x3c, 0x7c, 0x1e, 0x0f, 0x00, 
0x00, 0x18, 0xfe, 0x3c, 0x0f, 0x00, 
0x00, 0x00, 0xff, 0x38, 0x07, 0x00, 
0x00, 0x80, 0xff, 0x01, 0x07, 0x00, 
0x00, 0xc0, 0xff, 0x03, 0x02, 0x00, 
0x00, 0x80, 0xff, 0x3f, 0x00, 0x00, 
0x00, 0x00, 0xff, 0x7f, 0x00, 0x00, 
0x00, 0x00, 0xfc, 0x7f, 0x0c, 0x00, 
0x00, 0x00, 0xf8, 0x3f, 0x1c, 0x00, 
0x00, 0x00, 0xc0, 0x07, 0x3c, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 
0x00, 0x00, 0x3e, 0x00, 0xc0, 0x01, 
0x00, 0x00, 0xff, 0x00, 0xc0, 0x01, 
0x00, 0x80, 0xf7, 0x01, 0x80, 0x03, 
0x00, 0x80, 0xc3, 0x03, 0x80, 0x03, 
0x00, 0xc0, 0x81, 0x0f, 0x80, 0x03, 
0x00, 0x80, 0x01, 0x1e, 0x80, 0x03, 
0x00, 0x80, 0x03, 0x3c, 0xc0, 0x01, 
0x00, 0x80, 0x03, 0x78, 0xc0, 0x01, 
0x00, 0x00, 0x07, 0xf0, 0xf3, 0x00, 
0x00, 0x00, 0x0f, 0xe0, 0x7f, 0x00, 
0x00, 0x00, 0x1e, 0x80, 0x3f, 0x00, 
0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 
};

//#define x_width 48
//#define x_height 26
static uint8_t Batery_pic[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x0c, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x08, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x08, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x08, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x08, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x18, 
0xfe, 0xff, 0xff, 0x3f, 0x10, 0x38, 
0xfe, 0xff, 0xff, 0x3f, 0x10, 0x38, 
0xfe, 0xff, 0xff, 0x3f, 0x10, 0x38, 
0xfe, 0xff, 0xff, 0x3f, 0xff, 0x39, 
0xfe, 0xff, 0xff, 0x3f, 0x10, 0x38, 
0xfe, 0xff, 0xff, 0x3f, 0x10, 0x38, 
0xfe, 0xff, 0xff, 0x3f, 0x10, 0x38, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x38, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x18, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x08, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x08, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x08, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x0c, 
0xfe, 0xff, 0xff, 0x3f, 0x00, 0x0c, 
0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

//#define x_width 16
//#define x_height 60
static uint8_t Slider_pic[] = {
0xff, 0xff, 
0x03, 0x80, 
0x03, 0x80, 
0x03, 0x80, 
0x07, 0x80, 
0x07, 0x80, 
0x07, 0x80, 
0x07, 0x80, 
0x07, 0x80, 
0x0f, 0x80, 
0x0f, 0x80, 
0x0f, 0x80, 
0xff, 0xff, 
0x1f, 0x80, 
0x1f, 0x80, 
0x1f, 0x80, 
0x3f, 0x80, 
0x3f, 0x80, 
0x3f, 0x80, 
0x3f, 0x80, 
0x3f, 0x80, 
0x7f, 0x80, 
0x7f, 0x80, 
0x7f, 0x80, 
0x7f, 0x80, 
0xff, 0x80, 
0xff, 0x80, 
0xff, 0xff, 
0xff, 0x80, 
0xff, 0x80, 
0xff, 0x81, 
0xff, 0x81, 
0xff, 0x81, 
0xff, 0x81, 
0xff, 0x83, 
0xff, 0x83, 
0xff, 0x83, 
0xff, 0x83, 
0xff, 0x83, 
0xff, 0x87, 
0xff, 0x87, 
0xff, 0x87, 
0xff, 0xff, 
0xff, 0x8f, 
0xff, 0x8f, 
0xff, 0x8f, 
0xff, 0x9f, 
0xff, 0x9f, 
0xff, 0x9f, 
0xff, 0x9f, 
0xff, 0x9f, 
0xff, 0xbf, 
0xff, 0xbf, 
0xff, 0xbf, 
0xff, 0xbf, 
0xff, 0xff, 
0xff, 0xff, 
0xff, 0xff, 
0xff, 0xff, 
0xff, 0xff, 
};

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
