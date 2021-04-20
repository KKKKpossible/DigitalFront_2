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


typedef struct AD5592R_t
{
    uint8_t  now_tr_data[2];
    uint16_t db_100multiple;
}AD5592R_t;


bool     VvaInit  (uint8_t ch);
bool     VvaWrite (uint8_t ch, uint16_t db_100multiple);
uint16_t VvaRead  (uint8_t ch);


#endif


#ifdef _cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_VVA_H_ */
