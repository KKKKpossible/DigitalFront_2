/*
 * sjk_flash.h
 *
 *  Created on: 2021. 4. 21.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_FLASH_H_
#define SRC_COMMON_HW_INC_SJK_FLASH_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"


#ifdef  HW_FLASH_USE
#define DEF_FLASH_CHANNEL_MAX HW_FLASH_CHANNEL_MAX


bool FlashInit  (void);
bool FlashErase (uint32_t addr, uint32_t length);
bool FlashWrite (uint32_t addr, uint8_t* p_data, uint32_t length);
bool FlashRead  (uint32_t addr, uint8_t* p_data, uint32_t length);


#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_FLASH_H_ */
