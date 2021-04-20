/*
 * gpio.c
 *
 *  Created on: 2021. 4. 13.
 *      Author: sungjinkim
 */


#include "sjk_gpio.h"


Gpio_out_t   gpio_output_arr[DEF_GPIO_OUTPUT_CHANNEL_MAX];
Gpio_input_t gpio_input_arr [DEF_GPIO_INPUT_CHANNEL_MAX];


static bool GpioArrInit (void);
static bool _GpioInit   (void);


bool GpioInit(void)
{
	bool ret = true;

	GpioArrInit ();
	_GpioInit   ();

	return ret;
}

bool GpioOn(uint8_t ch)
{
    bool ret = true;
    switch(ch)
    {
        case DEF_GPIO_OUTPUT_CHANNEL_0:
        case DEF_GPIO_OUTPUT_CHANNEL_1:
        case DEF_GPIO_OUTPUT_CHANNEL_2:
        case DEF_GPIO_OUTPUT_CHANNEL_3:
            HAL_GPIO_WritePin(gpio_output_arr[ch].port, gpio_output_arr[ch].pin, gpio_output_arr[ch].set);
            break;
        default:
            ret = false;
            break;
    }
    return ret;
}

bool GpioOff(uint8_t ch)
{
    bool ret = true;
    switch(ch)
    {
        case DEF_GPIO_OUTPUT_CHANNEL_0:
        case DEF_GPIO_OUTPUT_CHANNEL_1:
        case DEF_GPIO_OUTPUT_CHANNEL_2:
        case DEF_GPIO_OUTPUT_CHANNEL_3:
            HAL_GPIO_WritePin(gpio_output_arr[ch].port, gpio_output_arr[ch].pin, gpio_output_arr[ch].reset);
            break;
        default:
            ret = false;
            break;
    }
    return ret;
}

bool GpioToggle(uint8_t ch)
{
    bool ret = true;
    switch(ch)
    {
        case DEF_GPIO_OUTPUT_CHANNEL_0:
        case DEF_GPIO_OUTPUT_CHANNEL_1:
        case DEF_GPIO_OUTPUT_CHANNEL_2:
        case DEF_GPIO_OUTPUT_CHANNEL_3:
            HAL_GPIO_TogglePin(gpio_output_arr[ch].port, gpio_output_arr[ch].pin);
            break;
        default:
            ret = false;
            break;
    }
    return ret;
}

ReadState GpioOutputRead(uint8_t ch)
{
    ReadState ret = RS_GPIO_PIN_RESET;
    GPIO_PinState state = GPIO_PIN_RESET;

    switch(ch)
    {
      case DEF_GPIO_OUTPUT_CHANNEL_0:
      case DEF_GPIO_OUTPUT_CHANNEL_1:
      case DEF_GPIO_OUTPUT_CHANNEL_2:
      case DEF_GPIO_OUTPUT_CHANNEL_3:
          state = HAL_GPIO_ReadPin(gpio_output_arr[ch].port, gpio_output_arr[ch].pin);
          if(state == GPIO_PIN_RESET)
          {
              ret = RS_GPIO_PIN_SET;
          }
          break;
      default:
          ret = RS_ERROR;
    }

    return ret;
}

ReadState GpioInputRead(uint8_t ch)
{
    ReadState     ret   = RS_GPIO_PIN_RESET;
    GPIO_PinState state = GPIO_PIN_RESET;

    switch(ch)
    {
        case DEF_GPIO_INPUT_CHANNEL_0:
        case DEF_GPIO_INPUT_CHANNEL_1:
        case DEF_GPIO_INPUT_CHANNEL_2:
            state = HAL_GPIO_ReadPin(gpio_input_arr[ch].port, gpio_input_arr[ch].pin);
            if(state == GPIO_PIN_SET)
            {
                ret = RS_GPIO_PIN_SET;
            }
            break;
        default:
            ret = RS_ERROR;
    }

    return ret;
}


static bool GpioArrInit(void)
{
    bool ret = true;
    for(int i = 0; i < DEF_GPIO_OUTPUT_CHANNEL_MAX; i++)
    {
        switch(i)
        {
            case DEF_GPIO_OUTPUT_CHANNEL_0:
                gpio_output_arr[i].port  = GPIOB;
                gpio_output_arr[i].pin   = GPIO_PIN_5;
                gpio_output_arr[i].set   = GPIO_PIN_SET;
                gpio_output_arr[i].reset = GPIO_PIN_RESET;
                break;
            case DEF_GPIO_OUTPUT_CHANNEL_1:
                gpio_output_arr[i].port  = GPIOB;
                gpio_output_arr[i].pin   = GPIO_PIN_9;
                gpio_output_arr[i].set   = GPIO_PIN_SET;
                gpio_output_arr[i].reset = GPIO_PIN_RESET;
                break;
            case DEF_GPIO_OUTPUT_CHANNEL_2:
                gpio_output_arr[i].port  = GPIOB;
                gpio_output_arr[i].pin   = GPIO_PIN_11;
                gpio_output_arr[i].set   = GPIO_PIN_SET;
                gpio_output_arr[i].reset = GPIO_PIN_RESET;
                break;
            case DEF_GPIO_OUTPUT_CHANNEL_3:
                gpio_output_arr[i].port  = GPIOB;
                gpio_output_arr[i].pin   = GPIO_PIN_12;
                gpio_output_arr[i].set   = GPIO_PIN_SET;
                gpio_output_arr[i].reset = GPIO_PIN_RESET;
                break;
            default:
                ret = false;
                return ret;
                break;
        }
    }

    for(int i = 0; i < DEF_GPIO_INPUT_CHANNEL_MAX; i++)
    {
        switch(i)
        {
            case DEF_GPIO_INPUT_CHANNEL_0:
                gpio_input_arr[i].port = GPIOB;
                gpio_input_arr[i].pin  = GPIO_PIN_3;
                break;
            case DEF_GPIO_INPUT_CHANNEL_1:
                gpio_input_arr[i].port = GPIOB;
                gpio_input_arr[i].pin  = GPIO_PIN_4;
                break;
            case DEF_GPIO_INPUT_CHANNEL_2:
                gpio_input_arr[i].port = GPIOB;
                gpio_input_arr[i].pin  = GPIO_PIN_8;
                break;
            default:
                ret = false;
                return ret;
                break;
        }
    }

    return ret;
}

static bool _GpioInit(void)
{
    bool ret = true;

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_5|GPIO_PIN_9, GPIO_PIN_RESET);

    /*Configure GPIO pin : PB11 */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : PB12 PB5 PB9 */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_5|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : PB3 PB4 PB8 */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    return ret;
}
