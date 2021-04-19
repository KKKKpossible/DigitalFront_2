/*
 * sjk_cli_data.c
 *
 *  Created on: 2021. 4. 19.
 *      Author: sungjinkim
 */


#include "sjk_cli_data.h"


extern Cli_t   cli_arr[DEF_CLI_CHANNEL_MAX];
extern Parse_t parse_var;


char* cli_led_on_cmd[] =
        {
                "led on", "Led On", "Led on", "\0",
        };

char* cli_led_off_cmd[] =
        {
                "led off", "Led Off", "Led off", "\0"
        };

char* cli_led_toggle_cmd[] =
        {
                "led toggle", "Led Toggle", "Led toggle", "\0"
        };

char* cli_led_read_cmd[] =
        {
                "led read", "Led Read", "Led read", "\0"
        };

void CliLedOn(void)
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

void CliLedOff(void)
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

void CliLedToggle(void)
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

void CliLedRead(void)
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



char* cli_cmd_mode_cmd[] =
        {
                "*0C*1"
        };

void CliCmdModeToggle(void)
{
    if(parse_var.cmd_mode_on == true)
    {
        parse_var.cmd_mode_on = false;
    }
    else
    {
        parse_var.cmd_mode_on = true;
    }
}
