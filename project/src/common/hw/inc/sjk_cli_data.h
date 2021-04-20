/*
 * sjk_cli_def.h
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */

#ifndef SRC_COMMON_HW_INC_SJK_CLI_DATA_H_
#define SRC_COMMON_HW_INC_SJK_CLI_DATA_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "hw.h"


#ifdef  HW_CLI_USE


// cli cmd string arr
extern char* cli_cmd_mode_cmd   [];

extern char* cli_log_on_cmd     [];
extern char* cli_log_off_cmd    [];
extern char* cli_log_toggle_cmd [];
extern char* cli_log_read_cmd   [];

// cli cmd method
void CliCmdModeToggle (uint8_t* data);

void CliLogOn         (uint8_t* data);
void CliLogOff        (uint8_t* data);
void CliLogToggle     (uint8_t* data);
void CliLogRead       (uint8_t* data);

// led cmd string arr
extern char* cli_led_on_cmd     [];
extern char* cli_led_off_cmd    [];
extern char* cli_led_toggle_cmd [];
extern char* cli_led_read_cmd   [];
// led cmd method
void CliLedOn     (uint8_t* data);
void CliLedOff    (uint8_t* data);
void CliLedToggle (uint8_t* data);
void CliLedRead   (uint8_t* data);


#endif


#ifdef __cplusplus
}
#endif

#endif /* SRC_COMMON_HW_INC_SJK_CLI_DATA_H_ */
