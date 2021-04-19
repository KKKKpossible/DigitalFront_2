/*
 * sjk_spi.h
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_SPI_H_
#define SRC_COMMON_HW_INC_SJK_SPI_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"


#ifdef  HW_SPI_USE
#define DEF_SPI_CHANNEL_MAX HW_SPI_CHANNEL_MAX


bool SpiInit  (void);
bool SpiWrite (uint8_t ch, uint16_t* data);
bool SpiRead  (uint8_t ch, uint16_t* buffer);


#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_SPI_H_ */
