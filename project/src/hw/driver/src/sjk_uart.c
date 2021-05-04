/*
 * uart.c
 *
 *  Created on: 2021. 4. 13.
 *      Author: sungjinkim
 */


#include "sjk_uart.h"


#define UART_INTERRUPT_LENGTH_MAX (1U)


Uart_t             uart_arr[HW_UART_CHANNEL_MAX];
UART_HandleTypeDef huart1;
HAL_StatusTypeDef  uart_status;
DMA_HandleTypeDef  hdma_usart1_rx;


static bool SjkUartInit  (uint8_t ch);
static bool AutoUartInit (void);


bool UartInit(uint8_t ch)
{
    bool ret = true;

    AutoUartInit();
    SjkUartInit(ch);

    return ret;
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel5;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

bool UartWriteTxBuffer(uint8_t ch, uint8_t* data, uint16_t length)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            for(int i = 0; i < length; i++)
            {
                if(UartIsFullTxBuffer(ch) != true)
                {
                    uart_arr[ch].tx_buffer[uart_arr[ch].tx_header] = data[i];
                    uart_arr[ch].tx_header = (uart_arr[ch].tx_header + 1) % UART_BUFFER_LENGTH;
                }
                else
                {
                    ret = false;
                    break;
                }
            }
            break;
        default:
            break;
    }

    return ret;
}

bool UartIsEmptyTxBuffer(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(uart_arr[ch].tx_header != uart_arr[ch].tx_tail)
            {
                ret = false;
            }
            break;
        default:
            break;
    }

    return ret;
}

bool UartIsFullTxBuffer(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if((uart_arr[ch].tx_header + 1) % UART_BUFFER_LENGTH != uart_arr[ch].tx_tail)
            {
                ret = false;
            }
            break;
        default:
            break;
    }

    return ret;
}

bool UartIsEmptyRxBuffer(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(uart_arr[ch].rx_header != uart_arr[ch].rx_tail)
            {
                ret = false;
            }
            break;
        default:
            break;
    }

    return ret;
}

bool UartIsFullRxBuffer(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if((uart_arr[ch].rx_header + 1) % UART_BUFFER_LENGTH != uart_arr[ch].rx_tail)
            {
                ret = false;
            }
            break;
        default:
            break;
    }

    return ret;
}



uint8_t UartReadRxBuffer(uint8_t ch)
{
    uint8_t ret = '\0';

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(UartRxAvailable(ch) != 0)
            {
                ret = uart_arr[ch].rx_buffer[uart_arr[ch].rx_tail];
                uart_arr[ch].rx_tail = (uart_arr[ch].rx_tail + 1) % UART_BUFFER_LENGTH;
            }
            break;
        default:
            break;
    }
    return ret;
}

uint16_t UartTxAvailable(uint8_t ch)
{
    uint16_t ret = 0;
    int length = 0;

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            length = (uart_arr[ch].tx_header - uart_arr[ch].tx_tail);
            if(length < 0)
            {
                length += UART_BUFFER_LENGTH;
            }
            ret = length;
            break;
        default:
            break;
    }

    return ret;
}

uint16_t UartRxAvailable(uint8_t ch)
{
    uint16_t ret = 0;
    int length = 0;

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            length = (uart_arr[ch].rx_header - uart_arr[ch].rx_tail);
            if(length < 0)
            {
                length += UART_BUFFER_LENGTH;
            }
            ret = length;

            break;
        default:
            break;
    }
    return ret;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    for(int i = 0; i < DEF_UART_CHANNEL_MAX; i++)
    {
        if(huart == uart_arr[i].phuart_n)
        {
            if((uart_arr[i].rx_header + 1) % UART_BUFFER_LENGTH != uart_arr[i].rx_tail)
            {
                uart_arr[i].rx_buffer[uart_arr[i].rx_header] = uart_arr[i].data;
                uart_arr[i].rx_header = (uart_arr[i].rx_header + 1) % UART_BUFFER_LENGTH;
            }
            HAL_UART_Receive_IT(uart_arr[i].phuart_n, &uart_arr[i].data, 1);
            break;
        }
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    for(int i = 0; i < DEF_UART_CHANNEL_MAX; i++)
    {
        if(huart == uart_arr[i].phuart_n)
        {
            uart_arr[DEF_UART_CHANNEL_0].tx_tail = (uart_arr[DEF_UART_CHANNEL_0].tx_tail + UART_INTERRUPT_LENGTH_MAX) % UART_BUFFER_LENGTH;

            if(UartIsEmptyTxBuffer(DEF_UART_CHANNEL_0) != true)
            {
                UartSendTxBufferInterrupt(DEF_UART_CHANNEL_0, UartTxAvailable(DEF_UART_CHANNEL_0));
            }
            break;
        }
    }
}

HAL_StatusTypeDef UartSendTxBufferInterrupt(uint8_t ch, uint16_t length)
{
    HAL_StatusTypeDef status = HAL_OK;

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(UartIsEmptyTxBuffer(ch) != true)
            {
                uint8_t tx_buff_buff = '\0';

                if(length > 0)
                {
                    length = UART_INTERRUPT_LENGTH_MAX;

                    tx_buff_buff = uart_arr[ch].tx_buffer[uart_arr[ch].tx_tail];
                    status = HAL_UART_Transmit_IT(uart_arr[ch].phuart_n, &tx_buff_buff, length);
                }
            }
            break;
        default:
            break;
    }

    return status;
}

HAL_StatusTypeDef UartSendTxBufferPolling(uint8_t ch, uint16_t length)
{
    HAL_StatusTypeDef status = HAL_OK;
    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(UartIsEmptyTxBuffer(ch) != true)
            {
                uint8_t tx_buff_buff[8] = {0, };

                if(length > 8)
                {
                    length = 8;
                }

                if(uart_arr[ch].tx_tail + length > UART_BUFFER_LENGTH - 1)
                {
                    int index = 0;
                    int index_2 = 0;

                    for(int i = uart_arr[ch].tx_tail; i < UART_BUFFER_LENGTH; i++)
                    {
                        tx_buff_buff[index] = uart_arr[ch].tx_buffer[uart_arr[ch].tx_tail];
                        index++;
                    }
                    index_2 = uart_arr[ch].tx_tail + length - (UART_BUFFER_LENGTH - 1) - index;
                    for(int i = 0; i < index_2; i++)
                    {
                        tx_buff_buff[index] = uart_arr[ch].tx_buffer[i];
                        index++;
                    }
                }
                else
                {
                    for(int i = 0; i < length; i++)
                    {
                        tx_buff_buff[i] = uart_arr[ch].tx_buffer[uart_arr[ch].tx_tail + i];
                    }
                }
                status = HAL_UART_Transmit(uart_arr[ch].phuart_n, tx_buff_buff, length, 10);
                if(status == HAL_OK)
                {
                    uart_arr[ch].tx_tail = (uart_arr[ch].tx_tail + length) % UART_BUFFER_LENGTH;
                }
            }
            break;
        default:
            break;
    }

    return status;
}

static bool SjkUartInit(uint8_t ch)
{
    bool ret = true;

    for(int i = 0; i < DEF_UART_CHANNEL_MAX; i++)
    {
        switch(i)
        {
            case DEF_UART_CHANNEL_0:
                uart_arr[i].phuart_n = &huart1;
                HAL_UART_Receive_IT(uart_arr[i].phuart_n, &uart_arr[i].data, 1);
                break;
            default:
                break;
        }
    }

    return ret;
}

static bool AutoUartInit(void)
{
    bool ret = true;
    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
      Error_Handler();
    }
    return ret;
}
