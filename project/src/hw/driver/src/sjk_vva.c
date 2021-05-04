/*
 * sjk_vv.c
 *
 *  Created on: 2021. 4. 20.
 *      Author: sungjinkim
 */


#include "sjk_vva.h"
#include "sjk_spi.h"
#include "sjk_flash.h"


Vva_t     vva_var;
AD5592R_t ad5592r_var;
uint16_t  voltage_per_db_arr[VOLTAGE_DB_TABLE_MAX];


static void DbCalculateVvaToSpiArr   (uint8_t ch, int      db_100multiple, uint8_t* buffer);
static void VoltCalculateVvaToSpiArr (uint8_t ch, uint16_t milli_volt    , uint8_t* buffer);
static bool SearchDbInTabel          (uint8_t ch, uint16_t milli_volt);


bool VvaInit(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            if(VvaTableLoad(ch) != true)
            {
                vva_var.offset = 0;
                vva_var.ratio  = 100;
                for(int i = 0; i < VOLTAGE_DB_TABLE_MAX; i++)
                {
                    voltage_per_db_arr[i]  = vva_var.offset + vva_var.ratio * i;
                }
                VvaTableSave(ch);
            }
            VvaSendDb(ch, voltage_per_db_arr[0]);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool VvaSendDb(uint8_t ch, int db_100multiple)
{
    bool ret = true;
    uint8_t send_buffer[2] = {0, };

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            DbCalculateVvaToSpiArr(ch, db_100multiple, send_buffer);
            SpiWrite(ch, send_buffer, 2);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool VvaDbRead(uint8_t ch, uint16_t* db_buff)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            *db_buff = ad5592r_var.db_100multiple;
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool VvaSendVoltage(uint8_t ch, uint16_t milli_volt)
{
    bool    ret            = true;
    uint8_t spi_tr_buff[2] = {0, };

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            VoltCalculateVvaToSpiArr(ch, milli_volt, spi_tr_buff);
            SpiWrite(DEF_SPI_CHANNEL_0, spi_tr_buff, 2);

            break;
        default:
            ret = false;
            break;
    }
    return ret;
}

bool VvaReadVoltage (uint8_t ch, uint16_t* mv_buff)
{
    bool ret = true;
    uint16_t buffer = 0;

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            for(int i = 0; i < 12; i++)
            {
                if(i < 8)
                {
                    if((ad5592r_var.now_tr_data[1] & (1 << i)) != 0)
                    {
                        buffer |= (1 << i);
                    }
                }
                else
                {
                    if((ad5592r_var.now_tr_data[0] & (1 << (i - 8))) != 0)
                    {
                        buffer |= (1 << i);
                    }
                }
            }
            *mv_buff = buffer;
            break;
        default:
            ret = false;
    }

    return ret;
}

static void DbCalculateVvaToSpiArr(uint8_t ch, int db_100multiple, uint8_t* buffer)
{
    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            if(db_100multiple < 0)
            {
                db_100multiple = -db_100multiple;
            }
            if(db_100multiple > 30 * 100)
            {
                buffer[0] = ad5592r_var.now_tr_data[0];
                buffer[1] = ad5592r_var.now_tr_data[1];
                break;
            }
            ad5592r_var.db_100multiple = db_100multiple;

            uint16_t voltage_buff = voltage_per_db_arr[db_100multiple / 100];

            if(db_100multiple % 100 != 0)
            {
                voltage_buff += (voltage_per_db_arr[(db_100multiple % 100) + 1] - voltage_per_db_arr[db_100multiple % 100])
                              * ((db_100multiple % 100) / 100);
            }

            float f_voltage_12bit_buff = voltage_buff * 4095.0 / 3300.0;
            int i_voltage_12bit_buff = f_voltage_12bit_buff;
            if(f_voltage_12bit_buff - (int)f_voltage_12bit_buff > 0.5)
            {
                i_voltage_12bit_buff += 1;
            }
            if(i_voltage_12bit_buff > 4095)
            {
                i_voltage_12bit_buff = 4095;
            }

            uint8_t high_4 = i_voltage_12bit_buff >> 8;
            uint8_t low_8  = i_voltage_12bit_buff - (high_4 << 8);

            uint8_t tr_buffer[2] = {0b10000000, 0b00000000};

            tr_buffer[0] |= high_4;
            tr_buffer[1] |= low_8;

            buffer[0] = tr_buffer[0];
            buffer[1] = tr_buffer[1];

            ad5592r_var.now_tr_data[0] = tr_buffer[0];
            ad5592r_var.now_tr_data[1] = tr_buffer[1];
            break;
        default:
            buffer[0] = ad5592r_var.now_tr_data[0];
            buffer[1] = ad5592r_var.now_tr_data[1];
            break;
    }
}

static bool SearchDbInTabel(uint8_t ch, uint16_t milli_volt)
{
    bool ret = true;

    for(int i = 0; i < VOLTAGE_DB_TABLE_MAX; i++)
    {
        if(voltage_per_db_arr[i] == milli_volt)
        {
            ad5592r_var.db_100multiple = i * 100;
            break;
        }
        else
        {
            if(i < VOLTAGE_DB_TABLE_MAX - 1)
            {
                if(voltage_per_db_arr[i] < voltage_per_db_arr[i + 1])
                {
                    if((voltage_per_db_arr[i] < milli_volt) && (milli_volt < voltage_per_db_arr[i + 1]))
                    {
                        ad5592r_var.db_100multiple = i * 100;
                        ad5592r_var.db_100multiple += (int)((float)(milli_volt - voltage_per_db_arr[i]) / (float)(voltage_per_db_arr[i + 1] - voltage_per_db_arr[i]) * 100.0);
                        break;
                    }
                }
                else
                {
                    if((voltage_per_db_arr[i + 1] < milli_volt) && (milli_volt < voltage_per_db_arr[i]))
                    {
                        ad5592r_var.db_100multiple  = i * 100;
                        ad5592r_var.db_100multiple += (milli_volt - voltage_per_db_arr[i + 1])
                                                    / (voltage_per_db_arr[i] - voltage_per_db_arr[i + 1]);
                        break;
                    }
                }
            }
            else
            {
                ret = false;
            }
        }
    }

    return ret;
}

static void VoltCalculateVvaToSpiArr(uint8_t ch, uint16_t milli_volt, uint8_t* buffer)
{
    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            if((milli_volt > 3300) || (milli_volt < 0))
            {
                buffer[0] = ad5592r_var.now_tr_data[0];
                buffer[1] = ad5592r_var.now_tr_data[1];
                break;
            }
            if(SearchDbInTabel(ch, milli_volt) != true)
            {
                buffer[0] = ad5592r_var.now_tr_data[0];
                buffer[1] = ad5592r_var.now_tr_data[1];
                break;
            }

            float f_voltage_12bit_buff = milli_volt * 4095.0 / 3300.0;
            int i_voltage_12bit_buff = f_voltage_12bit_buff;
            if(f_voltage_12bit_buff - (int)f_voltage_12bit_buff > 0.5)
            {
                i_voltage_12bit_buff += 1;
            }
            if(i_voltage_12bit_buff > 4095)
            {
                i_voltage_12bit_buff = 4095;
            }

            uint8_t high_4 = i_voltage_12bit_buff >> 8;
            uint8_t low_8  = i_voltage_12bit_buff - (high_4 << 8);

            uint8_t tr_buffer[2] = {0b10000000, 0b00000000};

            tr_buffer[0] |= high_4;
            tr_buffer[1] |= low_8;

            buffer[0] = tr_buffer[0];
            buffer[1] = tr_buffer[1];

            ad5592r_var.now_tr_data[0] = tr_buffer[0];
            ad5592r_var.now_tr_data[1] = tr_buffer[1];
            break;
    }
}

bool VvaTableLoad(uint8_t ch)
{
    bool ret = true;

    uint8_t flash_load_buff[(31 * 2) + 2] = {0, };

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            FlashRead(VVA_SAVE_CHECK_ADDR, flash_load_buff, (VOLTAGE_DB_TABLE_MAX * 2) + 2);
            if((flash_load_buff[0] == SAVE_KEY_VALUE_0) && (flash_load_buff[1] == SAVE_KEY_VALUE_1))
            {
                for(int i = 0; i < VOLTAGE_DB_TABLE_MAX; i++)
                {
                    voltage_per_db_arr[i]  = 0;
                    voltage_per_db_arr[i] |= flash_load_buff[2 * i + 2];
                    voltage_per_db_arr[i] |= flash_load_buff[(2 * i) + 1 + 2] << 8;
                }
            }
            else
            {
                ret = false;
            }
            break;
        default:
            break;
    }

    return ret;
}

bool VvaTableSave(uint8_t ch)
{
    bool    ret        = true;
    uint8_t key_arr[2] = {SAVE_KEY_VALUE_0, SAVE_KEY_VALUE_1};

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            FlashErase(VVA_SAVE_CHECK_ADDR, (VOLTAGE_DB_TABLE_MAX * 2) + 2);
            FlashWrite(VVA_SAVE_CHECK_ADDR, key_arr, 2);
            FlashWrite(VVA_SAVE_CHECK_ADDR + 2, (uint8_t*)voltage_per_db_arr, VOLTAGE_DB_TABLE_MAX * 2);
            break;
        default:
            break;
    }

    return ret;
}
