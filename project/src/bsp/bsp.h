/*
 * bsp.h
 *
 *  Created on: 2021. 4. 13.
 *      Author: sungjinkim
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "stm32f1xx_hal.h"

#include "usart.h"


void BspInit(void);
void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* SRC_BSP_BSP_H_ */
