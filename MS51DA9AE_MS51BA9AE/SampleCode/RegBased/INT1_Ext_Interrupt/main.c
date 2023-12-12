/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/******************************
  * @brief     External pin interrupt INT0 subroutine
  * @param[in] None.
  * @return    None.
******************************/
#if defined __C51__
void INT0_ISR(void) interrupt 2          // Vector @  0x03

#elif defined __ICC8051__
#pragma vector=0x13
__interrupt void INT1_ISR(void)

#elif defined __SDCC__
void INT0_ISR(void) __interrupt (2)          // Vector @  0x03
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */
  
    clr_TCON_IE1;          //clr int flag wait next falling edge

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
    P17_QUASI_MODE;                      //setting INT0 pin P1.7 as Quasi mode with internal pull high  
    P17 = 1;
    INT1_LOW_LEVEL_TRIG;                //setting trig condition level or edge
    set_IE_EX1;                         //INT0_Enable;
    ENABLE_GLOBAL_INTERRUPT;            //Global interrupt enable
    while(1);
}



