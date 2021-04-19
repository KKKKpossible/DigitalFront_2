/*
 * dma.h
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_DMA_H_
#define SRC_COMMON_HW_INC_SJK_DMA_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"


#ifdef HW_DMA_USE

bool DmaInit(void);

#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_DMA_H_ */
