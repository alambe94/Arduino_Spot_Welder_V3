/*
 * menu_page2.c
 *
 *  Created on: 14-Nov-2019
 *      Author: medprime
 */

#include "menu_main.h"

void Show_Page2_Comman()
    {

    char temp[10];

    ssd1306_Fill(Black);

    ssd1306_SetCursor(0, 5);
    ssd1306_WriteString(STR_Back, Font_7x10, White);

    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse_C, Font_7x10, White);
    ssd1306_SetCursor(80, 20);
    ssd1306_WriteString(STR_Auto_Value, Font_7x10, White);

    ssd1306_SetCursor(0, 35);
    ssd1306_WriteString(STR_Delay, Font_7x10, White);
    ssd1306_SetCursor(80, 35);
    itoa(Get_Auto_Pulse_Delay(), temp, 10);
    ssd1306_WriteString(temp, Font_7x10, White);

    ssd1306_SetCursor(0, 50);
    ssd1306_WriteString(STR_Duration, Font_7x10, White);
    ssd1306_SetCursor(80, 50);
    itoa(Get_Main_Pulse_Duration(), temp, 10);
    ssd1306_WriteString(temp, Font_7x10, White);

    ssd1306_UpdateScreen();
    }

void Show_Page2_Screen1()
    {

    ssd1306_SetCursor(0, 5);
    ssd1306_WriteString(STR_Back, Font_7x10, Black);

    ssd1306_UpdateScreen();
    }

void Show_Page2_Screen2()
    {

    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse_C, Font_7x10, Black);
    ssd1306_SetCursor(80, 20);
    ssd1306_WriteString(STR_Auto_Value, Font_7x10, Black);

    ssd1306_UpdateScreen();
    }

void Show_Page2_Screen3()
    {

    char temp[10];
    itoa(Get_Auto_Pulse_Delay(), temp, 10);

    ssd1306_SetCursor(0, 35);
    ssd1306_WriteString(STR_Delay, Font_7x10, Black);
    ssd1306_SetCursor(80, 35);
    ssd1306_WriteString(temp, Font_7x10, Black);

    ssd1306_UpdateScreen();

    }

void Show_Page2_Screen4()
    {

    char temp[10];
    itoa(Get_Main_Pulse_Duration(), temp, 10);

    ssd1306_SetCursor(0, 50);
    ssd1306_WriteString(STR_Duration, Font_7x10, Black);
    ssd1306_SetCursor(80, 50);
    ssd1306_WriteString(temp, Font_7x10, Black);

    ssd1306_UpdateScreen();
    }

void Show_Page2(uint8_t screen)
    {

    switch (screen)
	{
    break;
case 1:
    Show_Page2_Comman();
    Show_Page2_Screen1();
    break;
case 2:
    Show_Page2_Comman();
    Show_Page2_Screen2();
    break;
case 3:
    Show_Page2_Comman();
    Show_Page2_Screen3();
    break;
case 4:
    Show_Page2_Comman();
    Show_Page2_Screen4();
    break;
    }
}

void Execute_Page2_Element1(uint8_t button, int16_t count)
{
In_Loop = 0;
Change_Page(1);
}

void Execute_Page2_Element2(uint8_t button, int16_t count)
{

static uint8_t toggle = 0;

In_Loop = 0;

if (toggle)
    {
    toggle = 0;
    Disble_Auto_Welder();
    STR_Auto_Value = STR_OFF;
    }
else
    {
    toggle = 1;
    Enable_Auto_Welder();
    STR_Auto_Value = STR_ON;
    }
Show_Page2_Comman();
Show_Page2_Screen2();

}

void Execute_Page2_Element3(uint8_t button, int16_t count)
{

Set_Auto_Pulse_Delay(count + Get_Auto_Pulse_Delay());

if (button == 1)
    {
    In_Loop = 0;
    }

Show_Page2_Screen3();

}

void Execute_Page2_Element4(uint8_t button, int16_t count)
{

if (button == 1)
    {
    In_Loop = 0;
    }

Set_Main_Pulse_Duration(count + Get_Main_Pulse_Duration());

Show_Page2_Screen4();

}

void Execute_Page2_Element(uint8_t screen, uint8_t button, int16_t count)
{

switch (screen)
    {
case 1:
    Execute_Page2_Element1(button, count);
    break;
case 2:
    Execute_Page2_Element2(button, count);
    break;
case 3:
    Execute_Page2_Element3(button, count);
    break;
case 4:
    Execute_Page2_Element4(button, count);
    break;
    }
}