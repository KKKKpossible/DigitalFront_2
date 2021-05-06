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
    int64_t data;
    int64_t offset;
    int64_t ratio_per;
    int64_t ratio_val;
    int     count;
    int64_t count_max;
    int64_t limit;
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
                monitor_arr[ch].offset       = 0;
                monitor_arr[ch].ratio_per    = 4095;
                monitor_arr[ch].ratio_val    = 3300;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                monitor_arr[ch].limit        = 3300;
                break;
            case DEF_MONITOR_TEMP_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 0;
                monitor_arr[ch].ratio_per    = 4095;
                monitor_arr[ch].ratio_val    = 3300;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                monitor_arr[ch].limit        = 3300;
                break;
            case DEF_MONITOR_HTEMP_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1430 / 4.3 + 2500;
                monitor_arr[ch].ratio_per    = -43 * 4095;
                monitor_arr[ch].ratio_val    = 10 * 3300;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                monitor_arr[ch].limit        = 3300;
                break;
            case DEF_MONITOR_EXT_ATTEN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 0;
                monitor_arr[ch].ratio_per    = 4095;
                monitor_arr[ch].ratio_val    = 3300;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                monitor_arr[ch].limit        = 3300;
                break;
            case DEF_MONITOR_INT_ATTEN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 0;
                monitor_arr[ch].ratio_per    = 4095;
                monitor_arr[ch].ratio_val    = 3300;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                monitor_arr[ch].limit        = 3300;
                break;
            case DEF_MONITOR_EXT_SWITCH_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 0;
                monitor_arr[ch].ratio_per    = 1;
                monitor_arr[ch].ratio_val    = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                monitor_arr[ch].limit        = 3300;
                break;
            case DEF_MONITOR_EXT_SWITCH_1:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 0;
                monitor_arr[ch].ratio_per    = 1;
                monitor_arr[ch].ratio_val    = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                monitor_arr[ch].limit        = 3300;
                break;
            case DEF_MONITOR_HPA_SHUTDOWN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 0;
                monitor_arr[ch].ratio_per    = 1;
                monitor_arr[ch].ratio_val    = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                monitor_arr[ch].limit        = 3300;
                break;
            case DEF_MONITOR_EXT_SHUTDOWN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 0;
                monitor_arr[ch].ratio_per    = 1;
                monitor_arr[ch].ratio_val    = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 100;
                monitor_arr[ch].limit        = 3300;
                break;
            case DEF_MONITOR_FAULT_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 0;
                monitor_arr[ch].ratio_per    = 1;
                monitor_arr[ch].ratio_val    = 1;
                monitor_arr[ch].count        = 0;
                monitor_arr[ch].count_max    = 0;
                monitor_arr[ch].limit        = 3300;
                break;
        }
    }

    return ret;
}

int64_t MonitorRead(uint8_t ch)
{
    int64_t ret =
            monitor_arr[ch].offset
            + (monitor_arr[ch].data * monitor_arr[ch].ratio_val
            / monitor_arr[ch].ratio_per);
    return ret;
}

int64_t MonitorReadData(uint8_t ch)
{
    return monitor_arr[ch].data;
}

int MonitorReadCount(uint8_t ch)
{
    return monitor_arr[ch].count;
}

int64_t MonitorReadCountMax(uint8_t ch)
{
    return monitor_arr[ch].count_max;
}

int64_t MonitorReadLimit(uint8_t ch)
{
    return monitor_arr[ch].limit;
}

void MonitorDataSet(uint8_t ch, int64_t data)
{
    monitor_arr[ch].data = data;
}

void MonitorDataAddOr(uint8_t ch, int64_t data)
{
    monitor_arr[ch].data |= data;
}

void MonitorDataDelAnd(uint8_t ch, int64_t data)
{
    monitor_arr[ch].data &= ~(data);
}

void MonitorOffsetSet(uint8_t ch, int64_t offset)
{
    monitor_arr[ch].offset = offset;
}

void MonitorRatioPerSet(uint8_t ch, int64_t ratio_per)
{
    monitor_arr[ch].ratio_per = ratio_per;
}

void MonitorRatioValSet(uint8_t ch, int64_t ratio_val)
{
    monitor_arr[ch].ratio_val = ratio_val;
}

void MonitorCountAdd(uint8_t ch, int64_t data)
{
    monitor_arr[ch].count += data;
}

void MonitorLimitSet(uint8_t ch, int64_t limit)
{
    monitor_arr[ch].limit = limit;
}
