/*
 * sjk_ext_shutdown.c
 *
 *  Created on: 2021. 5. 4.
 *      Author: sungjinkim
 */


#include "sjk_shutdown.h"


extern Gpio_t  gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_MAX];
extern Gpio_t  gpio_input_arr [DEF_GPIO_INPUT_CHANNEL_MAX];


bool ExtShutdonInit(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_EXT_SHUTDOWN_CHANNEL_0:
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_2].port  = GPIOB;
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_2].pin   = GPIO_PIN_8;
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_2].set   = GPIO_PIN_SET;
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_2].reset = GPIO_PIN_RESET;
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

ReadState ExtShutdonRead(uint8_t ch)
{
    ReadState ret = RS_ERROR;

    switch(ch)
    {
        case DEF_EXT_SHUTDOWN_CHANNEL_0:
            ret = GpioInputRead(DEF_GPIO_INPUT_CHANNEL_2);
            break;
        default:
            break;
    }

    return ret;
}

bool ShutdownInit(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_SHUTDOWN_CHANNEL_0:
            gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_0].port  = GPIOB;
            gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_0].pin   = GPIO_PIN_5;
            gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_0].set   = GPIO_PIN_SET;
            gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_0].reset = GPIO_PIN_RESET;

            GpioOff(DEF_GPIO_OUTPUT_CHANNEL_0);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool ShutdownOn(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_SHUTDOWN_CHANNEL_0:
            GpioOn(DEF_GPIO_OUTPUT_CHANNEL_0);
            break;
        default:
            break;
    }

    return ret;
}

bool ShutdownOff(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_SHUTDOWN_CHANNEL_0:
            GpioOff(DEF_GPIO_OUTPUT_CHANNEL_0);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool ShutdownToggle(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_SHUTDOWN_CHANNEL_0:
            GpioToggle(DEF_GPIO_OUTPUT_CHANNEL_0);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

ReadState ShutdownRead(uint8_t ch)
{
    ReadState ret = RS_ERROR;

    switch(ch)
    {
        case DEF_EXT_SHUTDOWN_CHANNEL_0:
            ret = GpioOutputRead(DEF_GPIO_OUTPUT_CHANNEL_0);
            break;
        default:
            ret = RS_ERROR;
            break;
    }

    return ret;
}
