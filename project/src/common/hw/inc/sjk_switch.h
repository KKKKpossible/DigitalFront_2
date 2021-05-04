/*
 * sjk_switch.h
 *
 *  Created on: 2021. 5. 4.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_SWITCH_H_
#define SRC_COMMON_HW_INC_SJK_SWITCH_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"
#include "sjk_gpio.h"


#ifdef  HW_SWITCH_USE
#define DEF_SWITCH_CHANNEL_MAX HW_SWITCH_CHANNEL_MAX


bool      SwitchInit (uint8_t ch);
ReadState SwitchRead (uint8_t ch);


#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_SWITCH_H_ */
