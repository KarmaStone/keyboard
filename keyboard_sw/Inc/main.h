/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BATTERY_DECT_Pin GPIO_PIN_0
#define BATTERY_DECT_GPIO_Port GPIOA
#define EN_BATTERY_DECT_Pin GPIO_PIN_1
#define EN_BATTERY_DECT_GPIO_Port GPIOA
#define NRF_CS_Pin GPIO_PIN_4
#define NRF_CS_GPIO_Port GPIOA
#define NRF_SCK_Pin GPIO_PIN_5
#define NRF_SCK_GPIO_Port GPIOA
#define MRF_MISO_Pin GPIO_PIN_6
#define MRF_MISO_GPIO_Port GPIOA
#define NRF_MOSI_Pin GPIO_PIN_7
#define NRF_MOSI_GPIO_Port GPIOA
#define NRF_CSC4_Pin GPIO_PIN_4
#define NRF_CSC4_GPIO_Port GPIOC
#define NRF_IRQ_Pin GPIO_PIN_5
#define NRF_IRQ_GPIO_Port GPIOC
#define BLE_SRDY_Pin GPIO_PIN_7
#define BLE_SRDY_GPIO_Port GPIOC
#define BLE_MRDY_Pin GPIO_PIN_8
#define BLE_MRDY_GPIO_Port GPIOC
#define BLE_CMD_Pin GPIO_PIN_9
#define BLE_CMD_GPIO_Port GPIOC
#define BLE_RST_Pin GPIO_PIN_8
#define BLE_RST_GPIO_Port GPIOA
#define RGB_CTL_Pin GPIO_PIN_12
#define RGB_CTL_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
