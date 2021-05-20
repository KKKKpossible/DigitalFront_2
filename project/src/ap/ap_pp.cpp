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

//	ApppOLEDInit();

	return ret;
}

bool ApClass::ApppMain(void)
{
	bool ret = true;

    static uint32_t mil = millis();
    //Display text

    if(millis() - mil > 500)
    {
        mil = millis();

        static uint16_t count = 0;

        display.clearDisplay();
        display.setTextSize(3);
        display.setTextColor(WHITE);
        display.setCursor(0,8);
        char text_buff[20] = {0, };
        sprintf(text_buff, "%d", count);

        display.printf((const char*)text_buff);
        display.display_1106();

        count++;

        if(count > 1 << 19)
        {
            count = 0;
        }

//        ApppOLEDOperate();

    }

	return ret;
}

bool ApClass::ApppOLEDInit(void)
{
    bool ret = true;

    display.begin(SSD1306_SWITCHCAPVCC, 0x78);

    if(MonitorRead(DEF_MONITOR_FAULT_0) && (1 << DEF_FAULT_OLED) != 0)
    {
        ret = false;

        return ret;
    }

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
    HAL_Delay(5000);

    display.clearDisplay();
    display.display();
    HAL_Delay(2000);

    return ret;
}

bool ApClass::ApppOLEDOperate(void)
{
    bool ret = true;

    if(MonitorRead(DEF_MONITOR_FAULT_0) && (1 << DEF_FAULT_OLED) != 0)
    {
        static uint16_t init_count = 0;

        if(init_count > 100)
        {
            init_count = 0;
            ApppOLEDInit();
        }
        else
        {
            init_count++;
        }

        ret = false;
    }
    else
    {
        static uint16_t count = 0;

        display.setTextSize(3);
        display.setTextColor(WHITE);
        display.setCursor(0,8);
        char text_buff[20] = {0, };
        sprintf(text_buff, "%d", count);

        display.printf((const char*)text_buff);
        display.display();

        count++;

        if(count > 1 << 19)
        {
            count = 0;
        }
    }

    return ret;
}
