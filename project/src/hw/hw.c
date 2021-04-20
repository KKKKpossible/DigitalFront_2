/*
 * hw.c
 *
 *  Created on: 2021. 4. 13.
 *      Author: sungjinkim
 */


#include "hw.h"


bool HwInit(void)
{
	bool ret = true;

	BspInit();

    DmaInit();

	GpioInit();
	UartInit(DEF_UART_CHANNEL_0);

	LedInit(DEF_LED_CHANNEL_0);

	CliInit();

	AdcInit();

	MonitorInit();

    SpiInit(DEF_SPI_CHANNEL_0);

	VvaInit(DEF_VVA_CHANNEL_0);

	return ret;
}
