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
#define DEF_UART_CHANNEL_0                 (0U)


// gpio output channel
#define DEF_GPIO_OUTPUT_CHANNEL_0  (0U)
#define DEF_GPIO_OUTPUT_CHANNEL_1  (1U)
#define DEF_GPIO_OUTPUT_CHANNEL_2  (2U)
#define DEF_GPIO_OUTPUT_CHANNEL_3  (3U)

// gpio input channel
#define DEF_GPIO_INPUT_CHANNEL_0   (0U)
#define DEF_GPIO_INPUT_CHANNEL_1   (1U)
#define DEF_GPIO_INPUT_CHANNEL_2   (2U)

// led channel
#define DEF_LED_CHANNEL_0          (0U)

// adc channel
#define DEF_ADC_CHANNEL_0          (0U)
#define DEF_ADC_CHANNEL_1          (1U)
#define DEF_ADC_CHANNEL_2          (2U)
#define DEF_ADC_CHANNEL_3          (3U)
#define DEF_ADC_CHANNEL_4          (4U)
#define DEF_ADC_CHANNEL_5          (5U)
#define DEF_ADC_CHANNEL_6          (6U)
#define DEF_ADC_CHANNEL_7          (7U)

// monitor channel
#define DEF_MONITOR_CHANNEL_0      (0U)
#define DEF_MONITOR_CHANNEL_1      (1U)
#define DEF_MONITOR_CHANNEL_2      (2U)
#define DEF_MONITOR_CHANNEL_3      (3U)
#define DEF_MONITOR_CHANNEL_4      (4U)
#define DEF_MONITOR_CHANNEL_5      (5U)
#define DEF_MONITOR_CHANNEL_6      (6U)
#define DEF_MONITOR_CHANNEL_7      (7U)
#define DEF_MONITOR_CHANNEL_8      (8U)
#define DEF_MONITOR_CHANNEL_9      (9U)

#define DEF_MONITOR_CURR_0         (DEF_MONITOR_CHANNEL_0)
#define DEF_MONITOR_TEMP_0         (DEF_MONITOR_CHANNEL_1)
#define DEF_MONITOR_HTEMP_0        (DEF_MONITOR_CHANNEL_2)
#define DEF_MONITOR_EXT_ATTEN_0    (DEF_MONITOR_CHANNEL_3)
#define DEF_MONITOR_INT_ATTEN_0    (DEF_MONITOR_CHANNEL_4)
#define DEF_MONITOR_EXT_SWITCH_0   (DEF_MONITOR_CHANNEL_5)
#define DEF_MONITOR_EXT_SWITCH_1   (DEF_MONITOR_CHANNEL_6)
#define DEF_MONITOR_HPA_SHUTDOWN_0 (DEF_MONITOR_CHANNEL_7)
#define DEF_MONITOR_EXT_SHUTDOWN_0 (DEF_MONITOR_CHANNEL_8)
#define DEF_MONITOR_FAULT          (DEF_MONITOR_CHANNEL_9)

#define DEF_SPI_CHANNEL_0          (0U)

#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_DEF_H_ */
