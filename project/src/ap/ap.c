/*
 * ap.c
 *
 *  Created on: Apr 13, 2021
 *      Author: sungjinkim
 */


#include "ap.h"
#include "stdio.h"

bool ApInit(void)
{
	bool ret = true;

	return ret;
}

bool ApMain(void)
{
	bool ret = true;

	CDC_Transmit_FS("1234", 5);
	return ret;
}
