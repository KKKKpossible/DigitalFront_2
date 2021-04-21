/*
 * sjk_flash.c
 *
 *  Created on: 2021. 4. 21.
 *      Author: sungjinkim
 */


#include "sjk_flash.h"


#define FLASH_SECTOR_MAX (64U)


typedef struct
{
    uint32_t addr;
    uint16_t length;
}Flashtbl_t;


static Flashtbl_t flash_tble[FLASH_SECTOR_MAX];


static bool FlashInSector(uint16_t sector_number, uint32_t addr, uint32_t length);


bool FlashInit(void)
{
    bool ret = true;

    for(int i = 0 ; i < FLASH_SECTOR_MAX; i++)
    {
        flash_tble[i].addr   = 0x8000000 + i * 1024;
        flash_tble[i].length = 1024;
    }

    return ret;
}

static bool FlashInSector(uint16_t sector_number, uint32_t addr, uint32_t length)
{
    bool ret = false;

    uint32_t sector_start;
    uint32_t sector_end;
    uint32_t flash_start;
    uint32_t flash_end;

    sector_start = flash_tble[sector_number].addr;
    sector_end   = flash_tble[sector_number].addr + flash_tble[sector_number].length - 1;
    flash_start  = addr;
    flash_end    = addr + length - 1;

    if((sector_start >= flash_start) && (sector_start <= flash_end))
    {
        ret = true;
    }

    if((sector_end >= flash_start) && (sector_end <= flash_end))
    {
        ret = true;
    }

    if((flash_start >= sector_start) && (flash_start <= sector_end))
    {
        ret = true;
    }

    if((flash_end >= sector_start) && (flash_end <= sector_end))
    {
        ret = true;
    }

    return ret;
}

bool FlashErase(uint32_t addr, uint32_t length)
{
    bool ret = false;

    FLASH_EraseInitTypeDef init;
    HAL_StatusTypeDef      status = HAL_ERROR;
    uint32_t               page_error;

    int16_t  start_sector_number = -1;
    uint32_t sector_count = 0;

    for(int i = 0; i < FLASH_SECTOR_MAX; i++)
    {
        if(FlashInSector(i, addr, length) == true)
        {
            if(start_sector_number < 0)
            {
                start_sector_number = i;
            }
            sector_count++;
        }
    }

    if(sector_count > 0)
    {
        HAL_FLASH_Unlock();

        init.TypeErase   = FLASH_TYPEERASE_PAGES;
        init.Banks       = FLASH_BANK_1;
        init.PageAddress = flash_tble[start_sector_number].addr;
        init.NbPages     = sector_count;
        status           = HAL_FLASHEx_Erase(&init, &page_error);

        HAL_FLASH_Lock();
    }

    if(status == HAL_OK)
    {
        ret = true;
    }

    return ret;
}

bool FlashWrite(uint32_t addr, uint8_t* p_data, uint32_t length)
{
    bool ret = true;
    HAL_StatusTypeDef status  = HAL_OK;

    if(addr % 2 != 0)
    {
        return false;
    }

    HAL_FLASH_Unlock();

    for(int i = 0; i < length; i += 2)
    {
        uint16_t data = 0;
        data |= p_data[i + 0] << 0;
        data |= p_data[i + 1] << 8;

        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (addr + i), (uint64_t)data);
        if(status != HAL_OK)
        {
            ret = false;
            break;
        }
    }

    HAL_FLASH_Lock();

    return ret;
}

bool FlashRead(uint32_t addr, uint8_t* p_data, uint32_t length)
{
    bool ret = true;

    uint8_t* p_byte = (uint8_t*)addr;

    for(int i = 0; i < length; i++)
    {
        p_data[i] = p_byte[i];
    }

    return ret;
}
