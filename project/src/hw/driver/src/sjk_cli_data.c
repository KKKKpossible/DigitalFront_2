/*
 * sjk_cli_data.c
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */


#include "sjk_cli_data.h"


extern Cli_t   cli_arr[];
extern Parse_t parse_var;


// cli cmd string arr
char* cli_cmd_mode_cmd[] =
        {
                "*0C*1"     , "CMT"       , "\0"
        };
char* cli_log_on_cmd[] =
        {
                "logon"    , "LogOn"    , "Logon"    , "LG1", "\0"
        };
char* cli_log_off_cmd[] =
        {
                "logoff"   , "LogOff"   , "Logoff"   , "LG0", "\0"
        };
char* cli_log_toggle_cmd[] =
        {
                "logtoggle", "LogToggle", "Logtoggle", "LGT", "\0"
        };
char* cli_log_read_cmd[] =
        {
                "logread"  , "LogRead"  , "Logread"  , "LR" , "\0"
        };

// cli cmd method
void CliCmdModeToggle(uint8_t* data)
{
    if(parse_var.cmd_mode_on == true)
    {
        parse_var.cmd_mode_on = false;
        if(parse_var.log_on == true)
        {
            UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"CMD MODE OFF\r\n", 14);
        }
    }
    else
    {
        parse_var.cmd_mode_on = true;
        if(parse_var.log_on == true)
        {
            UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"CMD MODE ON\r\n", 13);
        }
    }
}

void CliLogOn(uint8_t* data)
{
    if(parse_var.log_on == false)
    {
        parse_var.log_on = true;
        if(parse_var.log_on == true)
        {
            UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"LOG ON\r\n", 8);
        }
    }
}

void CliLogOff(uint8_t* data)
{
    if(parse_var.log_on == true)
    {
        parse_var.log_on = false;
        if(parse_var.log_on == false)
        {
            UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"LOG OFF\r\n", 9);
        }
    }
}

void CliLogToggle(uint8_t* data)
{
    if(parse_var.log_on == true)
    {
        CliLogOff(data);
    }
    else
    {
        CliLogOn(data);
    }
}

void CliLogRead(uint8_t* data)
{
    if(parse_var.log_on == true)
    {
        UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"ON\r\n", 4);
    }
    else
    {
        UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"OFF\r\n", 5);
    }
}


// led cmd string arr
char* cli_led_on_cmd[] =
        {
                "ledon"    , "LedOn"    ,   "Ledon"    , "L1", "\0"
        };

char* cli_led_off_cmd[] =
        {
                "ledoff"   , "Led Off"   ,   "Ledoff"   , "L0", "\0"
        };

char* cli_led_toggle_cmd[] =
        {
                "ledtoggle", "LedToggle",   "Ledtoggle", "LT", "\0"
        };

char* cli_led_read_cmd[] =
        {
                "ledread"  , "LedRead"  ,   "Ledread"  , "LR", "\0"
        };

// led cmd method
void CliLedOn(uint8_t* data)
{
    bool result = LedOn(DEF_LED_CHANNEL_0);

    if(parse_var.log_on == true)
    {
        if(result == true)
        {
            UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"LED ON\r\n", 8);
        }
        else
        {
            UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", 8);
        }
    }
}

void CliLedOff(uint8_t* data)
{
    bool result = LedOff(DEF_LED_CHANNEL_0);

    if(parse_var.log_on == true)
    {
        if(result == true)
        {
            UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"LED OFF\r\n", strlen("LED OFF\r\n"));
        }
        else
        {
            UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", strlen("ERROR\r\n"));
        }
    }
}

void CliLedToggle(uint8_t* data)
{
    bool result = LedToggle(DEF_LED_CHANNEL_0);

    if(parse_var.log_on == true)
    {
        if(result == true)
        {
            UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"LED TOGGLE\r\n", strlen("LED TOGGLE\r\n"));
        }
        else
        {
            UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", strlen("ERROR\r\n"));
        }
    }
}

void CliLedRead(uint8_t* data)
{

    if(parse_var.log_on == true)
    {
        ReadState state = LedRead(DEF_LED_CHANNEL_0);

        switch(state)
        {
            case RS_ERROR:
                UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", strlen("ERROR\r\n"));
                break;
            case RS_GPIO_PIN_RESET:
                UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"RESET\r\n", strlen("RESET\r\n"));
                break;
            case RS_GPIO_PIN_SET:
                UartWrite(DEF_UART_CHANNEL_0, (uint8_t*)"SET\r\n", strlen("SET\r\n"));
                break;
            default:
                break;
        }
    }
}
