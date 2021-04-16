#include "main.h"
#include "main_pp.h"


extern ApClass ap;

extern UART_HandleTypeDef huart1;

extern Cli_t cli_arr[DEF_CLI_CHANNEL_MAX];

int main(void)
{
	HwInit();
	ApInit();

	while(true)
	{
		ApMain();
		ap.ApppMain();
	}

	return 0;
}
