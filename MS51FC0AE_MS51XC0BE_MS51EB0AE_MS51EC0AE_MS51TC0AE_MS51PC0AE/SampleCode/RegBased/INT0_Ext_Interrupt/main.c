/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/******************************
  * @brief     External pin interrupt INT0 subroutin.
  * @param[in] None.
  * @return    None.
******************************/
#if defined __C51__
void INT0_ISR(void) interrupt 0          // Vector @  0x03
#elif defined __ICC8051__
#pragma vector=0x03
__interrupt void INT0_ISR(void)
#elif defined __SDCC__
void INT0_ISR(void) __interrupt (0)          // Vector @  0x03
#endif
{
    PUSH_SFRS;              /* for SFRS page */

    clr_TCON_IE0;          //clr int flag wait next falling edge

    POP_SFRS;
}


void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    P30_QUASI_MODE;                      //setting INT0 pin P3.0 as Quasi mode with internal pull high  
    P30 = 1;
    INT0_FALLING_EDGE_TRIG;              //setting trig condition level or edge
    ENABLE_INT0_INTERRUPT;                         //INT0_Enable;
    ENABLE_GLOBAL_INTERRUPT;            //Global interrupt enable
    while(1);
}



