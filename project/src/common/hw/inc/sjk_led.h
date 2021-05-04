/*
 * sjk_led.h
 *
 *  Created on: 2021. 4. 16.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_LED_H_
#define SRC_COMMON_HW_INC_SJK_LED_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"
#include "sjk_gpio.h"


#ifdef  HW_LED_USE
#define DEF_LED_CHANNEL_MAX HW_LED_CHANNEL_MAX


bool      LedInit   (uint8_t ch);
bool      LedOn     (uint8_t ch);
bool      LedOff    (uint8_t ch);
bool      LedToggle (uint8_t ch);
ReadState LedRead   (uint8_t ch);

#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_LED_H_ */
