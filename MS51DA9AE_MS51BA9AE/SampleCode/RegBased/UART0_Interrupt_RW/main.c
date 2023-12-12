/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#if defined __C51__
void Serial_ISR(void)  interrupt 4

#elif defined __ICC8051__
#pragma vector=0x23
__interrupt void SerialPort0_ISR(void)

#elif defined __SDCC__
void Serial_ISR(void) __interrupt (4)
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */

    if (RI)
    {
        uart0_receive_flag = 1;
        uart0_receive_data = SBUF;
        clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }

    if (TI)
    {
        if (!PRINTFG)
        {
            TI = 0;
        }
    }

    if (SFRS_TMP)                 /* for SFRS page */
    {
      ENABLE_SFR_PAGE1;
    }
}


/************************************************************************************************************/
/*  Main function                                                                                           */
/************************************************************************************************************/
 void main(void)
{
    GPIO_LED_QUASI_MODE;
/* Modify HIRC to 24MHz for UART baud rate */
    MODIFY_HIRC(HIRC_24);
    P06_QUASI_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_INTERRUPT;                                   /* Enable UART0 interrupt */
    ENABLE_GLOBAL_INTERRUPT;                                  /* Global interrupt enable */
  
/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart0_receive_flag)
    {
      GPIO_LED ^= 1;
      UART_Send_Data(UART0,uart0_receive_data);
      uart0_receive_flag = 0;
    }
  }
}
