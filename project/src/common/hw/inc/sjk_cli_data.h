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
// cli cmd method
void CliCmdModeToggle (uint8_t ch, char* fmt, ...);

// cli log string arr
extern char* cli_log_on_cmd     [];
extern char* cli_log_off_cmd    [];
extern char* cli_log_toggle_cmd [];
extern char* cli_log_read_cmd   [];
// cli log method
void CliLogOn         (uint8_t ch, char* fmt, ...);
void CliLogOff        (uint8_t ch, char* fmt, ...);
void CliLogToggle     (uint8_t ch, char* fmt, ...);
void CliLogRead       (uint8_t ch, char* fmt, ...);

// led cmd string arr
extern char* cli_led_on_cmd     [];
extern char* cli_led_off_cmd    [];
extern char* cli_led_toggle_cmd [];
extern char* cli_led_read_cmd   [];
// led cmd method
void CliLedOn     (uint8_t ch, char* fmt, ...);
void CliLedOff    (uint8_t ch, char* fmt, ...);
void CliLedToggle (uint8_t ch, char* fmt, ...);
void CliLedRead   (uint8_t ch, char* fmt, ...);

// vva cmd string arr
extern char* cli_vva_dbset        [];
extern char* cli_vva_dbread       [];
extern char* cli_vva_tableset     [];
extern char* cli_vva_tableread    [];
extern char* cli_vva_voltage_set  [];
extern char* cli_vva_voltage_read [];
//vva cmd method
void CliVvaDbSet     (uint8_t ch, char* fmt, ...);
void CliVvaDbRead    (uint8_t ch, char* fmt, ...);
void CliVvaTableSet  (uint8_t ch, char* fmt, ...);
void CliVvaTableRead (uint8_t ch, char* fmt, ...);
void CliVvaVoltSet   (uint8_t ch, char* fmt, ...);
void CliVvaVoltRead  (uint8_t ch, char* fmt, ...);


#endif


#ifdef __cplusplus
}
#endif

#endif /* SRC_COMMON_HW_INC_SJK_CLI_DATA_H_ */
