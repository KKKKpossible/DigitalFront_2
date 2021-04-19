/*
 * dma.c
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */


#include "sjk_dma.h"


bool DmaInit(void)
{
        bool ret = true;

        /* DMA controller clock enable */
        __HAL_RCC_DMA1_CLK_ENABLE();

        /* DMA interrupt init */
        /* DMA1_Channel1_IRQn interrupt configuration */
        HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

        return ret;
}
