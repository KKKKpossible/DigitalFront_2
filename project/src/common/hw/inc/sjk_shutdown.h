/*
 * sjk_ext_shutdown.h
 *
 *  Created on: 2021. 5. 4.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_SHUTDOWN_H_
#define SRC_COMMON_HW_INC_SJK_SHUTDOWN_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"
#include "sjk_gpio.h"


#ifdef  HW_EXT_SHUTDOWN_USE
#define DEF_EXT_SHUTDOWN_CHANNEL_MAX HW_EXT_SHUTDOWN_CHANNEL_MAX


bool      ExtShutdonInit (uint8_t ch);
ReadState ExtShutdonRead (uint8_t ch);


#endif


#ifdef  HW_SHUTDOWN_USE
#define DEF_SHUTDOWN_CHANNEL_MAX HW_SHUTDOWN_CHANNEL_MAX

bool      ShutdownInit   (uint8_t ch);
bool      ShutdownOn     (uint8_t ch);
bool      ShutdownOff    (uint8_t ch);
bool      ShutdownToggle (uint8_t ch);
ReadState ShutdownRead   (uint8_t ch);


#endif


#ifdef __cplusplus
}
#endif

#endif /* SRC_COMMON_HW_INC_SJK_SHUTDOWN_H_ */
