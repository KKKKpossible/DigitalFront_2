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


bool UartInit(uint8_t ch);


#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_UART_H_ */
