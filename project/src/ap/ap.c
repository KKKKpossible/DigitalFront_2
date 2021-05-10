/*
 * ap.c
 *
 *  Created on: Apr 13, 2021
 *      Author: sungjinkim
 */


#include "ap.h"


extern Parse_t parse_var;

uint64_t global_fault;

static bool ext_atten_load = false;


static void ApParsing                     (void);
static void ApMonitor                     (void);
static void ApAdcRead                     (uint8_t hw_channel_read, uint8_t monitor_ch);
static void ApReadHwWriteOnMonitor        (void);
static void ApReadFaultWriteHwWithMonitor (void);
static void ApBlink                       (void);


bool ApInit(void)
{
	bool ret = true;

	return ret;
}

bool ApMain(void)
{
	bool   ret           = true;
    static uint32_t tick = 0;

    ApParsing();

	if(millis() - tick > 1)
    {
	    tick = millis();

	    ApMonitor();

	    ApBlink();
    }

	return ret;
}

static void ApBlink(void)
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

static void ApParsing(void)
{
    int uart_rxlength = UartRxAvailable(DEF_UART_CHANNEL_0);

    if(uart_rxlength != 0)
    {
        uint8_t data = UartReadRxBuffer(DEF_UART_CHANNEL_0);
        Parse(DEF_UART_CHANNEL_0, data);
    }
}

static void ApMonitor(void)
{
    ApReadHwWriteOnMonitor();
    ApReadFaultWriteHwWithMonitor();
}

static void FaultReset(uint8_t monitor_ch)
{
    switch(monitor_ch)
    {
        case DEF_ADC_CURRENT_0:
            MonitorDataDelAnd(DEF_MONITOR_FAULT_0, (1 << DEF_FAULT_CURRENT_0));
            break;
        case DEF_ADC_TEMP_0:
            MonitorDataDelAnd(DEF_MONITOR_FAULT_0, (1 << DEF_FAULT_TEMPERATURE_0));
            break;
        case DEF_ADC_EXT_ATTEN_0:
            break;
        case DEF_ADC_HS_TEMP_0:
            MonitorDataDelAnd(DEF_MONITOR_FAULT_0, (1 << DEF_FAULT_HS_TEMPERATURE_0));
            break;
        default:
            return;
    }
}

static void FaultSet(uint8_t monitor_ch)
{
    switch(monitor_ch)
    {
        case DEF_ADC_CURRENT_0:
            MonitorDataAddOr(DEF_MONITOR_FAULT_0, (1 << DEF_FAULT_CURRENT_0));
            break;
        case DEF_ADC_TEMP_0:
            MonitorDataAddOr(DEF_MONITOR_FAULT_0, (1 << DEF_FAULT_TEMPERATURE_0));
            break;
        case DEF_ADC_EXT_ATTEN_0:
            break;
        case DEF_ADC_HS_TEMP_0:
            MonitorDataAddOr(DEF_MONITOR_FAULT_0, (1 << DEF_FAULT_HS_TEMPERATURE_0));
            break;
        default:
            break;
    }
}

static void ApAdcRead(uint8_t hw_channel_read, uint8_t monitor_ch)
{
    if(MonitorReadCount(monitor_ch) < MonitorReadCountMax(monitor_ch))
    {
        MonitorCountAdd (monitor_ch, 1);
        AdcSumBuffAdd   (hw_channel_read, AdcBufferRead(hw_channel_read));
    }
    else
    {
        uint32_t adc_sum = AdcSumBuffRead(hw_channel_read) / MonitorReadCountMax(monitor_ch);
        MonitorDataSet  (monitor_ch     , adc_sum);
        MonitorCountAdd (monitor_ch     , -(MonitorReadCountMax(monitor_ch)));
        AdcSumBuffAdd   (hw_channel_read, -(AdcSumBuffRead(hw_channel_read)));

        switch(hw_channel_read)
        {
            case DEF_ADC_EXT_ATTEN_0:
                ext_atten_load = true;
                break;
            default:
                break;
        }

        if(MonitorRead(monitor_ch) > MonitorReadLimit(monitor_ch))
        {
            FaultSet(monitor_ch);
        }
        else
        {
            FaultReset(monitor_ch);
        }
    }
}

static void ApReadHwWriteOnMonitor(void)
{
    uint32_t hw_channel_read;

    for(uint8_t monitor_ch = DEF_MONITOR_CHANNEL_0; monitor_ch < DEF_MONITOR_CHANNEL_MAX; monitor_ch++)
    {
        switch(monitor_ch)
        {
            case DEF_MONITOR_CURR_0:         // (DEF_MONITOR_CHANNEL_0)
                hw_channel_read = DEF_ADC_CURRENT_0;
                ApAdcRead(hw_channel_read, monitor_ch);
                break;
            case DEF_MONITOR_TEMP_0:         // (DEF_MONITOR_CHANNEL_1)
                hw_channel_read = DEF_ADC_TEMP_0;
                ApAdcRead(hw_channel_read, monitor_ch);
                break;
            case DEF_MONITOR_HTEMP_0:        // (DEF_MONITOR_CHANNEL_2)
                hw_channel_read = DEF_ADC_HS_TEMP_0;
                ApAdcRead(hw_channel_read, monitor_ch);
                break;
            case DEF_MONITOR_EXT_ATTEN_0:    // (DEF_MONITOR_CHANNEL_3)
                hw_channel_read = DEF_ADC_EXT_ATTEN_0;
                ApAdcRead(hw_channel_read, monitor_ch);
                break;
            case DEF_MONITOR_INT_ATTEN_0:    // (DEF_MONITOR_CHANNEL_4)
                if(ext_atten_load == true)
                {
                    MonitorDataSet(monitor_ch, MonitorReadData(DEF_MONITOR_EXT_ATTEN_0));
                }
                break;
            case DEF_MONITOR_EXT_SWITCH_0:   // (DEF_MONITOR_CHANNEL_5)
                hw_channel_read = DEF_SWITCH_CHANNEL_0;
                if(SwitchRead(hw_channel_read) == RS_GPIO_PIN_SET)
                {
                    if(MonitorReadCount(monitor_ch) > MonitorReadCountMax(monitor_ch))
                    {
                        MonitorDataSet(monitor_ch, 1);
                    }
                    else
                    {
                        MonitorCountAdd(monitor_ch, 1);
                    }
                }
                else
                {
                    if(MonitorReadCount(monitor_ch) != 0)
                    {
                        MonitorCountAdd(monitor_ch, -1);
                    }
                }
                break;
            case DEF_MONITOR_EXT_SWITCH_1:   // (DEF_MONITOR_CHANNEL_6)
                hw_channel_read = DEF_SWITCH_CHANNEL_1;
                if(SwitchRead(hw_channel_read) == RS_GPIO_PIN_SET)
                {
                    if(MonitorReadCount(monitor_ch) > MonitorReadCountMax(monitor_ch))
                    {
                        MonitorDataSet(monitor_ch, 1);
                    }
                    else
                    {
                        MonitorCountAdd(monitor_ch, 1);
                    }
                }
                else
                {
                    if(MonitorReadCount(monitor_ch) != 0)
                    {
                        MonitorCountAdd(monitor_ch, -1);
                    }
                }
                break;
            case DEF_MONITOR_HPA_SHUTDOWN_0: // (DEF_MONITOR_CHANNEL_7)
                break;
            case DEF_MONITOR_EXT_SHUTDOWN_0: // (DEF_MONITOR_CHANNEL_8)
                hw_channel_read = DEF_EXT_SHUTDOWN_CHANNEL_0;
                if(ExtShutdonRead(hw_channel_read) == RS_GPIO_PIN_SET)
                {
                    if(MonitorReadCount(monitor_ch) > MonitorReadCountMax(monitor_ch))
                    {
                        MonitorDataSet(monitor_ch, 1);
                    }
                    else
                    {
                        MonitorCountAdd(monitor_ch, 1);
                    }
                }
                else
                {
                    if(MonitorReadCount(monitor_ch) != 0)
                    {
                        MonitorCountAdd(monitor_ch, -1);
                    }
                }
                break;
            case DEF_MONITOR_FAULT_0:        // (DEF_MONITOR_CHANNEL_9)
                break;
            default:
                break;
        }
    }
}
static void ApReadFaultWriteHwWithMonitor(void)
{
    uint32_t hw_channel;

    for(int monitor_ch = DEF_MONITOR_CHANNEL_0; monitor_ch < DEF_MONITOR_CHANNEL_MAX; monitor_ch++)
    {
        switch(monitor_ch)
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
                if(ext_atten_load == true)
                {
                    ext_atten_load = false;
                    uint16_t voltage = MonitorRead(DEF_MONITOR_EXT_ATTEN_0);
                    VvaSendMiliVolt(DEF_VVA_CHANNEL_0, voltage);
                }
                break;
            case DEF_MONITOR_EXT_SWITCH_0:   // (DEF_MONITOR_CHANNEL_5)
                break;
            case DEF_MONITOR_EXT_SWITCH_1:   // (DEF_MONITOR_CHANNEL_6)
                break;
            case DEF_MONITOR_HPA_SHUTDOWN_0: // (DEF_MONITOR_CHANNEL_7)
                hw_channel = DEF_SHUTDOWN_CHANNEL_0;
                if(MonitorRead(DEF_MONITOR_FAULT_0) != 0)
                {
                    MonitorDataSet(monitor_ch, 1);
                    ShutdownOn(hw_channel);
                }
                else
                {
                    if(MonitorRead(monitor_ch) == 1)
                    {
                        ShutdownOn(hw_channel);
                    }
                    else if(MonitorRead(monitor_ch) == 0)
                    {
                        ShutdownOff(hw_channel);
                    }
                }
                break;
            case DEF_MONITOR_EXT_SHUTDOWN_0: // (DEF_MONITOR_CHANNEL_8)
                break;
            case DEF_MONITOR_FAULT_0:        // (DEF_MONITOR_CHANNEL_9)
                if(MonitorRead(DEF_MONITOR_FAULT_0) != 0)
                {
                    LedOn(DEF_LED_CHANNEL_1);
                }
                else
                {
                    LedOff(DEF_LED_CHANNEL_1);
                }
                break;
            default:
                break;
        }
    }
}
