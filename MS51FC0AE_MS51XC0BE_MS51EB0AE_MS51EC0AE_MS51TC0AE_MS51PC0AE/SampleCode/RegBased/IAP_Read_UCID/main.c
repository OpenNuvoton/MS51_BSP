/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/***********************/
/* main loop           */
/***********************/ 
void main(void)
{
  uint8_t u8Counter;
	
  
/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
  
  
  Read_UCID();
  printf ("\n UCID = ");
  for(u8Counter=0;u8Counter<12;u8Counter++)
  {
#if defined __C51__
	    printf ("\r 0x%bX",UCIDBuffer[u8Counter]);
#elif defined __ICC8051__
	    printf ("\r 0x%hX",UCIDBuffer[u8Counter]);
#elif defined __SDCC__
	    printf ("\r 0x%hX",UCIDBuffer[u8Counter]);
#endif
  }
  while(1);


}