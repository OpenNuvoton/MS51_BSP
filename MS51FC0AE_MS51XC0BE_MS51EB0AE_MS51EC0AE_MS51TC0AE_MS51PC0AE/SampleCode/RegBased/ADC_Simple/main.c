/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

void main (void) 
{
    uint16_t temp;

  /* Initial UART0 for printf */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
  
    ENABLE_ADC_CH0;

    while(1)
    {
      Timer2_Delay(24000000,128,300,1000);;
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                  // ADC start trig signal
      while(ADCF == 0);
      temp = ADCRH<<4;
      temp += ADCRL&0x0F;
      printf ("\n ADC Value = 0x%02X", temp);
      P35 ^= 1;
    }
}


