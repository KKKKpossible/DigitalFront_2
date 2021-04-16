/*
 * sjk_cli.c
 *
 *  Created on: 2021. 4. 15.
 *      Author: sungjinkim
 */


#include "sjk_cli.h"
#include "hw.h"


extern Cli_t   cli_arr[];
extern Parse_t parse_var;

static char* cli_led_on[] =
        {
                "led on", "Led On", "Led on", "\0",
        };

static char* cli_led_off[] =
        {
                "led off", "Led Off", "Led off", "\0"
        };

static char* cli_led_toggle[] =
        {
                "led toggle", "Led Toggle", "Led toggle", "\0"
        };

static char* cli_led_read[] =
        {
                "led read", "Led Read", "Led read", "\0"
        };


static char* cli_cmd_mode[] =
        {
                "C"
        };

static void CliLedOn(void)
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

static void CliLedOff(void)
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

static void CliLedToggle(void)
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

static void CliLedRead(void)
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

static void CliCmdModeToggle(void)
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


static bool ParseProcedure(void)
{
    bool ret = 0;
    bool catched = false;
    for(int i = 0; i < DEF_CLI_CHANNEL_MAX; i++)
    {
        if(catched == true)
        {
            break;
        }

        int j = 0;
        while(cli_arr[i].cmd[j][0] != '\0')
        {
            if(strcmp((const char*)parse_var.buffer, cli_arr[i].cmd[j]) == 0)
            {
                cli_arr[i].fp();
                catched = true;
                break;
            }
            j++;
        }
    }

    return ret;
}

Cli_t cli_arr[DEF_CLI_CHANNEL_MAX] =
        {
                {.name = "LED ON"         , .cmd = cli_led_on     , .fp = CliLedOn        },
                {.name = "LED OFF"        , .cmd = cli_led_off    , .fp = CliLedOff       },
                {.name = "LED TOGGLE"     , .cmd = cli_led_toggle , .fp = CliLedToggle    },
                {.name = "LED Read"       , .cmd = cli_led_read   , .fp = CliLedRead      },
                {.name = "CMD MODE ON OFF", .cmd = cli_cmd_mode   , .fp = CliCmdModeToggle}
        };

Parse_t parse_var;

bool CliInit(void)
{
    bool ret = true;

    parse_var.asterisk_det      = false;
    parse_var.echo_on[SERIAL]   = true;
    parse_var.echo_on[ETHERNET] = false;
    parse_var.cmd_mode_on       = true;
    parse_var.log_on            = true;

    return ret;
}

void Parse(uint8_t data)
{
    switch(data)
    {
        case '*':
            parse_var.asterisk_det = true;
            break;
        case 0:
            if(parse_var.asterisk_det == true)
            {
                parse_var.index = 0;
            }
            else
            {
                parse_var.buffer[parse_var.index] = data;
                parse_var.index++;
            }
            break;
        case 1:
            if(parse_var.asterisk_det == true)
            {
                parse_var.buffer[parse_var.index] = '\0';
                ParseProcedure();
            }
            else
            {
                parse_var.buffer[parse_var.index] = data;
                parse_var.index++;
            }
            break;
        case 2:
            if(parse_var.asterisk_det == true)
            {
                parse_var.buffer[parse_var.index] = '*';
            }
            else
            {
                parse_var.buffer[parse_var.index] = data;
                parse_var.index++;
            }
            break;
        default:
            parse_var.buffer[parse_var.index] = data;
            parse_var.index++;
            break;
    }
}
