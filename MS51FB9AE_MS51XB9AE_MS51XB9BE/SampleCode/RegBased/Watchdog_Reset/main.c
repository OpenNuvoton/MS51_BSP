/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"



/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main (void)
{
    uint8_t   ct;

	WDT_Clear();
    WDT_Open(1024);

	GPIO_LED_QUASI_MODE;
/* Note WDT timer base is LIRC 10Khz*/
	MODIFY_HIRC(HIRC_24);
	Enable_UART0_VCOM_printf_24M_115200();
    printf("\n\r  Test start MCU reset ");
    WDT_Clear();

    Read_CONFIG();
    SFRS = 0;
    printf ("\n\r Now config value is :   ");
    for(ct=0;ct<5;ct++)
    {
    	SFRS = 0;
    	printf ("\r 0x%X", IAPCFBuf[ct]);
        WDT_Clear();
    }
    SFRS = 0;
    printf("\n\r  WDT Reset enabled in CONFIG ");
    WDT_Clear();

    printf ("\n\r ");
    printf("\n\r  P32 connect to VDD, WDT not reset ");
    WDT_Clear();
//--------------------------------------------------------
//Warning:
//Pleaes always check CONFIG WDT disable first 
//only when WDT reset disable, WDT use as pure timer
//--------------------------------------------------------
    while (GPIO_LED)
    {
        WDT_Clear();
    }
    while(1);

}

