/*
 * sjk_i2c.h
 *
 *  Created on: May 7, 2021
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_I2C_H_
#define SRC_COMMON_HW_INC_SJK_I2C_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"


#ifdef  HW_I2C_USE
#define DEF_I2C_CHANNEL_MAX HW_I2C_CHANNEL_MAX


bool I2CInit      (void);
bool I2CWrite     (uint8_t ch, uint8_t* data  , uint16_t size);
bool I2CRead      (uint8_t ch, uint8_t* buffer, uint16_t size);
bool I2CWriteRead (uint8_t ch, uint8_t* buffer, uint16_t size);


#endif


#ifdef __cplusplus
}
#endif



#endif /* SRC_COMMON_HW_INC_SJK_I2C_H_ */
