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
#if 0  //origin putchar
char putchar (char c)
{
    while (!TI_1);  /* wait until transmitter ready */
    TI_1 = 0;
    SBUF_1 = c;      /* output character */
    return (c);
}
#endif
#if 0
int putchar (int c)       /* for UART0 */
{
    UART_Send_Data(UART0,c);
	return (c);
}
#endif
#if 1
int putchar (int c)       /* for UART1 */
{
	UART_Send_Data(UART1,c);
	return (c);
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
