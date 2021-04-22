/*
 * sjk_monitor.c
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */


#include "sjk_monitor.h"
#include "sjk_vva.h"


typedef struct Monitor_t
{
    uint32_t     data;
    uint32_t     offset;
    uint32_t     ratio;
    uint32_t     record_count;
}Monitor_t;


static Monitor_t monitor_arr[DEF_MONITOR_CHANNEL_MAX] =
        {

        };


static bool     MonitorReadBool   (uint8_t ch);
static bool     MonitorWriteBool  (uint8_t ch, uint32_t data);
static uint32_t MonitorReadUint32 (uint8_t ch);


bool MonitorInit()
{
    bool ret = true;

    for(int ch; ch < DEF_MONITOR_CHANNEL_MAX; ch++)
    {
        switch(ch)
        {
            case DEF_MONITOR_CURR_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].record_count = 10;
                break;
            case DEF_MONITOR_TEMP_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].record_count = 10;
                break;
            case DEF_MONITOR_HTEMP_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].record_count = 10;
                break;
            case DEF_MONITOR_EXT_ATTEN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].record_count = 10;
                break;
            case DEF_MONITOR_INT_ATTEN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].record_count = 10;
                break;
            case DEF_MONITOR_EXT_SWITCH_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].record_count = 10;
                break;
            case DEF_MONITOR_EXT_SWITCH_1:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].record_count = 10;
                break;
            case DEF_MONITOR_HPA_SHUTDOWN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].record_count = 10;
                break;
            case DEF_MONITOR_EXT_SHUTDOWN_0:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].record_count = 10;
                break;
            case DEF_MONITOR_FAULT:
                monitor_arr[ch].data         = 0;
                monitor_arr[ch].offset       = 1;
                monitor_arr[ch].ratio        = 1;
                monitor_arr[ch].record_count = 10;
                break;
        }
    }

    return ret;
}

bool MonitorRead(uint8_t ch, uint32_t* retbuff)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_MONITOR_CURR_0:
            *retbuff = MonitorReadUint32(ch);
            break;
        case DEF_MONITOR_TEMP_0:
            *retbuff = MonitorReadUint32(ch);
            break;
        case DEF_MONITOR_HTEMP_0:
            *retbuff = MonitorReadUint32(ch);
            break;
        case DEF_MONITOR_EXT_ATTEN_0:
            *retbuff = MonitorReadUint32(ch);
            break;
        case DEF_MONITOR_INT_ATTEN_0:
            break;
        case DEF_MONITOR_EXT_SWITCH_0:
            *retbuff = MonitorReadBool(ch);
            break;
        case DEF_MONITOR_EXT_SWITCH_1:
            *retbuff = MonitorReadBool(ch);
            break;
        case DEF_MONITOR_HPA_SHUTDOWN_0:
            *retbuff = MonitorReadBool(ch);
            break;
        case DEF_MONITOR_EXT_SHUTDOWN_0:
            *retbuff = MonitorReadBool(ch);
            break;
        case DEF_MONITOR_FAULT:
            *retbuff = MonitorReadBool(ch);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool MonitorWrite(uint8_t ch, uint32_t data)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_MONITOR_CURR_0:
            ret = false;
            break;
        case DEF_MONITOR_TEMP_0:
            ret = false;
            break;
        case DEF_MONITOR_HTEMP_0:
            ret = false;
            break;
        case DEF_MONITOR_EXT_ATTEN_0:
            ret = false;
            break;
        case DEF_MONITOR_INT_ATTEN_0:
            break;
        case DEF_MONITOR_EXT_SWITCH_0:
            ret = false;
            break;
        case DEF_MONITOR_EXT_SWITCH_1:
            ret = false;
            break;
        case DEF_MONITOR_HPA_SHUTDOWN_0:
            ret = MonitorWriteBool(ch, data);
            break;
        case DEF_MONITOR_EXT_SHUTDOWN_0:
            ret = false;
            break;
        case DEF_MONITOR_FAULT:
            ret = MonitorWriteBool(ch, data);
            break;
    }
    return ret;
}

static bool MonitorReadBool(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {

    }

    return ret;
}

static bool MonitorWriteBool(uint8_t ch, uint32_t data)
{
    bool ret = true;

    switch(ch)
    {
        default:
            ret = false;
            break;
    }

    return ret;
}

static uint32_t MonitorReadUint32(uint8_t ch)
{
    uint32_t ret = true;

    switch(ch)
    {

    }

    return ret;
}

