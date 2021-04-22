/*
 * ap.c
 *
 *  Created on: Apr 13, 2021
 *      Author: sungjinkim
 */


#include "ap.h"


extern Parse_t parse_var;


bool ApInit(void)
{
	bool ret = true;

	return ret;
}

static void ParsingAp(void)
{
    uint16_t length = UartRxAvailable(DEF_UART_CHANNEL_0);
    if(length != 0)
    {
        for(int i = 0; i < length; i++)
        {
            uint8_t data = UartReadBuffer(DEF_UART_CHANNEL_0);
            if(parse_var.echo_on[SERIAL] == true)
            {
                UartWrite(DEF_UART_CHANNEL_0, &data, 1);
            }
            Parse(data);
        }
    }
}

bool ApMain(void)
{
	bool ret = true;
    static uint32_t tick = 0;

    ParsingAp();

	if(millis() - tick > 100)
    {
        tick = millis();
    }

	return ret;
}

