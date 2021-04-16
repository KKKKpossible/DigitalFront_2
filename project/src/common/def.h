/*
 * def.h
 *
 *  Created on: Apr 13, 2021
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_DEF_H_
#define SRC_COMMON_DEF_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "stdbool.h"
#include "stdint.h"
#include "string.h"
#include "stdarg.h"

// uart channel
#define DEF_UART_CHANNEL_0        (0U)


// gpio output channel
#define DEF_GPIO_OUTPUT_CHANNEL_0 (0U)
#define DEF_GPIO_OUTPUT_CHANNEL_1 (1U)
#define DEF_GPIO_OUTPUT_CHANNEL_2 (2U)
#define DEF_GPIO_OUTPUT_CHANNEL_3 (3U)

// gpio input channel
#define DEF_GPIO_INPUT_CHANNEL_0  (0U)
#define DEF_GPIO_INPUT_CHANNEL_1  (1U)
#define DEF_GPIO_INPUT_CHANNEL_2  (2U)

// cli channel
#define DEF_CLI_CHANNEL_LED       (0U)
#define DEF_CLI_CHANNEL_CMD_MODE  (0U)

// led channel
#define DEF_LED_CHANNEL_0         (0U)


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_DEF_H_ */
