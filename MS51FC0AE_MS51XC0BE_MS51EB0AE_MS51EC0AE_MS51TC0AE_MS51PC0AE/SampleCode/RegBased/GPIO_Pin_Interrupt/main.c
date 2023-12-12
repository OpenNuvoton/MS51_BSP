/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

uint8_t PinIntFlag;

/******************************************************************************
Pin interrupt subroutine.
******************************************************************************/
#if defined __C51__
void PinInterrupt_ISR (void) interrupt 7
#elif defined __ICC8051__
#pragma vector=0x3B
__interrupt void PIT_ISR(void)
#elif defined __SDCC__
void PinInterrupt_ISR (void) __interrupt (7)
#endif
{
    PUSH_SFRS;

    SFRS = 0;
    switch(PIF)
    {
      case (SET_BIT0): PinIntFlag = SET_BIT0; PIF&=CLR_BIT0; break;
      case (SET_BIT2): PinIntFlag = SET_BIT2; PIF&=CLR_BIT2; break;
      default: break;
    }

    POP_SFRS;
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
  /* UART0 initial for printf */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n PIT test start!");
  /* Disable BOD for power down current */
    BOD_DISABLE;

  /* PIT initial setting */
    P13_INPUT_MODE;
    P13_PULLUP_ENABLE;
    P32_INPUT_MODE;
    P32_PULLDOWN_ENABLE;
    P35_QUASI_MODE;
    P35 = 1;

    ENABLE_PIT0_P13_LOWLEVEL;
    ENABLE_PIT2_P32_BOTHEDGE;
    ENABLE_PIN_INTERRUPT;                   // Enable pin interrupt
    ENABLE_GLOBAL_INTERRUPT;                // global enable bit
  /* mail loop in power down and wakeup check flag to print */
	
    while(1)
    {
       set_PCON_PD;
       _nop_();
       _nop_();

      switch(PinIntFlag)
      {
        case (SET_BIT0): printf("\n PIT0 interrupt!"); PinIntFlag&=CLR_BIT0; break;
        case (SET_BIT2): printf("\n PIT2 interrupt!"); PinIntFlag&=CLR_BIT2; break;
        default: break;
      }
    }
}


