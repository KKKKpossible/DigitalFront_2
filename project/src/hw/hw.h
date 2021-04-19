/*
 * hw.h
 *
 *  Created on: Apr 13, 2021
 *      Author: sungjinkim
 */

#ifndef SRC_HW_HW_H_
#define SRC_HW_HW_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"

#include "sjk_gpio.h"
#include "sjk_uart.h"
#include "sjk_cli.h"
#include "sjk_gpio.h"
#include "sjk_led.h"
#include "sjk_adc.h"
#include "sjk_dma.h"
#include "sjk_monitor.h"


bool HwInit(void);


#ifdef __cplusplus
}
#endif


#endif /* SRC_HW_HW_H_ */
