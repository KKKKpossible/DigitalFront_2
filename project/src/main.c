/*
 * main.c
 *
 *  Created on: 2021. 4. 14.
 *      Author: sungjinkim
 */


#include "main.h"


extern UART_HandleTypeDef huart1;


int main(void)
{
    HwInit();
    ApInit();

    uint32_t tick = 0;

    while(true)
    {
        ApMain();

        if(millis() - tick > 100)
        {
            tick = millis();
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
            HAL_UART_Transmit(&huart1, (uint8_t*)"1", 1, 10);
        }
    }

    return 0;
}
