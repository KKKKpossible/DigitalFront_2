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

#define RESET_Pin       GPIO_PIN_13
#define RESET_GPIO_Port GPIOB
#define D_C_Pin         GPIO_PIN_14
#define D_C_GPIO_Port   GPIOB
#define CS_Pin          GPIO_PIN_15
#define CS_GPIO_Port    GPIOB


typedef struct Gpio_t
{
    GPIO_TypeDef* port;
    uint16_t      pin;
    GPIO_PinState set;
    GPIO_PinState reset;
}Gpio_t;

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
