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


static void CheckDividerArgOne  (char** pcheck);
static void CmdCatchWithExecute (char** pcheck);
static bool ParseProcedure      (void);

Cli_t cli_arr[] =
        {
                {.name = "LED ON"         , .cmd = cli_led_on_cmd       , .fp = CliLedOn        },
                {.name = "LED OFF"        , .cmd = cli_led_off_cmd      , .fp = CliLedOff       },
                {.name = "LED TOGGLE"     , .cmd = cli_led_toggle_cmd   , .fp = CliLedToggle    },
                {.name = "LED Read"       , .cmd = cli_led_read_cmd     , .fp = CliLedRead      },
                {.name = "CMD MODE ON OFF", .cmd = cli_cmd_mode_cmd     , .fp = CliCmdModeToggle},
                {.name = "LOG ON"         , .cmd = cli_log_on_cmd       , .fp = CliLogOn        },
                {.name = "LOG OFF"        , .cmd = cli_log_off_cmd      , .fp = CliLogOff       },
                {.name = "LOG TOGGLE"     , .cmd = cli_log_toggle_cmd   , .fp = CliLogToggle    },
                {.name = "LOG Read"       , .cmd = cli_log_read_cmd     , .fp = CliLogRead      },
                {.name = "VVA Set"        , .cmd = cli_vva_dbset        , .fp = CliVvaDbSet     },
                {.name = "VVA Read"       , .cmd = cli_vva_dbread       , .fp = CliVvaDbRead    },
                {.name = "VVA TableSet"   , .cmd = cli_vva_tableset     , .fp = CliVvaTableSet  },
                {.name = "VVA TableRead"  , .cmd = cli_vva_tableread    , .fp = CliVvaTableRead },
                {.name = "VVA VoltSet"    , .cmd = cli_vva_voltage_set  , .fp = CliVvaVoltSet   },
                {.name = "VVA VoltRead"   , .cmd = cli_vva_voltage_read , .fp = CliVvaVoltRead  },
                {.name = "\0"}
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

static void CheckDividerArgOne(char** pcheck)
{
    int      index              = 0;
    char     divider[]          = " \t\0";
    uint16_t count_divider      = 0;
    uint16_t next_index_pcheck  = count_divider + 1;

    pcheck[0] = (char*)&parse_var.buffer[0];

    for(; parse_var.buffer[index] != '\0'; index++)
    {
        if(count_divider != 0)
        {
            for(int i = 0; divider[i] != '\0'; i++)
            {
                if(parse_var.buffer[index] == divider[i])
                {
                    parse_var.buffer[index] = '\0';
                    if(parse_var.buffer[index + 1] != '\0')
                    {
                        pcheck[next_index_pcheck] = (char*)(&parse_var.buffer[index + 1]);
                        break;
                    }
                }
            }
        }
        for(int i = 0; divider[i] != '\0'; i++)
        {
            if(parse_var.buffer[index] == divider[i])
            {
                parse_var.buffer[index] = '\0';
                if(parse_var.buffer[index + 1] != '\0')
                {
                    pcheck[next_index_pcheck] = (char*)(&parse_var.buffer[index + 1]);
                    count_divider++;
                    next_index_pcheck  = count_divider + 1;
                    break;
                }
            }
        }
    }
}

static void CmdCatchWithExecute(char** pcheck)
{
    bool catched_cmd = false;

    for(int i = 0; cli_arr[i].name[0] != '\0'; i++)
    {
        if(catched_cmd == true)
        {
            break;
        }

        int j = 0;
        while(cli_arr[i].cmd[j][0] != '\0')
        {
            if(strcmp((const char*)(pcheck[0]), cli_arr[i].cmd[j]) == 0)
            {
                if(pcheck[1] == NULL)
                {
                    cli_arr[i].fp(DEF_UART_CHANNEL_0 , "%c", '\0');
                }
                else
                {
                    if(pcheck[2] == NULL)
                    {
                        cli_arr[i].fp(DEF_UART_CHANNEL_0, "%s", pcheck[1]);
                    }
                    else
                    {
                        cli_arr[i].fp(DEF_UART_CHANNEL_0, "%s %s", pcheck[1], pcheck[2]);
                    }
                }
                catched_cmd = true;
                break;
            }
            j++;
        }
    }
}

static bool ParseProcedure(void)
{
    bool ret = 0;

    char* pcheck[3] = {NULL, NULL, NULL};
    CheckDividerArgOne(pcheck);
    CmdCatchWithExecute(pcheck);

    return ret;
}
