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
	uint8_t  data;
	uint8_t  buffer[UART_BUFFER_LENGTH];
	uint16_t header;
	uint16_t tail;
	bool 	 opened;
}Uart_t;


Uart_t uart_arr[HW_UART_CHANNEL_MAX];

UART_HandleTypeDef huart1;

bool UartInit(uint8_t ch)
{
	bool ret = true;

	huart1.Instance 		    = USART1;
	huart1.Init.BaudRate 	    = 115200;
	huart1.Init.WordLength 	    = UART_WORDLENGTH_8B;
	huart1.Init.StopBits 	    = UART_STOPBITS_1;
	huart1.Init.Parity 		    = UART_PARITY_NONE;
	huart1.Init.Mode 		    = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl 	    = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling    = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}

	switch(ch)
	{
	case DEF_UART_CHANNEL_0:
		uart_arr[ch].opened = true;

		HAL_UART_Receive_IT(&huart1, &uart_arr[ch].data, 1);

		break;
	default:
		break;
	}

	return ret;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == huart1.Instance)
    {
        HAL_UART_Transmit_IT(&huart1, &uart_arr[DEF_UART_CHANNEL_0].data, 1);
        HAL_UART_Receive_IT(&huart1, &uart_arr[DEF_UART_CHANNEL_0].data, 1);
    }
}
