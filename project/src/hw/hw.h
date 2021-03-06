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
#include "sjk_cli_data.h"
#include "sjk_gpio.h"
#include "sjk_led.h"
#include "sjk_adc.h"
#include "sjk_dma.h"
#include "sjk_monitor.h"
#include "sjk_spi.h"
#include "sjk_vva.h"
#include "sjk_flash.h"
#include "sjk_shutdown.h"
#include "sjk_switch.h"
#include "sjk_i2c.h"


bool HwInit(void);


#ifdef __cplusplus
}
#endif


#endif /* SRC_HW_HW_H_ */
