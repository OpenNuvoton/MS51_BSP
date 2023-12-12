/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"


void main (void)
{
    /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");

    ALL_GPIO_QUASI_MODE;
    P12_PUSHPULL_MODE;
    P13_INPUT_MODE;

    while(1)
    {
      P0 = ~P0;
      P1 = ~P1;
      P30 ^= 1;
      P1 |= SET_BIT2;
      if (!(P1&SET_BIT3))
      {
        CALL_NOP;
      }
      Timer2_Delay(24000000,4,200,1000);

      P1 &= CLR_BIT2;
      if (P1&SET_BIT3)
      {
        CALL_NOP;
      }
      Timer2_Delay(24000000,4,200,1000);
    }
}





