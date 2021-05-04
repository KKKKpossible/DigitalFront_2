/*
 * ap.h
 *
 *  Created on: Apr 13, 2021
 *      Author: sungjinkim
 */

#ifndef SRC_AP_AP_H_
#define SRC_AP_AP_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw.h"


typedef enum ApFault_enum
{
    FAULT_CURRENT,
    FAULT_TEMP_0,
    FAULT_HTEMP_0,
}ApFault_enum;


bool ApInit(void);
bool ApMain(void);


extern uint64_t global_fault;


#ifdef __cplusplus
}
#endif



#endif /* SRC_AP_AP_H_ */
