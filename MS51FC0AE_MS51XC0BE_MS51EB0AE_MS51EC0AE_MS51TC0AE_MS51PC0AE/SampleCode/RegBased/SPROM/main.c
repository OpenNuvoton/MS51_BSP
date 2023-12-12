/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"
#include "sprom.h"

void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    
    ENABLE_SPROM;             //Enable SPROM memory mapping only for check SPROM in memory window

#if defined __C51__
    printf ("\n protect bit is 0x%bX", lockdata);
#elif defined __ICC8051__
    printf ("\n protect bit is 0x%hx", lockdata);
#elif defined __SDCC__
    printf ("\n protect bit is 0x%hx", lockdata);
#endif

    while(1)
    {
      SPROM_CODE();
#if defined __C51__
      printf ("\n SPTEMP= 0x%bX", SPTEMP);
#elif defined __ICC8051__
      printf ("\n SPTEMP= 0x%hx", SPTEMP);
#elif defined __SDCC__
      printf ("\n SPTEMP= 0x%hx", SPTEMP);
#endif

      Timer0_Delay(24000000,300,1000);
    }
}
