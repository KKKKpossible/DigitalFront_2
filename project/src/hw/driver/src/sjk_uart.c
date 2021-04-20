/*
 * uart.c
 *
 *  Created on: 2021. 4. 13.
 *      Author: sungjinkim
 */


#include "sjk_uart.h"


#define UART_BUFFER_LENGTH (100U)


typedef struct Uart_t
{
	uint8_t             data;
	uint8_t             rx_buffer[UART_BUFFER_LENGTH];
	uint8_t             tx_buffer[UART_BUFFER_LENGTH];
	uint16_t            rx_header;
	uint16_t            rx_tail;
	uint16_t            tx_header;
    uint16_t            tx_tail;
	bool 	            opened;
	UART_HandleTypeDef* phuart_n;
}Uart_t;


Uart_t uart_arr[HW_UART_CHANNEL_MAX];
UART_HandleTypeDef huart1;


static bool SjkUartInit  (uint8_t ch);
static bool AutoUartInit (void);
static void UartSend     (uint8_t ch);

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
    GPIO_InitStruct.Pin   = GPIO_PIN_9;
    GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin  = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}


bool UartWrite(uint8_t ch, uint8_t* data, uint16_t length)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            for(int i = 0; i < length; i++)
            {
                if((uart_arr[ch].tx_header + 1) % UART_BUFFER_LENGTH != uart_arr[ch].tx_tail)
                {
                    uart_arr[ch].tx_buffer[uart_arr[ch].tx_header] = data[i];
                    uart_arr[ch].tx_header = (uart_arr[ch].tx_header + 1) % UART_BUFFER_LENGTH;
                }
            }

            UartSend(ch);
            break;
        default:
            break;
    }

    return ret;
}

uint8_t UartReadBuffer(uint8_t ch)
{
    uint8_t ret = '\0';

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(uart_arr[ch].rx_tail != uart_arr[ch].rx_header)
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

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(uart_arr[ch].tx_header - uart_arr[ch].tx_tail % UART_BUFFER_LENGTH != 0)
            {
                ret = (uart_arr[ch].tx_header - uart_arr[ch].tx_tail + UART_BUFFER_LENGTH) % UART_BUFFER_LENGTH;
            }
            break;
        default:
            break;
    }

    return ret;
}

uint16_t UartRxAvailable(uint8_t ch)
{
    uint16_t ret = 0;

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(uart_arr[ch].rx_header - uart_arr[ch].rx_tail % UART_BUFFER_LENGTH != 0)
            {
                ret = (uart_arr[ch].rx_header - uart_arr[ch].rx_tail + UART_BUFFER_LENGTH) % UART_BUFFER_LENGTH;
            }
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
            if(UartTxAvailable(i) != 0)
            {
                UartSend(i);
            }
            break;
        }
    }
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

    huart1.Instance          = USART1;
    huart1.Init.BaudRate     = 115200;
    huart1.Init.WordLength   = UART_WORDLENGTH_8B;
    huart1.Init.StopBits     = UART_STOPBITS_1;
    huart1.Init.Parity       = UART_PARITY_NONE;
    huart1.Init.Mode         = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }

    return ret;
}

static void UartSend(uint8_t ch)
{
    int left = 0;

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            left = UartTxAvailable(ch);

            if(left > 8)
            {
                left = 8;
            }

            HAL_StatusTypeDef status = HAL_UART_Transmit(uart_arr[ch].phuart_n, &uart_arr[ch].tx_buffer[uart_arr[ch].tx_tail], left, 10);

            uint32_t time_out = millis();
            while(status == HAL_BUSY)
            {
                status = HAL_UART_Transmit(uart_arr[ch].phuart_n, &uart_arr[ch].tx_buffer[uart_arr[ch].tx_tail], left, 10);
                if(millis() - time_out > 10)
                {
                    break;
                }
            }
            uart_arr[ch].tx_tail = (uart_arr[ch].tx_tail + left) % UART_BUFFER_LENGTH;
            break;
        default:
            break;
    }
}
