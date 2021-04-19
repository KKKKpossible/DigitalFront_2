/*
 * sjk_monitor.h
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_MONITOR_H_
#define SRC_COMMON_HW_INC_SJK_MONITOR_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"


#ifdef  HW_MONITOR_USE
#define DEF_MONITOR_CHANNEL_MAX HW_MONITOR_CHANNEL_MAX


bool MonitorInit  (void);
bool MonitorRead  (uint8_t ch, uint32_t* retbuff); // not clear
bool MonitorWrite (uint8_t ch, uint32_t  data);    // not clear


#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_MONITOR_H_ */
