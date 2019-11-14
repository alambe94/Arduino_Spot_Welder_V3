/*
 * menu_page1.c
 *
 *  Created on: 14-Nov-2019
 *      Author: medprime
 */

#include "menu_main.h"

extern uint8_t Foot_Switchn_Flag;

void Show_Page1_Screen1()
    {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Back, Font_11x18, Black);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse, Font_11x18, White);
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, White);
    ssd1306_UpdateScreen();
    }


void Show_Page1_Screen2()
    {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Back, Font_11x18, White);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse, Font_11x18, Black);
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, White);
    ssd1306_UpdateScreen();
    }

void Show_Page1_Screen3()
    {

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Back, Font_11x18, White);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Auto_Pulse, Font_11x18, White);
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, Black);
    ssd1306_UpdateScreen();

    }

void Show_Page1_Screen4()
    {

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Auto_Pulse, Font_11x18, White);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, White);
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString(STR_Shrt_Pulse, Font_11x18, Black);
    ssd1306_UpdateScreen();

    }

void Show_Page1(uint8_t screen)
    {

    switch (screen)
	{
    case 1:
	Show_Page1_Screen1();
	break;
    case 2:
	Show_Page1_Screen2();
	break;
    case 3:
	Show_Page1_Screen3();
	break;
    case 4:
	Show_Page1_Screen4();
	break;
	}
    }

void Execute_Page1_Element1(uint8_t button, int16_t count)
    {

    char temp[10];

    int16_t bat_voltage;

    if (In_Loop)
	{

        if(button == 1)
            {
            In_Loop = 0; // exit loop
            }

	Set_Main_Pulse_Duration(count + Get_Main_Pulse_Duration());


	HAL_ADC_PollForConversion(&hadc, 10);
	bat_voltage = HAL_ADC_GetValue(&hadc)*13;

	if(bat_voltage < Get_Batt_Alarm())
	    {
	    //Disble_Welder();
	    }

	if (Foot_Switchn_Flag)
	    {
	    Foot_Switchn_Flag = 0;

	    if (Get_Welder_Status())
		{
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Pulse:", Font_11x18, White);
		itoa(Get_Main_Pulse_Duration(), temp, 10);
		ssd1306_WriteString(temp, Font_11x18, White);
		ssd1306_WriteString("ms", Font_11x18, White);
		ssd1306_UpdateScreen();

		HAL_GPIO_WritePin(Gate_Driver_GPIO_Port, Gate_Driver_Pin,
			GPIO_PIN_SET);
		HAL_Delay(Get_Main_Pulse_Duration());
		HAL_GPIO_WritePin(Gate_Driver_GPIO_Port, Gate_Driver_Pin,
			GPIO_PIN_RESET);
		HAL_Delay(1000);
		}
	    else
		{
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Battery Low", Font_7x10, White);
		ssd1306_SetCursor(0, 15);
		ssd1306_WriteString("Under Voltage", Font_7x10, White);
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString("Lock Out", Font_7x10, White);
		ssd1306_SetCursor(0, 45);
		ssd1306_WriteString("Reboot Welder", Font_7x10, White);
		ssd1306_UpdateScreen();
		HAL_Delay(2000);
		}
	    }

	ssd1306_Fill(Black);

	ssd1306_SetCursor(45, 0);
	itoa(Get_Main_Pulse_Duration(), temp, 10);
	ssd1306_WriteString(temp, Font_11x18, White);
	ssd1306_WriteString("ms", Font_11x18, White);

	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString("Battery:", Font_7x10, White);
	ssd1306_SetCursor(75, 20);
	itoa(bat_voltage, temp, 10);
	ssd1306_WriteString(temp, Font_7x10, White);
	ssd1306_WriteString("mV", Font_7x10, White);

	ssd1306_SetCursor(0, 35);
	ssd1306_WriteString("Tot Welds:", Font_7x10, White);
	ssd1306_SetCursor(75, 35);
	ssd1306_WriteString("125", Font_7x10, White);

	ssd1306_SetCursor(0, 50);
	ssd1306_WriteString(STR_Auto, Font_7x10, White);
	ssd1306_WriteString(STR_Space, Font_7x10, White);
	ssd1306_WriteString(STR_Auto_Value, Font_7x10, White);

	ssd1306_SetCursor(100, 50);
	ssd1306_WriteString(">>", Font_7x10, White);

	ssd1306_UpdateScreen();

	}
    }

void Execute_Page1_Element2(uint8_t button, int16_t count)
    {
    In_Loop = 0;
    Change_Page(2);
    }

void Execute_Page1_Element3(uint8_t button, int16_t count)
    {

    char temp[10];

    if (In_Loop)
	{

	if (button == 1)
	    {
	    In_Loop = 0;
	    }

	Set_Batt_Alarm(Get_Batt_Alarm() + (count * 10));

	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(STR_Batt_Alarm, Font_11x18, White);

	ssd1306_SetCursor(0, 20);
	itoa(Get_Batt_Alarm(), temp, 10);
	ssd1306_WriteString(temp, Font_11x18, White);
	ssd1306_WriteString(" mV", Font_11x18, White);
	ssd1306_UpdateScreen();

	}

    }


void Execute_Page1_Element4(uint8_t button, int16_t count)
    {

    char temp[10];



    Set_Short_Pulse_Duration(Get_Short_Pulse_Duration() + (count));

    if (button == 1)
	{
	In_Loop = 0; //exit loop
	}

    ssd1306_Fill(Black);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(STR_Shrt_Pulse, Font_11x18, White);

    ssd1306_SetCursor(0, 20);
    itoa(Get_Short_Pulse_Duration(), temp, 10);
    ssd1306_WriteString(temp, Font_11x18, White);
    ssd1306_WriteString(" ms ", Font_11x18, White);
    ssd1306_UpdateScreen();

    }

void Execute_Page1_Element(uint8_t screen, uint8_t button, int16_t count)
    {
    switch (screen)
	{
    case 1:
	Execute_Page1_Element1(button, count);
	break;
    case 2:
	Execute_Page1_Element2(button, count);
	break;
    case 3:
	Execute_Page1_Element3(button, count);
	break;
    case 4:
	Execute_Page1_Element4(button, count);
	break;
	}
    }