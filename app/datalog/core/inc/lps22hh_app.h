/**
 ******************************************************************************
 * @file    lps22hh_app.h
 * @author  SRA - MCD
 *
 *
 * @brief   Header for lps22hh_app.c module.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LPS22HH_APP_H
#define __LPS22HH_APP_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "lps22hh_reg.h"
#include "sensors_manager.h"
#include "stm32l4xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define LPS22HH_SAMPLES_PER_TS (256)

    /* Exported macro ------------------------------------------------------------*/
    /* Exported variables --------------------------------------------------------*/
    extern SM_Init_Param_t LPS22HH_Init_Param;

    /* Exported functions ------------------------------------------------------- */
    void LPS22HH_Peripheral_Init(void);
    void LPS22HH_OS_Init(void);
    void LPS22HH_Data_Ready(
        uint8_t subSensorId, uint8_t* buf, uint16_t size, double timeStamp);
    void LPS22HH_Set_ODR(float newODR);
    void LPS22HH_Set_FS(float newFS1, float newFS2);
    void LPS22HH_Start(void);
    void LPS22HH_Stop(void);
    uint8_t LPS22HH_Create_Sensor(const SM_Init_Param_t* pxParams);
    uint8_t LPS22HH_Get_Id(void);

    uint8_t LPS22HH_updateConfig(void);

#ifdef __cplusplus
}
#endif

#endif /* __LPS22HH_APP_H */
