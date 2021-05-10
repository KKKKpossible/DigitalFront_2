/*
 * sjk_spi.c
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */


#include "sjk_spi.h"
#include "sjk_gpio.h"


SPI_HandleTypeDef hspi1;


bool SpiInit(uint8_t ch)
{
    bool    ret = true;
    uint8_t data[2] = {0, };


    /* USER CODE BEGIN SPI1_Init 0 */

    /* USER CODE END SPI1_Init 0 */

    /* USER CODE BEGIN SPI1_Init 1 */

    /* USER CODE END SPI1_Init 1 */
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
      Error_Handler();
    }

    switch(ch)
    {
        case DEF_SPI_CHANNEL_0:
            data[0] = 0b00101000;
            data[1] = 0b00000001;
            SpiWrite(DEF_SPI_CHANNEL_0, data, 2);
            break;
        default:
            break;
    }

    return ret;
}

bool SpiWrite(uint8_t ch, uint8_t* data, uint16_t size)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_SPI_CHANNEL_0:
            GpioOff(DEF_SPI_SS_CHANNEL_0);
            HAL_SPI_Transmit(&hspi1, data, size, 10);
//            HAL_SPI_Transmit_IT(&hspi1, data, size);
            GpioOn(DEF_SPI_SS_CHANNEL_0);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool SpiRead(uint8_t ch, uint8_t* buffer, uint16_t size)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_SPI_CHANNEL_0:
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool SpiWriteRead(uint8_t ch, uint8_t* buffer, uint16_t size)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_SPI_CHANNEL_0:
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
}


void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* SPI1 interrupt Init */
    HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SPI1_IRQn);
  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

    /* SPI1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(SPI1_IRQn);
  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
}
