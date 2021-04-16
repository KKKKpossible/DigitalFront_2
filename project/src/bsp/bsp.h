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

//#include "adc.h"
//#include "i2c.h"
//#include "rtc.h"
//#include "spi.h"
//#include "tim.h"
//#include "usart.h"
//#include "gpio.h"


void BspInit(void);
void Error_Handler(void);


void     delay  (uint32_t mill);
uint32_t millis (void);

#ifdef __cplusplus
}
#endif

#endif /* SRC_BSP_BSP_H_ */
