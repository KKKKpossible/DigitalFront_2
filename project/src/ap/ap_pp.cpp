/*
 * ap_pp.cpp
 *
 *  Created on: 2021. 4. 13.
 *      Author: sungjinkim
 */


#include "ap_pp.h"


extern Adafruit_SSD1306 display;


ApClass ap;


ApClass::ApClass(void)
{

}

bool ApClass::ApppInit(void)
{
	bool ret = true;

	display.begin(SSD1306_SWITCHCAPVCC, 0x78);

    display.clearDisplay();
    display.display();
    HAL_Delay(5000);

    display.clearDisplay();
    display.display();

    //Display text
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0,8);
    display.printf("SJKIM DESIGNED");
    display.display();
    HAL_Delay(2000);

	return ret;
}

bool ApClass::ApppMain(void)
{
	bool ret = true;

	return ret;
}
