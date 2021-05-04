/*
 * sjk_switch.c
 *
 *  Created on: 2021. 5. 4.
 *      Author: sungjinkim
 */


#include "sjk_switch.h"


extern Gpio_t  gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_MAX];
extern Gpio_t  gpio_input_arr [DEF_GPIO_INPUT_CHANNEL_MAX];


bool SwitchInit(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_SWITCH_CHANNEL_0:
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_0].port  = GPIOB;
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_0].pin   = GPIO_PIN_3;
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_0].set   = GPIO_PIN_SET;
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_0].reset = GPIO_PIN_RESET;
            break;
        case DEF_SWITCH_CHANNEL_1:
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_0].port  = GPIOB;
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_0].pin   = GPIO_PIN_4;
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_0].set   = GPIO_PIN_SET;
            gpio_input_arr[DEF_GPIO_INPUT_CHANNEL_0].reset = GPIO_PIN_RESET;
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

ReadState SwitchRead(uint8_t ch)
{
    ReadState ret = RS_ERROR;

    switch(ch)
    {
        case DEF_SWITCH_CHANNEL_0:
            ret = GpioInputRead(DEF_GPIO_INPUT_CHANNEL_0);
            break;
        case DEF_SWITCH_CHANNEL_1:
            ret = GpioInputRead(DEF_GPIO_INPUT_CHANNEL_0);
            break;
        default:
            break;
    }

    return ret;
}
