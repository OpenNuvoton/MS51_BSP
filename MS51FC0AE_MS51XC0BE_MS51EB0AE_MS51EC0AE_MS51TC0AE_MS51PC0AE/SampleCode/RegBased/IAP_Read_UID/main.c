/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"


void main(void)
{
	  uint8_t u8Counter;

/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;

  Read_UID();
  printf ("\n UID = ");
  for(u8Counter=0;u8Counter<12;u8Counter++)
  {
#if defined __C51__
        printf ("\r 0x%bX",UIDBuffer[u8Counter]);
#elif defined __ICC8051__
        printf ("\r 0x%hX",UIDBuffer[u8Counter]);
#elif defined __SDCC__
        printf (" 0x%hX",UIDBuffer[u8Counter]);
#endif
  }

  while(1);


}
