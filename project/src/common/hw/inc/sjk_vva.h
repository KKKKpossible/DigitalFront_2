/*
 * sjk_vva.h
 *
 *  Created on: 2021. 4. 20.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_VVA_H_
#define SRC_COMMON_HW_INC_SJK_VVA_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"


#ifdef  HW_VVA_USE
#define DEF_VVA_CHANNEL_MAX HW_VVA_CHANNEL_MAX


#define VOLTAGE_DB_TABLE_MAX (31U)

#define VVA_SAVE_CHECK_ADDR  (0x8000000 + (62 * 1024))

#define SAVE_KEY_VALUE_0     (118U)
#define SAVE_KEY_VALUE_1     (96U)


typedef struct AD5592R_t
{
    uint8_t  now_tr_data[2];
    uint16_t db_100multiple;
}AD5592R_t;


typedef struct Vva_t
{
    uint16_t offset;
    uint16_t ratio;
}Vva_t;


extern Vva_t     vva_var;
extern AD5592R_t ad5592r_var;
extern uint16_t  voltage_per_db_arr[VOLTAGE_DB_TABLE_MAX];


bool     VvaInit        (uint8_t ch);
bool     VvaSendDb      (uint8_t ch, int db_100multiple);
bool     VvaDbRead      (uint8_t ch, uint16_t* db_buff);
bool     VvaSendVoltage (uint8_t ch, uint16_t voltage);
bool     VvaReadVoltage (uint8_t ch, uint16_t* mv_buff);
bool     VvaTableLoad   (uint8_t ch);
bool     VvaTableSave   (uint8_t ch);

#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_VVA_H_ */
