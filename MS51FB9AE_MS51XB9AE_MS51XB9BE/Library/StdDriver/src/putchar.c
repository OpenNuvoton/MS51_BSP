/***********************************************************************/
/*  This file is part of the C51 Compiler package                      */
/*  Copyright KEIL ELEKTRONIK GmbH 1990 - 2002                         */
/***********************************************************************/
/*                                                                     */
/*  PUTCHAR.C:  This routine is the general character output of C51.   */
/*  You may add this file to a uVision2 project.                       */
/*                                                                     */
/*  To translate this file use C51 with the following invocation:      */
/*     C51 PUTCHAR.C <memory model>                                    */
/*                                                                     */
/*  To link the modified PUTCHAR.OBJ file to your application use the  */
/*  following Lx51 invocation:                                         */
/*     Lx51 <your object file list>, PUTCHAR.OBJ <controls>            */
/*                                                                     */
/***********************************************************************/
#include "numicro_8051.h"

/*
 * putchar (mini version): outputs charcter only
 */
#if 0
char putchar (char c)
{
		while (!TI_1);  /* wait until transmitter ready */
		TI_1 = 0;
		SBUF_1 = c;      /* output character */
		return (c);
}
#endif

#if defined __C51__
char putchar (char c)
#elif defined __ICC8051__
int putchar (int c) 
#endif
{
#if 1 
  /* For UART 0 */
  UART_Send_Data(UART0,c);
  return (c);
#endif
#if 0
  /* For UART 1 */
  UART_Send_Data(UART1,c);
  return (c);
#endif
}