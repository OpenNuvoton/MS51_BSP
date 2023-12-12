/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

BIT t2captureflag;
uint8_t captemph,captempl;

/******************************
  * @brief     Capture interrupt vector.
  * @param[in] None.
  * @return    None.
******************************/
#if defined __C51__
void Capture_ISR (void) interrupt 12            // Vector @  0x63

#elif defined __ICC8051__
#pragma vector=0x63                             // Vector number 12
__interrupt void Capture_ISR(void)

#elif defined __SDCC__
void Capture_ISR (void) __interrupt (12)        // Vector @  0x63
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */

    SFRS = 1;
    if (CAPCON0&SET_BIT0)
    {
       captemph = C0H;
       captempl = C0L;
       clr_CAPCON0_CAPF0;
    }
    else if (CAPCON0&SET_BIT2)
    {
       captemph = C2H;
       captempl = C2L;
       clr_CAPCON0_CAPF2;
    }
    t2captureflag = 1;

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
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n ML51 series capture demo." );

    P03_QUASI_MODE;
    TIMER2_CAP0_CAPTURE_MODE;
    IC5_P03_CAP0_RISINGEDGE_CAPTURE;

    P11_QUASI_MODE;                          //Define P11 as IC2 input pin.
    TIMER2_Capture(IC2,CaptureEither,7);

    TIMER2_Capture_Interrupt(ENABLE);
    Global_Interrupt(ENABLE);

    while(1)
    {
      if (t2captureflag)
      {
          t2captureflag = 0;
          SFRS=0;
#if defined __C51__
          printf ("\n capture high byte = 0x%BD", captemph);
          printf ("\n capture low byte = 0x%BD", captempl);
#elif defined __ICC8051__
          printf ("\n capture high byte = 0x%hx", captemph);
          printf ("\n capture low byte = 0x%hx", captempl);
#elif defined __SDCC__
          printf ("\n capture high byte = 0x%hx", captemph);
          printf ("\n capture low byte = 0x%hx", captempl);
#endif

      }
    }
}
