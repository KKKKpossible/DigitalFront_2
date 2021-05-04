/*
 * sjk_monitor.c
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */


#include "sjk_monitor.h"
#include "hw.h"


typedef struct Monitor_t
{
    uint32_t data;
    uint32_t offset;
    uint32_t ratio;
    int      count;
    uint32_t count_max;
}Monitor_t;


static Monitor_t monitor_arr[DEF_MONITOR_CHANNEL_MAX];


bool MonitorInit()
{
    bool ret = true;

    for(int ch = DEF_MONITOR_CHANNEL_0; ch < DEF_MONITOR_CHANNEL_MAX; ch++)
    {
        switch(ch)
        {
            case DEF_MONITOR_CURR_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                break;
            case DEF_MONITOR_TEMP_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                break;
            case DEF_MONITOR_HTEMP_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                break;
            case DEF_MONITOR_EXT_ATTEN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                break;
            case DEF_MONITOR_INT_ATTEN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                break;
            case DEF_MONITOR_EXT_SWITCH_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;

                break;
            case DEF_MONITOR_EXT_SWITCH_1:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                break;
            case DEF_MONITOR_HPA_SHUTDOWN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                break;
            case DEF_MONITOR_EXT_SHUTDOWN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                break;
        }
    }

    return ret;
}

uint32_t MonitorReadData(uint8_t ch)
{
    return monitor_arr[ch].data * monitor_arr[ch].offset * monitor_arr[ch].ratio;
}

int MonitorReadCount (uint8_t ch)
{
    return monitor_arr[ch].count;
}

uint32_t MonitorReadCountMax (uint8_t ch)
{
    return monitor_arr[ch].count_max;
}

void MonitorDataSet(uint8_t ch, uint32_t data)
{
    monitor_arr[ch].data = data;
}

void MonitorOffsetSet(uint8_t ch, uint32_t offset)
{
    monitor_arr[ch].offset = offset;
}

void MonitorRatioSet(uint8_t ch, uint32_t ratio)
{
    monitor_arr[ch].ratio = ratio;
}

void MonitorCountAdd(uint8_t ch, int data)
{
    monitor_arr[ch].count += data;
}
