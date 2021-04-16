/*
 * sjk_cli.h
 *
 *  Created on: 2021. 4. 15.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_CLI_H_
#define SRC_COMMON_HW_INC_SJK_CLI_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw_def.h"


#ifdef  HW_CLI_USE
#define DEF_CLI_CHANNEL_MAX HW_CLI_CHANNEL_MAX

typedef enum ECHO_ENUM
{
    SERIAL, ETHERNET, ECHO_ENUM_MAX
}ECHO_ENUM;


typedef struct Cli_t
{
    const char* name;
    char**      cmd;
    void  (*fp)(void);
}Cli_t;



typedef struct Parse_t
{
    bool     asterisk_det;
    uint8_t  buffer[100];
    uint16_t index;
    bool     echo_on[ECHO_ENUM_MAX];
    bool     cmd_mode_on;
    bool     log_on;
}Parse_t;


bool CliInit (void);
void Parse   (uint8_t data);


#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INC_SJK_CLI_H_ */