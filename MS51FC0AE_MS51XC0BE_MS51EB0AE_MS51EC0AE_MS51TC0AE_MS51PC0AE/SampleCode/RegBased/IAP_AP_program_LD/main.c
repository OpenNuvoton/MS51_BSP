/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

void main (void) 
{
    uint8_t i;

  /* IAP data buffer size is 128 since each page of MS51 is 128 byte*/
    for(i=0;i<128;i++)
    {
      IAPDataBuf[i]=i;
    }

    /* Only when P3.5 to low to program LDROM process*/
    GPIO_LED_QUASI_MODE;
    while (GPIO_LED);
    
    
    Erase_LDROM(0,128);
    Erase_Verify_LDROM(0,128);
    Program_LDROM(0,128);
    Program_Verify_LDROM(0,128);

    while(1);

}

