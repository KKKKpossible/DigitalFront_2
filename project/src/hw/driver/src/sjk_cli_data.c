/*
 * sjk_cli_data.c
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */


#include "sjk_cli_data.h"
#include "stdio.h"


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
void CliCmdModeToggle(uint8_t ch, char* fmt, ...)
{
    char buf[256] = {0, };
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 256, fmt, args);

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
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
            break;
        default:
            break;
    }

    va_end(args);
}

void CliLogOn(uint8_t ch, char* fmt, ...)
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

void CliLogOff(uint8_t ch, char* fmt, ...)
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

void CliLogToggle(uint8_t ch, char* fmt, ...)
{
    if(parse_var.log_on == true)
    {
        CliLogOff(ch, "%c", '\0');
    }
    else
    {
        CliLogOn(ch, "%c", '\0');
    }
}

void CliLogRead(uint8_t ch, char* fmt, ...)
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
void CliLedOn(uint8_t ch, char* fmt, ...)
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

void CliLedOff(uint8_t ch, char* fmt, ...)
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

void CliLedToggle(uint8_t ch, char* fmt, ...)
{
    char buf[256] = {0, };
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 256, fmt, args);

    bool result = LedToggle(DEF_LED_CHANNEL_0);

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
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
            break;
        default:
            break;
    }

    va_end(args);
}

void CliLedRead(uint8_t ch, char* fmt, ...)
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

// vva cmd string arr
char* cli_vva_dbset[] =
        {
                "vvaset", "VVASet", "VVASET", "VVS", "\0"
        };

char* cli_vva_dbread[] =
        {
                "vvaread", "VVARead", "VVAREAD", "VVR", "\0"
        };

char* cli_vva_tableset[] =
        {
                "vvatableset", "VVATableSet", "VVATABLESET", "VVTS", "\0"
        };

char* cli_vva_tableread[] =
        {
                "vvatableread", "VVATableRead", "VVATABLEREAD", "VVTR", "\0"
        };

char* cli_vva_voltage_set  [] =
        {
                "vvavoltset", "VVAVoltSet", "VVAVOLTSET", "VVVS", "\0"
        };
char* cli_vva_voltage_read [] =
        {
                "vvavoltread", "VVAVoltRead", "VVAVOLTREAD", "VVVR", "\0"
        };

//vva cmd method
void CliVvaDbSet(uint8_t ch, char* fmt, ...)
{

}

void CliVvaDbRead(uint8_t ch, char* fmt, ...)
{

}

void CliVvaTableSet(uint8_t ch, char* fmt, ...)
{

}

void CliVvaTableRead(uint8_t ch, char* fmt, ...)
{

}

void CliVvaVoltSet(uint8_t ch, char* fmt, ...)
{

}

void CliVvaVoltRead(uint8_t ch, char* fmt, ...)
{

}
