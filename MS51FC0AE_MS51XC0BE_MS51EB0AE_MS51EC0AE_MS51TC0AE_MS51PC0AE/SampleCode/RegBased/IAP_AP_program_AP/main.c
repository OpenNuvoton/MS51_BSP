/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

//---------------------------------------------------------------
// Following define by customer
// Please confirm the start addresss not over your code size
//---------------------------------------------------------------
#define     DATA_SIZE           4096
#define     DATA_START_ADDR     0x3800


void main (void) 
{
    uint8_t i;
    for(i=0;i<128;i++)
    {
       IAPDataBuf[i] = i;
    }

    GPIO_LED_QUASI_MODE;
    while (GPIO_LED);
  
    Erase_APROM(0x4700,1024);
    Erase_Verify_APROM(0x4700,1024);
    Program_APROM(0x4700,128);
    Program_Verify_APROM(0x4700,128);

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
