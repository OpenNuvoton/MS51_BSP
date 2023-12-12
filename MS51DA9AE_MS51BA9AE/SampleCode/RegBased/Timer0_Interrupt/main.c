/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#if defined __C51__
void Timer0_ISR (void) interrupt 1              // vector=0x0B 

#elif defined __ICC8051__
#pragma vector=0x0B                             // Interrupt 1 
__interrupt void Timer0_ISR(void)

#elif defined __SDCC__
void Timer0_ISR (void) __interrupt (1)          // vector=0x0B
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */
    SFRS = 0;
/* following setting for reload Timer 0 counter */
    TH0 = TH0TMP;
    TL0 = TL0TMP;
/* following clear flag for next interrupt */
    clr_TCON_TF0;
    GPIO_LED ^= 1;
    if (SFRS_TMP)                 /* for SFRS page */
    {
      ENABLE_SFR_PAGE1;
    }
}


/******************************
  * @brief     Main loop.
  * @param[in] None.
  * @return    None.
******************************/
void main (void)
{

    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;

    Timer0_AutoReload_Interrupt_Initial(24,32000);
    ENABLE_GLOBAL_INTERRUPT;

    while(1);
}

