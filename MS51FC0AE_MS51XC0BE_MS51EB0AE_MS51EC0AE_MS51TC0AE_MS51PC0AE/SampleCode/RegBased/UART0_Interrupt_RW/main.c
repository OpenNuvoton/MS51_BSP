/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/* UART0 interrupt vector demo */
#if defined __C51__
void Serial_ISR(void)  interrupt 4
#elif defined __ICC8051__
#pragma vector=0x23
__interrupt void SerialPort0_ISR(void)
#elif defined __SDCC__
void Serial_ISR(void) __interrupt (4)
#endif
{
    PUSH_SFRS;
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
    POP_SFRS;
}  

/**
 * @brief       Main loop
 * @param       None
 * @return      None
 * @details     UART4 printf send data.
 */
 void main(void)
{

/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24); 
    P06_PUSHPULL_MODE;
    P07_INPUT_MODE;
    UART_Open(24000000,UART0_Timer3,115200);

    ENABLE_UART0_INTERRUPT;                                   /* Enable UART0 interrupt */
    ENABLE_GLOBAL_INTERRUPT;                                  /* Global interrupt enable */
  
/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart0_receive_flag)
    {
      uart0_receive_flag = 0;
      DISABLE_UART0_INTERRUPT;
      UART_Send_Data(UART0,uart0_receive_data);
      ENABLE_UART0_INTERRUPT;
    }
  }
}