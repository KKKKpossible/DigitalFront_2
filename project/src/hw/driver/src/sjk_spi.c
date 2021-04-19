/*
 * sjk_spi.c
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */


#include "sjk_spi.h"

bool SpiInit(void)
{
    bool ret = true;

    for(int ch = 0; ch < DEF_SPI_CHANNEL_MAX; ch++)
    {
        switch(ch)
        {
            case DEF_SPI_CHANNEL_0:
                break;
            default:
                ret = false;
                break;
        }
    }

    return ret;
}

bool SpiWrite(uint8_t ch, uint16_t* data)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_SPI_CHANNEL_0:
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool SpiRead(uint8_t ch, uint16_t* buffer)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_SPI_CHANNEL_0:
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}
