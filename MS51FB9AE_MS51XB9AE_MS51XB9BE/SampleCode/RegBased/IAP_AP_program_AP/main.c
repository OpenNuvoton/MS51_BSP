/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#define     DATA_START_ADDR     0x3800 

/************************************************
  * @brief     Main loop.
  * @param[in] None.
  * @return    None.
*************************************************/
void main (void) 
{
    uint8_t i, temp;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();

    printf ("\n Toggle P05 to low to start test ...");
    GPIO_LED_QUASI_MODE;

    for(i=0;i<128;i++)
       IAPDataBuf[i] =  i;
       
    while(GPIO_LED);
    Erase_APROM(DATA_START_ADDR,128);
    Erase_Verify_APROM(DATA_START_ADDR,128);
    Program_APROM(DATA_START_ADDR,128);
    Program_Verify_APROM(DATA_START_ADDR,128);

#if defined __C51__
    temp = Read_APROM_BYTE (DATA_START_ADDR+0x0A);
    printf ("\n\r Read out Value = 0x%bx", temp);
#elif defined __ICC8051__
    temp = Read_APROM_BYTE ((uint16_t __code *)(DATA_START_ADDR+0x09));
    printf ("\n\r Read out Value = 0x%hx", temp);
#elif defined __SDCC__
    temp = Read_APROM_BYTE ((uint16_t __code *)(DATA_START_ADDR+0x09));
    printf ("\n\r Read out Value = 0x%hx", temp);
#endif

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
