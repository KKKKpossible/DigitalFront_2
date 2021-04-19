/*
 * sjk_cli.c
 *
 *  Created on: 2021. 4. 15.
 *      Author: sungjinkim
 */


#include "sjk_cli.h"
#include "sjk_cli_data.h"
#include "hw.h"


extern Cli_t   cli_arr[];
extern Parse_t parse_var;


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
                {.name = "LED ON"         , .cmd = cli_led_on_cmd     , .fp = CliLedOn        },
                {.name = "LED OFF"        , .cmd = cli_led_off_cmd    , .fp = CliLedOff       },
                {.name = "LED TOGGLE"     , .cmd = cli_led_toggle_cmd , .fp = CliLedToggle    },
                {.name = "LED Read"       , .cmd = cli_led_read_cmd   , .fp = CliLedRead      },
                {.name = "CMD MODE ON OFF", .cmd = cli_cmd_mode_cmd   , .fp = CliCmdModeToggle}
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
    if(parse_var.index >= PARSE_BUFF_MAX)
    {
        parse_var.index = PARSE_BUFF_MAX - 1;
    }

    if(parse_var.cmd_mode_on == true)
    {
        switch(data)
        {
            case '\r':
            case '\n':
               if(parse_var.index != 0)
               {
                   parse_var.buffer[parse_var.index] = '\0';
                   ParseProcedure();
                   parse_var.index = 0;
               }
               else
               {
                   parse_var.index = 0;
               }
               break;
            default:
               parse_var.buffer[parse_var.index] = data;
               parse_var.index++;
               break;
        }
    }
    else
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
                    parse_var.asterisk_det = false;
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
                    parse_var.asterisk_det = false;
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
                    parse_var.index++;
                    parse_var.asterisk_det = false;
                }
                else
                {
                    parse_var.buffer[parse_var.index] = data;
                    parse_var.index++;
                }
                break;
            default:
                if(parse_var.asterisk_det == true)
                {
                    parse_var.asterisk_det = false;
                }
                parse_var.buffer[parse_var.index] = data;
                parse_var.index++;
                break;
        }
    }
}
