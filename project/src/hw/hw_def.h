/*
 * hw_def.h
 *
 *  Created on: Apr 13, 2021
 *      Author: sungjinkim
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "bsp.h"
#include "def.h"


#define HW_UART_USE
#define     HW_UART_CHANNEL_MAX        (1U)

#define HW_GPIO_USE
#define     HW_GPIO_OUTPUT_CHANNEL_MAX (4U)
#define     HW_GPIO_INPUT_CHANNEL_MAX  (3U)

#define HW_CLI_USE
#define     HW_CLI_CHANNEL_MAX         (5U)

#define HW_LED_USE
#define     HW_LED_CHANNEL_MAX         (1U)

#endif /* SRC_HW_HW_DEF_H_ */
