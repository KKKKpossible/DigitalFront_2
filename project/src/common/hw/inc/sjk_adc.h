/*
 * sjk_adc.h
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_ADC_H_
#define SRC_COMMON_HW_INC_SJK_ADC_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"


#ifdef  HW_ADC_USE
#define DEF_ADC_CHANNEL_MAX HW_ADC_CHANNEL_MAX


bool AdcInit  (void);
bool AdcStart (void);
bool AdcStop  (void);


#endif


//uint32_t AdcRead(ADC_HandleTypeDef* hadc);



#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_ADC_H_ */
