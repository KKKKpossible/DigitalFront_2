/*
 * hw_pp.cpp
 *
 *  Created on: 2021. 5. 10.
 *      Author: sungjinkim
 */


#include "hw_pp.h"


extern Adafruit_SSD1306 display;


bool HwppInit(void)
{
    bool ret = true;

    display.begin_1106(SSD1306_SWITCHCAPVCC, 0x7A);

    return ret;
}
