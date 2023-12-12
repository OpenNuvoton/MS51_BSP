/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

BIT bodflag;

#if defined __C51__
void BOD_ISR (void) interrupt 8           // Vector @  0x43
#elif defined __ICC8051__
#pragma vector=0x43
__interrupt void BOD_ISR(void)
#elif defined __SDCC__
void BOD_ISR (void) __interrupt (8)           // Vector @  0x43
#endif
{
    clr_CHPCON_IAPEN; 
    clr_BODCON0_BOF;
    bodflag=0;
}

//----------------------------------------------------------------------------------------------//
void main (void)
{
/* As defaut all multi function define as GPIO */ 
  ALL_GPIO_QUASI_MODE;

  BOD_Open(Enable, VBOD_2_7, BOD_Reset_Disable);
  BOD_LowPower(LPBOD_Mode_3);
  BOD_Interrupt(Enable);
  ENABLE_GLOBAL_INTERRUPT;
  while(1)
  {
     P1=~P1;
     _delay_();
     if (bodflag)
     {
       while (1)
         P1=~P1;
     }
  }
}



