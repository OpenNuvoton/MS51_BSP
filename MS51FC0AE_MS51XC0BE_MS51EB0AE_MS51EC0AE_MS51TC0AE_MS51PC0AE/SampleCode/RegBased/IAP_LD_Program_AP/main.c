/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/***********************************************************************************************************/
/*  Step 1 Enable CONFIG to boot from LDROM , LDROM siez 2K                                                */
/*  Step 2 Define APROM buffer data loop from 0 to 0x7F                                                    */
/*  Step 3 erase / erase blank check / program / read verify APROM process                                 */
/***********************************************************************************************************/
void main (void) 
{
    uint8_t i;
/*Must boot from LDROM and LDROM size 4k */  

    for (i=0;i<128;i++)
    {
      IAPDataBuf[i]=i;
    }
/*if P3.5 trig to low start Write APROM */ 
/*Check with Nulink ICP please always keep P1.7 to high */
    GPIO_LED_QUASI_MODE;
    while(GPIO_LED);
    Erase_APROM(0x80,128);
    Erase_Verify_APROM(0x80,128);
    Program_APROM(0x80,128);
    Program_Verify_APROM(0x80,128);

    while(1);
}