/*
 * uart.h
 *
 *  Created on: 2021. 4. 13.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_UART_H_
#define SRC_COMMON_HW_INC_SJK_UART_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"


#ifdef  HW_UART_USE
#define DEF_UART_CHANNEL_MAX HW_UART_CHANNEL_MAX


#define UART_BUFFER_LENGTH (1024U)


typedef struct Uart_t
{
    uint8_t             data;
    uint8_t             rx_buffer[UART_BUFFER_LENGTH];
    uint8_t             tx_buffer[UART_BUFFER_LENGTH];
    uint16_t            rx_header;
    uint16_t            rx_tail;
    uint16_t            tx_header;
    uint16_t            tx_tail;
    bool                opened;
    UART_HandleTypeDef* phuart_n;
}Uart_t;


extern Uart_t            uart_arr[HW_UART_CHANNEL_MAX];
extern HAL_StatusTypeDef uart_status;


bool              UartInit                  (uint8_t ch);
bool              UartWriteTxBuffer         (uint8_t ch, uint8_t* data, uint16_t length);
bool              UartIsEmptyTxBuffer       (uint8_t ch);
bool              UartIsFullTxBuffer        (uint8_t ch);
bool              UartIsEmptyRxBuffer       (uint8_t ch);
bool              UartIsFullRxBuffer        (uint8_t ch);
uint8_t           UartReadRxBuffer          (uint8_t ch);
uint16_t          UartTxAvailable           (uint8_t ch);
uint16_t          UartRxAvailable           (uint8_t ch);
HAL_StatusTypeDef UartSendTxBufferPolling   (uint8_t ch, uint16_t length);
HAL_StatusTypeDef UartSendTxBufferInterrupt (uint8_t ch, uint16_t length);


#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_UART_H_ */
