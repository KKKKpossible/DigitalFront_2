/*
 * gpio.h
 *
 *  Created on: 2021. 4. 13.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_GPIO_H_
#define SRC_COMMON_HW_INC_SJK_GPIO_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"


#ifdef  HW_GPIO_USE
#define DEF_GPIO_OUTPUT_CHANNEL_MAX HW_GPIO_OUTPUT_CHANNEL_MAX
#define DEF_GPIO_INPUT_CHANNEL_MAX  HW_GPIO_INPUT_CHANNEL_MAX


typedef struct Gpio_out_t
{
    GPIO_TypeDef* port;
    uint16_t      pin;
    GPIO_PinState set;
    GPIO_PinState reset;
}Gpio_out_t;

typedef struct Gpio_input_t
{
    GPIO_TypeDef* port;
    uint16_t      pin;
}Gpio_input_t;

typedef enum ReadState
{
    RS_ERROR          = (-1U),
    RS_GPIO_PIN_RESET = ( 0U),
    RS_GPIO_PIN_SET   = ( 1U)
}ReadState;


bool      GpioInit       (void);
bool      GpioOn         (uint8_t ch);
bool      GpioOff        (uint8_t ch);
bool      GpioToggle     (uint8_t ch);
ReadState GpioOutputRead (uint8_t ch);
ReadState GpioInputRead  (uint8_t ch);


#endif

#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_GPIO_H_ */
