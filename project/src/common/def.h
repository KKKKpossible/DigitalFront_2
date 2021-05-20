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
#include "stdlib.h"
#include "stdio.h"


// uart channel
#define DEF_UART_CHANNEL_0         (0U)

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
#define DEF_LED_CHANNEL_1          (1U)

// adc channel
#define DEF_ADC_CHANNEL_0          (0U)
#define DEF_ADC_CHANNEL_1          (1U)
#define DEF_ADC_CHANNEL_2          (2U)
#define DEF_ADC_CHANNEL_3          (3U)
#define DEF_ADC_CHANNEL_4          (4U)
#define DEF_ADC_CHANNEL_5          (5U)
#define DEF_ADC_CHANNEL_6          (6U)
#define DEF_ADC_CHANNEL_7          (7U)

#define DEF_ADC_CURRENT_0          (DEF_ADC_CHANNEL_0)
#define DEF_ADC_TEMP_0             (DEF_ADC_CHANNEL_1)
#define DEF_ADC_HS_TEMP_0          (DEF_ADC_CHANNEL_2)
#define DEF_ADC_EXT_ATTEN_0        (DEF_ADC_CHANNEL_3)

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
#define DEF_MONITOR_FAULT_0        (DEF_MONITOR_CHANNEL_9)

// spi channel
#define DEF_SPI_CHANNEL_0          (0U)
#define DEF_SPI_SS_CHANNEL_0       (DEF_GPIO_OUTPUT_CHANNEL_2)

// vva channel
#define DEF_VVA_CHANNEL_0          (0U)

// shutdown channel
#define DEF_EXT_SHUTDOWN_CHANNEL_0 (0U)
#define DEF_SHUTDOWN_CHANNEL_0     (0U)

// switch channel
#define DEF_SWITCH_CHANNEL_0       (0U)
#define DEF_SWITCH_CHANNEL_1       (1U)

// fault channel
#define DEF_FAULT_CHANNEL_0        (0U)
#define DEF_FAULT_CHANNEL_1        (1U)
#define DEF_FAULT_CHANNEL_2        (2U)
#define DEF_FAULT_CHANNEL_3        (3U)
#define DEF_FAULT_CHANNEL_4        (4U)

#define DEF_FAULT_CURRENT_0        (DEF_FAULT_CHANNEL_0)
#define DEF_FAULT_TEMPERATURE_0    (DEF_FAULT_CHANNEL_1)
#define DEF_FAULT_HS_TEMPERATURE_0 (DEF_FAULT_CHANNEL_2)
#define DEF_FAULT_VOLTAGE_0        (DEF_FAULT_CHANNEL_3)
#define DEF_FAULT_OLED             (DEF_FAULT_CHANNEL_4)

// i2c channel
#define DEF_I2C_CHANNEL_0          (0U)

// lcd channel
#define DEF_OLED_CHANNEL_0         (0U)


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_DEF_H_ */
