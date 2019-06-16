/**
  ******************************************************************************
  * File Name          : SPI.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
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

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */

SPI_HandleTypeDef hspi;
DMA_HandleTypeDef hdma_spi_tx;

void MX_SPI3_Init(void)
{
	hspi.Instance = SPI3;
	hspi.Init.Mode = SPI_MODE_MASTER;
	hspi.Init.Direction = SPI_DIRECTION_2LINES;
	hspi.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi.Init.NSS = SPI_NSS_SOFT;
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi.Init.CRCPolynomial = 7;
	hspi.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	if (HAL_SPI_Init(&hspi) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_HARD_OUTPUT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 7;
	hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		Error_Handler();
	}
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *spiHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (spiHandle->Instance == SPI1)
	{
		/* USER CODE BEGIN SPI1_MspInit 0 */

		/* USER CODE END SPI1_MspInit 0 */
		/* SPI1 clock enable */
		__HAL_RCC_SPI1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**SPI1 GPIO Configuration    
		PA4     ------> SPI1_NSS
		PA5     ------> SPI1_SCK
		PA6     ------> SPI1_MISO
		PA7     ------> SPI1_MOSI 
		*/
		GPIO_InitStruct.Pin = NRF_CS_Pin | NRF_SCK_Pin | MRF_MISO_Pin | NRF_MOSI_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN SPI1_MspInit 1 */

		/* USER CODE END SPI1_MspInit 1 */
	}
	if (spiHandle->Instance == SPI3)
	{

		/* Peripheral clock enable */
		__HAL_RCC_SPI3_CLK_ENABLE();

		/**SPI3 GPIO Configuration    
    	PC12     ------> SPI1_MOSI 
    	*/
		GPIO_InitStruct.Pin = GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* SPI3 DMA Init */
		/* SPI3_TX Init */
		hdma_spi_tx.Instance = DMA2_Channel2;
		hdma_spi_tx.Init.Request = DMA_REQUEST_3;
		hdma_spi_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_spi_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_spi_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_spi_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_spi_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_spi_tx.Init.Mode = DMA_NORMAL;
		hdma_spi_tx.Init.Priority = DMA_PRIORITY_LOW;
		if (HAL_DMA_Init(&hdma_spi_tx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(spiHandle, hdmatx, hdma_spi_tx);
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *spiHandle)
{
	if (spiHandle->Instance == SPI1)
	{
		/* USER CODE BEGIN SPI1_MspDeInit 0 */

		/* USER CODE END SPI1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI1_CLK_DISABLE();

		/**SPI1 GPIO Configuration    
		PA4     ------> SPI1_NSS
		PA5     ------> SPI1_SCK
		PA6     ------> SPI1_MISO
		PA7     ------> SPI1_MOSI 
		*/
		HAL_GPIO_DeInit(GPIOA, NRF_CS_Pin | NRF_SCK_Pin | MRF_MISO_Pin | NRF_MOSI_Pin);

		/* USER CODE BEGIN SPI1_MspDeInit 1 */
		
		/* USER CODE END SPI1_MspDeInit 1 */
	}
	if (spiHandle->Instance == SPI3)
	{
		/* Peripheral clock disable */
		__HAL_RCC_SPI3_CLK_DISABLE();

		/**SPI1 GPIO Configuration    
		PC12     ------> SPI3_MOSI 
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);

		/* Peripheral DMA DeInit*/
		HAL_DMA_DeInit(spiHandle->hdmatx);
	}
	
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
