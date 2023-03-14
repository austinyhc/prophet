/**
 ******************************************************************************
 * @file    STWIN_conf.h
 * @author  System Research & Applications Team - Catania Lab.
 * @version V2.0.0
 * @date    05-Jul-2019
 * @brief   This file contains definitions for the MEMS components bus interfaces
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
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
#ifndef __STWIN_CONF_H__
#define __STWIN_CONF_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "STWIN_bus.h"
#include "STWIN_errno.h"
#include "stm32l4xx_hal.h"

/* Analog and digital mics */

/* The N_MS value defines the number of millisecond to be processed at each AudioProcess call,
that must be consistent with the N_MS_PER_INTERRUPT defined in the audio driver.
The default value of the N_MS_PER_INTERRUPT directive in the driver is set to 1,
for backward compatibility: leaving this values as it is allows to avoid any
modification in the application layer developed with the older versions of the driver */
#define N_MS (N_MS_PER_INTERRUPT)

/* Select used microphone:
  AMIC_ONBOARD --> Only analog  mic
  BOTH_ONBOARD --> Only digital mic
  DMIC_ONBOARD --> Both analog and digital mics
*/
#define ONBOARD_MIC BOTH_ONBOARD

#if ((ONBOARD_MIC & AMIC_ONBOARD) || (ONBOARD_MIC & DMIC_ONBOARD))
#define AUDIO_IN_CHANNELS 1
#else
#define AUDIO_IN_CHANNELS 2
#endif

#define AUDIO_IN_SAMPLING_FREQUENCY 16000 // 48000

#define AUDIO_IN_BUFFER_SIZE DEFAULT_AUDIO_IN_BUFFER_SIZE
#define AUDIO_VOLUME_INPUT 64U
#define BSP_AUDIO_IN_IT_PRIORITY 6U

/* Define the audio peripheral used: 1U = DFSDM */
#define BSP_AUDIO_IN_INSTANCE 1U

/* Define 1 to use already implemented callback; 0 to implement callback
   into an application file */
#define USE_BC_TIM_IRQ_CALLBACK 0U
#define USE_BC_GPIO_IRQ_HANDLER 1U
#define USE_BC_GPIO_IRQ_CALLBACK 1U

/* Enable/Disable sensor on board */
#define USE_MOTION_SENSOR_IIS2DH_0 0U
#define USE_MOTION_SENSOR_IIS2MDC_0 1U
#define USE_MOTION_SENSOR_IIS3DWB_0 0U
#define USE_MOTION_SENSOR_ISM330DHCX_0 1U
#define USE_ENV_SENSOR_HTS221_0 1U
#define USE_ENV_SENSOR_LPS22HH_0 1U
#define USE_ENV_SENSOR_STTS751_0 0U

/* ism330dhcx */
#define BSP_ISM330DHCX_CS_GPIO_CLK_ENABLE() __GPIOF_CLK_ENABLE()
#define BSP_ISM330DHCX_CS_PORT GPIOF
#define BSP_ISM330DHCX_CS_PIN GPIO_PIN_13

#define BSP_ISM330DHCX_INT2_GPIO_CLK_ENABLE() __GPIOF_CLK_ENABLE()
#define BSP_ISM330DHCX_INT2_GPIO_CLK_DISABLE() __GPIOF_CLK_DISABLE()
#define BSP_ISM330DHCX_INT2_PORT GPIOF
#define BSP_ISM330DHCX_INT2_PIN GPIO_PIN_4
#define BSP_ISM330DHCX_INT2_EXTI_IRQn EXTI4_IRQn

#define M_INT2_O_GPIO_CLK_ENABLE() BSP_ISM330DHCX_INT2_GPIO_CLK_ENABLE()
#define M_INT2_O_GPIO_CLK_DISABLE() BSP_ISM330DHCX_INT2_GPIO_CLK_DISABLE()
#define M_INT2_O_GPIO_PORT BSP_ISM330DHCX_INT2_PORT
#define M_INT2_O_PIN BSP_ISM330DHCX_INT2_PIN
#define M_INT2_O_EXTI_IRQn BSP_ISM330DHCX_INT2_EXTI_IRQn

#ifdef __cplusplus
}
#endif

#endif /* __STWIN_CONF_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
