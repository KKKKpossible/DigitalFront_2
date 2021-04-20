/*
 * sjk_vva.h
 *
 *  Created on: 2021. 4. 20.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_VVA_H_
#define SRC_COMMON_HW_INC_SJK_VVA_H_


#ifdef _cplusplus
extern "C"{
#endif


#include "hw_def.h"


#ifdef  HW_VVA_USE
#define DEF_VVA_CHANNEL_MAX HW_VVA_CHANNEL_MAX


bool     VvaInit  (uint8_t ch);
bool     VvaWrite (uint8_t ch, uint16_t db_100multiple);
uint16_t VvaRead  (uint8_t ch);


#endif


#ifdef _cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_VVA_H_ */
