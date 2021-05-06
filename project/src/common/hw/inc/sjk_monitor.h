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


bool     MonitorInit         (void);
int64_t  MonitorRead         (uint8_t ch);
int64_t  MonitorReadData     (uint8_t ch);
int      MonitorReadCount    (uint8_t ch);
int64_t MonitorReadCountMax  (uint8_t ch);
int64_t MonitorReadLimit     (uint8_t ch);
void     MonitorDataSet      (uint8_t ch, int64_t data     );
void     MonitorDataAddOr    (uint8_t ch, int64_t data     );
void     MonitorDataDelAnd   (uint8_t ch, int64_t data     );
void     MonitorOffsetSet    (uint8_t ch, int64_t offset   );
void     MonitorRatioPerSet  (uint8_t ch, int64_t ratio_per);
void     MonitorRatioValSet  (uint8_t ch, int64_t ratio_val);
void     MonitorCountAdd     (uint8_t ch, int64_t data     );
void     MonitorLimitSet     (uint8_t ch, int64_t limit    );

#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_MONITOR_H_ */
