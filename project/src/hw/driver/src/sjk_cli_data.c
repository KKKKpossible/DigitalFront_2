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
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"CMD MODE OFF\r\n", 14);
                }
            }
            else
            {
                parse_var.cmd_mode_on = true;
                if(parse_var.log_on == true)
                {
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"CMD MODE ON\r\n", 13);
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
            UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"LOG ON\r\n", 8);
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
            UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"LOG OFF\r\n", 9);
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
        UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"ON\r\n", 4);
    }
    else
    {
        UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"OFF\r\n", 5);
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
            UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"LED ON\r\n", 8);
        }
        else
        {
            UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", 8);
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
            UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"LED OFF\r\n", strlen("LED OFF\r\n"));
        }
        else
        {
            UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", strlen("ERROR\r\n"));
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
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"LED TOGGLE\r\n", strlen("LED TOGGLE\r\n"));
                }
                else
                {
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", strlen("ERROR\r\n"));
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
                UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", strlen("ERROR\r\n"));
                break;
            case RS_GPIO_PIN_RESET:
                UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"RESET\r\n", strlen("RESET\r\n"));
                break;
            case RS_GPIO_PIN_SET:
                UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"SET\r\n", strlen("SET\r\n"));
                break;
            default:
                break;
        }
    }
}

// vva cmd string arr
char* cli_vva_dbset[] =
        {
                "vvadbset"     , "VVADbSet"     , "VVADBSET"     , "VVDS" , "\0"
        };

char* cli_vva_dbread[] =
        {
                "vvadbread"    , "VVADbRead"    , "VVADBREAD"    , "VVDR" , "\0"
        };

char* cli_vva_tableset[] =
        {
                "vvatableset"  , "VVATableSet"  , "VVATABLESET"  , "VVTS" , "\0"
        };

char* cli_vva_tableread[] =
        {
                "vvatableread" , "VVATableRead" , "VVATABLEREAD" , "VVTR" , "\0"
        };

char* cli_vva_voltage_set[] =
        {
                "vvamilvoltset", "VVAMilVoltSet", "VVAMILVOLTSET", "VVMVS", "\0"
        };
char* cli_vva_voltage_read[] =
        {
                "vvavoltread"  , "VVAVoltRead"  , "VVAVOLTREAD"  , "VVVR" , "\0"
        };

//vva cmd method
void CliVvaDbSet(uint8_t ch, char* fmt, ...)
{
    char buf[256] = {0, };
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 256, fmt, args);

    uint16_t var = 0;

    bool point_check = false;

    for(int i = 0; buf[i] != '\0'; i++)
    {
        if(buf[i] == '.')
        {
            point_check = true;

            if(i < 255)
            {
                buf[i] = '\0';
                var = atoi(buf) * 100;

                if(i + 1 + 3 < 255)
                {
                    buf[i + 1 + 3] = '\0';
                    uint16_t var_under = atoi(&buf[i + 1]);
                    if(var_under < 10)
                    {
                        var_under *= 10;
                    }
                    var += var_under;
                }
            }
            else if(i == 255)
            {
                buf[i] = '\0';
                var = atoi(buf) * 100;
            }
        }
    }

    bool result = false;

    if(point_check == true)
    {
        result = VvaSendDb(DEF_VVA_CHANNEL_0, var);
    }

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(parse_var.log_on == true)
            {
                if(result == true)
                {
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"VVA DB SET\r\n", strlen("VVA DB SET\r\n"));
                }
                else
                {
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", strlen("ERROR\r\n"));
                }
            }
            break;
        default:
            break;
    }

    va_end(args);
}

void CliVvaDbRead(uint8_t ch, char* fmt, ...)
{
    char buf[256] = {0, };
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 256, fmt, args);

    uint16_t value = 0;
    bool result = VvaDbRead(DEF_VVA_CHANNEL_0, &value);

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(parse_var.log_on == true)
            {
                if(result == true)
                {
                    char buffer[30] = {0, };
                    uint16_t overpoint = 0;
                    uint16_t underpoint = 0;

                    overpoint  = value / 100;
                    underpoint = value - (overpoint * 100);
                    if(underpoint < 10)
                    {
                        sprintf(buffer, "VVA DB READ %d.0%d\r\n", overpoint, underpoint);
                    }
                    else
                    {
                        sprintf(buffer, "VVA DB READ %d.%d\r\n", overpoint, underpoint);
                    }
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)buffer, strlen(buffer));
                }
                else
                {
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", strlen("ERROR\r\n"));
                }
            }
            break;
        default:
            break;
    }

    va_end(args);
}

void CliVvaTableSet(uint8_t ch, char* fmt, ...)
{
    char buf[256] = {0, };
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 256, fmt, args);

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            break;
        default:
            break;
    }

    va_end(args);
}

void CliVvaTableRead(uint8_t ch, char* fmt, ...)
{
    char buf[256] = {0, };
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 256, fmt, args);

    int index = atoi(buf);

    switch(ch)
    {
        case DEF_VVA_CHANNEL_0:
            if(index != -1)
            {
                if(parse_var.log_on == true)
                {
                    uint8_t tr_buffer[50] = {0, };
                    sprintf((char*)tr_buffer, "VVA TABLE READ [%d] = %d[mV]\r\n", index, (int)voltage_per_db_arr[index]);
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)tr_buffer, strlen((char*)tr_buffer));
                }
            }
            else
            {
                if(parse_var.log_on == true)
                {
                    uint8_t tr_buffer[50] = {0, };
                    for(int i = 0; i < VOLTAGE_DB_TABLE_MAX; i++)
                    {
                        sprintf((char*)tr_buffer, "VVA TABLE READ [%d] = %d[mV]\r\n", i, (int)voltage_per_db_arr[i]);
                        UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)tr_buffer, strlen((char*)tr_buffer));
                    }
                }
            }
            break;
        default:
            break;
    }

    va_end(args);
}

void CliVvaMiliVoltSet(uint8_t ch, char* fmt, ...)
{
    char buf[256] = {0, };
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 256, fmt, args);

    bool result = VvaSendVoltage(DEF_VVA_CHANNEL_0, atoi(buf));

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(parse_var.log_on == true)
            {
                if(result == true)
                {
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"VVA MILLI VOLT SET\r\n", strlen("VVA MILLI VOLT SET\r\n"));
                }
                else
                {
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", strlen("ERROR\r\n"));
                }
            }
            break;
        default:
            break;
    }

    va_end(args);
}

void CliVvaVoltRead(uint8_t ch, char* fmt, ...)
{
    char buf[256] = {0, };
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 256, fmt, args);

    uint16_t value = 0;
    bool result = VvaReadVoltage(DEF_VVA_CHANNEL_0, &value);

    float f_value = value * 3300.0 / 4095.0;
    value = f_value;
    if(f_value - (int)(f_value) > 0.5)
    {
        value += 1;
    }

    switch(ch)
    {
        case DEF_UART_CHANNEL_0:
            if(parse_var.log_on == true)
            {
                if(result == true)
                {
                    char buffer[100] = {0, };
                    sprintf(buffer, "VVA VOLT READ %d.%d[V]\r\n", value / 1000, value % 1000);
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)buffer, strlen(buffer));
                }
                else
                {
                    UartWriteTxBuffer(DEF_UART_CHANNEL_0, (uint8_t*)"ERROR\r\n", strlen("ERROR\r\n"));
                }
            }
            break;
        default:
            break;
    }

    va_end(args);
}
