/*
 * sjk_vv.c
 *
 *  Created on: 2021. 4. 20.
 *      Author: sungjinkim
 */


#include "sjk_vva.h"
#include "sjk_spi.h"


#define VOLTAGE_DB_TABLE_MAX (31U)
#define DEFAULT_DB_SET_VAL   (0U)


typedef struct Vva_t
{
    uint16_t offset;
    uint16_t ratio;
}Vva_t;


Vva_t     vva_var;
AD5592R_t ad5592r_var;
uint16_t  voltage_per_db_arr[VOLTAGE_DB_TABLE_MAX];


static void CalculateVvaToSpiArr(uint8_t ch, uint16_t db_100multiple, uint8_t* buffer);


bool VvaInit(uint8_t ch)
{
    bool ret = true;

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            vva_var.offset = 0;
            vva_var.ratio  = 100;
            for(int i = 0; i < VOLTAGE_DB_TABLE_MAX; i++)
            {
                voltage_per_db_arr[i] = vva_var.offset + vva_var.ratio * i;
            }
            VvaWrite(ch, DEFAULT_DB_SET_VAL);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

bool VvaWrite(uint8_t ch, uint16_t db_100multiple)
{
    bool ret = true;
    uint8_t send_buffer[2] = {0, };

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            CalculateVvaToSpiArr(ch, db_100multiple, send_buffer);
            SpiWrite(ch, send_buffer, 2);
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

uint16_t VvaRead(uint8_t ch)
{
    uint16_t ret = 0;

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            ret = ad5592r_var.db_100multiple;
            break;
        default:
            break;
    }

    return ret;
}

static void CalculateVvaToSpiArr(uint8_t ch, uint16_t db_100multiple, uint8_t* buffer)
{
    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            if(db_100multiple > 30 * 100)
            {
                buffer[0] = ad5592r_var.now_tr_data[0];
                buffer[1] = ad5592r_var.now_tr_data[1];
                break;
            }
            ad5592r_var.db_100multiple = db_100multiple;

            uint16_t voltage_buff = voltage_per_db_arr[db_100multiple / 100];

            if((db_100multiple % 100 != 0) || (db_100multiple % 10 != 0))
            {
                voltage_buff += (voltage_per_db_arr[(db_100multiple % 100) + 1] - voltage_per_db_arr[db_100multiple % 100])
                              * ((db_100multiple % 100) / 100);
            }

            uint16_t voltage_12bit_buff = voltage_buff * 4095 / 3300;

            uint8_t high_4 = voltage_12bit_buff >> 8;
            uint8_t low_8  = voltage_12bit_buff - (high_4 << 8);

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
