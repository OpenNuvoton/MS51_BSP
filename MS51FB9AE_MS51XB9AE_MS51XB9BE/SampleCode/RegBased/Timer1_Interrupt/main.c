/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"


/******************************
  * @brief     Main loop.
  * @param[in] None.
  * @return    None.
******************************/
#if defined __C51__
void Timer1_ISR (void) interrupt 3             // vector=0x1B

#elif defined __ICC8051__
#pragma vector=0x1B                            //* interrupt 3
__interrupt void Timer1_ISR(void)

#elif defined __SDCC__
void Timer1_ISR (void) __interrupt (3)         // vector=0x1B
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */
  /* following setting for reload Timer 0 counter, this is must for next time*/
    TH1 = TH1TMP;
    TL1 = TL1TMP;
  /* following clear flag is necessary for next time */
    clr_TCON_TF1;
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

    Timer1_AutoReload_Interrupt_Initial(24,6400);
    ENABLE_GLOBAL_INTERRUPT;

    while(1);
}

