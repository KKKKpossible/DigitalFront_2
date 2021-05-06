/*
 * sjk_led.c
 *
 *  Created on: 2021. 4. 16.
 *      Author: sungjinkim
 */


#include "sjk_led.h"


extern Gpio_t  gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_MAX];


bool LedInit(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_LED_CHANNEL_0:
            gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_3].set   = GPIO_PIN_RESET;
            gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_3].reset = GPIO_PIN_SET;
            break;
        case DEF_LED_CHANNEL_1:
            gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_1].set   = GPIO_PIN_SET;
            gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_1].reset = GPIO_PIN_RESET;
            break;
        default:
            break;
    }

    return ret;
}

bool LedOn(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_LED_CHANNEL_0:
            GpioOn(DEF_GPIO_OUTPUT_CHANNEL_3);
            break;
        case DEF_LED_CHANNEL_1:
            GpioOn(DEF_GPIO_OUTPUT_CHANNEL_1);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool LedOff(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_LED_CHANNEL_0:
            GpioOff(DEF_GPIO_OUTPUT_CHANNEL_3);
            break;
        case DEF_LED_CHANNEL_1:
            GpioOff(DEF_GPIO_OUTPUT_CHANNEL_1);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool LedToggle(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_LED_CHANNEL_0:
            GpioToggle(DEF_GPIO_OUTPUT_CHANNEL_3);
            break;
        case DEF_LED_CHANNEL_1:
            GpioToggle(DEF_GPIO_OUTPUT_CHANNEL_1);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

ReadState LedRead(uint8_t ch)
{
    ReadState ret = RS_ERROR;

    switch(ch)
    {
        case DEF_LED_CHANNEL_0:
            ret = GpioOutputRead(DEF_GPIO_OUTPUT_CHANNEL_3);
            break;
        case DEF_LED_CHANNEL_1:
            ret = GpioOutputRead(DEF_GPIO_OUTPUT_CHANNEL_1);
            break;
        default:
            ret = RS_ERROR;
            break;
    }

    return ret;
}
