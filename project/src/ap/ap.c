/*
 * ap.c
 *
 *  Created on: Apr 13, 2021
 *      Author: sungjinkim
 */


#include "ap.h"


#define JUDGE_HIGH_COUNT (200U)


extern Parse_t parse_var;


uint64_t global_fault;


static void ParsingAp        (void);
static void MonitorReadAp    (void);
static void MonitorOperateAp (void);
static void BlinkAp          (void);


bool ApInit(void)
{
	bool ret = true;

    delay(30);

	return ret;
}

bool ApMain(void)
{
	bool   ret           = true;
    static uint32_t tick = 0;

    ParsingAp();

	if(millis() - tick > 1)
    {
	    tick = millis();

	    MonitorReadAp();
	    MonitorOperateAp();

	    BlinkAp();
    }

	return ret;
}

static void BlinkAp(void)
{
    static uint16_t blink = 0;

    if(blink > 500)
    {
        LedOn(DEF_LED_CHANNEL_0);
        if(blink > 1000)
        {
            blink = 0;
        }
    }
    else
    {
        LedOff(DEF_LED_CHANNEL_0);
    }

    blink++;
}

static void ParsingAp(void)
{
    int uart_rxlength = UartRxAvailable(DEF_UART_CHANNEL_0);

    if(uart_rxlength != 0)
    {
        uint8_t data = UartReadRxBuffer(DEF_UART_CHANNEL_0);
        Parse(DEF_UART_CHANNEL_0, data);
    }
}

static void MonitorReadAp(void)
{
    uint32_t hw_channel;

    for(int ch = DEF_MONITOR_CHANNEL_0; ch < DEF_MONITOR_CHANNEL_MAX; ch++)
    {
        switch(ch)
        {
            case DEF_MONITOR_CURR_0:         // (DEF_MONITOR_CHANNEL_0)
                break;
            case DEF_MONITOR_TEMP_0:         // (DEF_MONITOR_CHANNEL_1)
                break;
            case DEF_MONITOR_HTEMP_0:        // (DEF_MONITOR_CHANNEL_2)
                break;
            case DEF_MONITOR_EXT_ATTEN_0:    // (DEF_MONITOR_CHANNEL_3)
                break;
            case DEF_MONITOR_INT_ATTEN_0:    // (DEF_MONITOR_CHANNEL_4)
                break;
            case DEF_MONITOR_EXT_SWITCH_0:   // (DEF_MONITOR_CHANNEL_5)
                hw_channel = DEF_SWITCH_CHANNEL_0;
                if(SwitchRead(hw_channel) == RS_GPIO_PIN_SET)
                {
                    MonitorCountAdd(ch, 1);
                }
                else
                {
                    if(MonitorReadCount(ch) != 0)
                    {
                        MonitorCountAdd(ch, -1);
                    }
                }
                break;
            case DEF_MONITOR_EXT_SWITCH_1:   // (DEF_MONITOR_CHANNEL_6)
                hw_channel = DEF_SWITCH_CHANNEL_1;
                if(SwitchRead(hw_channel) == RS_GPIO_PIN_SET)
                {
                    MonitorCountAdd(ch, 1);
                }
                else
                {
                    if(MonitorReadCount(ch) != 0)
                    {
                        MonitorCountAdd(ch, -1);
                    }
                }
                break;
            case DEF_MONITOR_HPA_SHUTDOWN_0: // (DEF_MONITOR_CHANNEL_7)
                hw_channel = DEF_SHUTDOWN_CHANNEL_0;
                if(ShutdownRead(hw_channel) == RS_GPIO_PIN_SET)
                {
                    MonitorCountAdd(ch, 1);
                }
                else
                {
                    if(MonitorReadCount(ch) != 0)
                    {
                        MonitorCountAdd(ch, -1);
                    }
                }
                break;
            case DEF_MONITOR_EXT_SHUTDOWN_0: // (DEF_MONITOR_CHANNEL_8)
                hw_channel = DEF_EXT_SHUTDOWN_CHANNEL_0;
                if(ExtShutdonRead(hw_channel) == RS_GPIO_PIN_SET)
                {
                    MonitorCountAdd(ch, 1);
                }
                else
                {
                    if(MonitorReadCount(ch) != 0)
                    {
                        MonitorCountAdd(ch, -1);
                    }
                }
                break;
            default:
                break;
        }
    }
}

static void MonitorOperateAp (void)
{
    static uint64_t fault_buff = 0;
    uint32_t hw_channel;

    for(int ch = DEF_MONITOR_CHANNEL_0; ch < DEF_MONITOR_CHANNEL_MAX; ch++)
    {
        switch(ch)
        {
            case DEF_MONITOR_CURR_0:         // (DEF_MONITOR_CHANNEL_0)
                break;
            case DEF_MONITOR_TEMP_0:         // (DEF_MONITOR_CHANNEL_1)
                break;
            case DEF_MONITOR_HTEMP_0:        // (DEF_MONITOR_CHANNEL_2)
                break;
            case DEF_MONITOR_EXT_ATTEN_0:    // (DEF_MONITOR_CHANNEL_3)
                break;
            case DEF_MONITOR_INT_ATTEN_0:    // (DEF_MONITOR_CHANNEL_4)
                break;
            case DEF_MONITOR_EXT_SWITCH_0:   // (DEF_MONITOR_CHANNEL_5)
                hw_channel = DEF_SWITCH_CHANNEL_0;
                if(MonitorReadCount(ch) > MonitorReadCountMax(ch))
                {
                    MonitorDataSet(ch, 1);
                }
                break;
            case DEF_MONITOR_EXT_SWITCH_1:   // (DEF_MONITOR_CHANNEL_6)
                hw_channel = DEF_SWITCH_CHANNEL_1;
                if(MonitorReadCount(ch) > MonitorReadCountMax(ch))
                {
                    MonitorDataSet(ch, 1);
                }
                break;
            case DEF_MONITOR_HPA_SHUTDOWN_0: // (DEF_MONITOR_CHANNEL_7)
                hw_channel = DEF_SHUTDOWN_CHANNEL_0;
                if(MonitorReadCount(ch) > MonitorReadCountMax(ch))
                {
                    MonitorDataSet(ch, 1);
                }
                break;
            case DEF_MONITOR_EXT_SHUTDOWN_0: // (DEF_MONITOR_CHANNEL_8)
                hw_channel = DEF_EXT_SHUTDOWN_CHANNEL_0;
                if(MonitorReadCount(ch) > MonitorReadCountMax(ch))
                {
                    MonitorDataSet(ch, 1);
                    if(MonitorReadData(ch) == 1)
                    {
                        ShutdownOn(hw_channel);
                    }
                }
                break;
            default:
                break;
        }
    }
}

