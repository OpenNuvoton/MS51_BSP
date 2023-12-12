/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

uint8_t PinIntVector;

/**
  * @brief     Pin interrupt vector.
  * @param[in] Vector 0x3B (7).
  * @return    None.
*/
#if defined __C51__
void PinInterrupt_ISR (void) interrupt 7

#elif defined __ICC8051__
#pragma vector=0x3B
__interrupt void Pin_INT_ISR(void)

#elif defined __SDCC__
void PinInterrupt_ISR (void) __interrupt (7)
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */
  
    SFRS = 0;
    switch(PIF)
    {
      case (SET_BIT0): PinIntVector = SET_BIT0; PIF&=CLR_BIT0; break;
      case (SET_BIT3): PinIntVector = SET_BIT3; PIF&=CLR_BIT3; break;
      default: break;
    }

    if (SFRS_TMP)                 /* for SFRS page */
    {
      ENABLE_SFR_PAGE1;
    }
}

/**
  * @brief     Main loop.
  * @param[in] None.
  * @return    None.
*/
void main (void) 
{
  /* UART0 initial for printf */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n PIT test start!");
  /* Disable BOD for power down current */
    BOD_DISABLE;

  /* PIT initial setting */
    P00_QUASI_MODE;
    P03_INPUT_MODE;

    ENABLE_INT_PORT0;
    ENABLE_BIT0_FALLINGEDGE_TRIG;
    ENABLE_BIT3_BOTHEDGE_TRIG;
    ENABLE_PIN_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;

    while(1)
    {
        switch(PinIntVector)
        {
          case (SET_BIT0): printf("\n PIT0 interrupt!"); PinIntVector&=CLR_BIT0; break;
          case (SET_BIT3): printf("\n PIT3 interrupt!"); PinIntVector&=CLR_BIT2; break;
          default: break;
        }
    }
}
