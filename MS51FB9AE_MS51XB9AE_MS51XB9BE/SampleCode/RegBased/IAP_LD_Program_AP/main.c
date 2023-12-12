/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/******************************
  * @brief     Main loop.
  * @param[in] None.
  * @return    None.
******************************/
void main (void) 
{
    uint8_t i;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r This code must run in LDROM !!");
    printf ("\n\r Enable LDROM in CONFIG and <BOOT FROM LDROM> !");
    printf ("\n\r ");
    printf ("\n\r Toggle P05 to low to start test ...");

    GPIO_LED_QUASI_MODE;
    while (GPIO_LED);

    for(i=0;i<128;i++)
      IAPDataBuf[i]=i;

    Erase_APROM(0x80,128);
    Erase_Verify_APROM(0x80,128);
    Program_APROM(0x80,128);
    Program_Verify_APROM(0x80,128);

    while(1);
}

