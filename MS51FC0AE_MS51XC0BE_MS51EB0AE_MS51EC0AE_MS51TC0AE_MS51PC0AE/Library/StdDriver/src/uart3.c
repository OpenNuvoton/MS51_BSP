/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

uint8_t uart3rvbuffer;
BIT uart3rvflag;

/**
 * @brief       SC1 interrupt vector
 * @param       None
 * @return      None
 * @details     Store receive data.
 */
#if 0
void SC1_ISR(void) interrupt 22          // Vector @  0x9B
{
    PUSH_SFRS;
        SFRS = 2;
        uart3rvflag = 1;
        uart3rvbuffer = SC1DR;
    POP_SFRS;
}
#endif

/**
 * @brief       UART3 transfer data without interrupt 
 * @param       u32SysClock , define Fsys value(value)
 * @param       u32Baudrate, Define baudrate (value)
 * @return      none
 * @details     none
 * @example:    UART3_Open(24000000,115200)
 */ 
void UART3_Open(uint32_t u32SysClock, uint32_t u32Baudrate)
{
    set_SC1CR0_SCEN;         /* Enable SC module */
    set_SC1CR1_UARTEN;       /* set as UART mode */
    set_SC1CR1_CLKKEEP;      
    clr_SC1CR0_CONSEL;       /* clr CONSEL and AUTOCEN*/
    clr_SC1CR0_AUTOCEN;
    SC1ETURD0 = LOBYTE(u32SysClock/8/u32Baudrate-1);  /* define baud rate low byte */
    SC1ETURD1 &= 0xF0;                                /* define baud rate high byte */
    SC1ETURD1 |= (HIBYTE(u32SysClock/8/u32Baudrate-1))&0x0F; 
    set_SC1CR1_PBOFF;     //parity bit disable
    SC1CR1&=0xCF;        //datalegth 8bit
    set_SC1CR0_NSB;      //stop bit = 1bit
  }

	/**
 * @brief       UART3 Parity Enable / Disable Setting 
 * @param       Enable / Disable
 * @return      none
 * @details     none
 * @example:    UART3_Parity(ENBALE,SCPODD)
 */ 
void UART3_Parity(uint8_t u8PStatus, uint8_t u8PEvenOdd)
{
    SFRS_TMP = SFRS;
    if (u8PStatus==DISABLE)
      {
        set_SC1CR1_PBOFF;
      }
      else if (u8PStatus==ENABLE)
      {
        clr_SC1CR1_PBOFF;
        if (u8PEvenOdd==SC1PEVEN)
        {
          clr_SC1CR1_OPE;
        }
        else if (u8PEvenOdd==SC1PODD)
        {
          set_SC1CR1_OPE;
        }
      }
    SFRS = SFRS_TMP;
}
/**
 * @brief       UART3 receive data without interrupt 
 * @param       baudrate value
 * @return      received data
 * @details     none
 * @example:    temp = UART3_Receive_Data()
 */ 
uint8_t UART3_Receive_Data(void)
{
    uint8_t c;

    clr_SC1CR0_RXOFF;
    while((SC1TSR&SET_BIT1)==SET_BIT1);
    c = SC1DR;
  
    return (c);
}

/**
 * @brief       UART3 transfer data without interrupt 
 * @param       baudrate value
 * @return      none
 * @details     none
 * @example:    UART3_Send_Data(0x55)
 */ 
void UART3_Send_Data(uint8_t c)
{
    clr_SC1CR0_TXOFF;
    SC1DR = c;
    while(!(SC1TSR&SET_BIT3));
    clr_SC1CR0_TXOFF;
}

