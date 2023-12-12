/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/******************************
  * @brief     Timer3 interrupt vector.
  * @param[in] None.
  * @return    None.
******************************/
#if defined __C51__
void Timer3_ISR(void)     interrupt  16

#elif defined __ICC8051__
#pragma vector=0x83                             /* interrupt 16 */
__interrupt void Timer3_ISR(void)

#elif defined __SDCC__
void Timer3_ISR(void)   __interrupt  (16)
#endif
{
  
    SFRS_TMP = SFRS;              /* for SFRS page */

    clr_T3CON_TF3;
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
    GPIO_LED_QUASI_MODE;

    Timer3_AutoReload_Interrupt_Initial(24,64000);
    ENABLE_GLOBAL_INTERRUPT;

    while(1);
}

