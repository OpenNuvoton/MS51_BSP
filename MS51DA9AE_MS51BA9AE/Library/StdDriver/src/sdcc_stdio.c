/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
/* Program Description:                                                                                    */
/*                                                                                                         */
/* This set of functions includes putchar (), getchar ()                                                   */
/* functionality for the SDCC compiler.                                                                    */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"


//-----------------------------------------------------------------------------
// putchar
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : character to send to UART
//
// This function outputs a character to the UART.
//-----------------------------------------------------------------------------
#if 0
char putchar (char c)
{
    while (!TI_1);  /* wait until transmitter ready */
    TI_1 = 0;
    SBUF_1 = c;      /* output character */
    return (c);
}
#else
int putchar (int c)  {
  while (!TI);
  TI = 0;
  return (SBUF = c);
}
#endif

//-----------------------------------------------------------------------------
// getchar
//-----------------------------------------------------------------------------
//
// Return Value : character received from UART
// Parameters   : None
//
// This function returns a character from the UART.
//-----------------------------------------------------------------------------
char getchar (void)
{
   char c;

   while (!RI);
   c = SBUF;
   RI = 0;

   return c;
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
