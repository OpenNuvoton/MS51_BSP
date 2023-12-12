/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

BIT   wdtintflag;
/************************************************************************************************************
*    WDT interrupt sub-routine
************************************************************************************************************/
#if defined __C51__
void WDT_ISR(void) interrupt 10          // Vector @  0x53

#elif defined __ICC8051__
#pragma vector=0x53
__interrupt void WDT_ISR (void)

#elif defined __SDCC__
void WDT_ISR(void) __interrupt (10)          // Vector @  0x53
#endif
{
PUSH_SFRS;
   CLEAR_WDT_INTERRUPT_FLAG;
  /* Config Enable WDT reset and not clear couter trig reset */
    GPIO_LED ^= 1;
    wdtintflag = 1;
POP_SFRS;
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    uint8_t ct; 
/* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");

    GPIO_LED_QUASI_MODE;
/*--------------------------------------------------------
*Warning:
*Pleaes always check CONFIG WDT disable first 
*only when WDT reset disable, WDT use as pure timer
--------------------------------------------------------*/
    WDT_TIMEOUT_1_6S;                     /* Setting WDT time out */
    WDT_RUN_IN_POWERDOWN_ENABLE;           /* WDT run in POWER DOWM mode setting if needed */
    ENABLE_WDT_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    WDT_COUNTER_RUN;                       /* WDT start to run */

    for(ct=0;ct<4;ct++)
    {
      WDT_Clear();
      Timer0_Delay(24000000,300,1000);
      GPIO_LED ^= 1;
    }
    while (1)
    {
      if (wdtintflag);
      {
        printf (" \n\r WDT interrupt ! \n\r");
        wdtintflag = 0;
        set_PCON_PD;
      }
    }
}
