/**
******************************************************************************
* @file    STWIN_bus.h
* @author  SRA - Central Labs
* @version V1.0.0
* @date    05-Jul-19
* @brief   header file for the BSP BUS IO driver
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
* All rights reserved.</center></h2>
*
* This software component is licensed by ST under BSD 3-Clause license,
* the "License"; You may not use this file except in compliance with the
* License. You may obtain a copy of the License at:
*                        opensource.org/licenses/BSD-3-Clause
*
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STWIN_BUS_H
#define STWIN_BUS_H

#ifdef __cplusplus
 extern "C" {
#endif


#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
typedef struct
{
  pI2C_CallbackTypeDef  pMspI2cInitCb;
  pI2C_CallbackTypeDef  pMspI2cDeInitCb;
} BSP_I2C_Cb_t;
#endif /* (USE_HAL_I2C_REGISTER_CALLBACKS == 1) */

//#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
//typedef struct
//{
//  pSPI_CallbackTypeDef  pMspSpiInitCb;
//  pSPI_CallbackTypeDef  pMspSpiDeInitCb;
//}BSP_SPI_Cb_t;
//#endif /* (USE_HAL_SPI_REGISTER_CALLBACKS == 1) */


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* BUS IO driver over I2C Peripheral */
int32_t BSP_I2C1_Init(void);
int32_t BSP_I2C1_DeInit(void);
int32_t BSP_I2C1_IsReady(void);
int32_t BSP_I2C1_WriteReg(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C1_ReadReg(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C1_WriteReg16(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C1_ReadReg16(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C1_Send(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_Recv(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_SendRecv(uint16_t DevAddr, uint8_t *pTxdata, uint8_t *pRxdata, uint16_t Length);
int32_t BSP_I2C2_Init(void);
int32_t BSP_I2C2_DeInit(void);
int32_t BSP_I2C2_IsReady(void);
int32_t BSP_I2C2_WriteReg(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C2_ReadReg(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C2_WriteReg16(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C2_ReadReg16(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C2_Send(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C2_Recv(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C2_SendRecv(uint16_t DevAddr, uint8_t *pTxdata, uint8_t *pRxdata, uint16_t Length);
int32_t BSP_I2C4_Init(void);
int32_t BSP_I2C4_DeInit(void);
int32_t BSP_I2C4_IsReady(void);
int32_t BSP_I2C4_WriteReg(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C4_ReadReg(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C4_WriteReg16(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C4_ReadReg16(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C4_Send(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C4_Recv(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C4_SendRecv(uint16_t DevAddr, uint8_t *pTxdata, uint8_t *pRxdata, uint16_t Length);
/* BUS IO driver over SPI Peripheral */
int32_t BSP_SPI1_Init(void);
int32_t BSP_SPI1_DeInit(void);
int32_t BSP_SPI1_Send(uint8_t *pData, uint16_t len);
int32_t BSP_SPI1_Recv(uint8_t *pData, uint16_t len);
int32_t BSP_SPI1_SendRecv(uint8_t *pTxData, uint8_t *pRxData, uint16_t len);
int32_t BSP_SPI2_Init(void);
int32_t BSP_SPI2_DeInit(void);
int32_t BSP_SPI2_Send(uint8_t *pData, uint16_t len);
int32_t BSP_SPI2_Recv(uint8_t *pData, uint16_t len);
int32_t BSP_SPI2_SendRecv(uint8_t *pTxData, uint8_t *pRxData, uint16_t len);
int32_t BSP_SPI3_Init(void);
int32_t BSP_SPI3_DeInit(void);
int32_t BSP_SPI3_Send(uint8_t *pData, uint16_t len);
int32_t BSP_SPI3_Recv(uint8_t *pData, uint16_t len);
int32_t BSP_SPI3_SendRecv(uint8_t *pTxData, uint8_t *pRxData, uint16_t len);
/* BUS IO driver over USART Peripheral */
int32_t BSP_USART3_Init(void);
int32_t BSP_USART3_DeInit(void);

int32_t BSP_GetTick(void);

//#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
//int32_t BSP_SPI_RegisterDefaultMspCallbacks (void);
//int32_t BSP_SPI_RegisterMspCallbacks (BSP_SPI_Cb_t *Callbacks);
//#endif /* (USE_HAL_SPI_REGISTER_CALLBACKS == 1)) */

#ifdef __cplusplus
}
#endif

#endif /* STWIN_BUS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/