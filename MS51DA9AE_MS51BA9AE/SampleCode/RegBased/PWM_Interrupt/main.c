/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/******************************
  * @brief     PWM interrupt subroutine.
  * @param[in] None.
  * @return    None.
******************************/
#if defined __C51__
void PWM_ISR (void) interrupt 13

#elif defined __ICC8051__
#pragma vector=0x6B
__interrupt void INT0_ISR(void)

#elif defined __SDCC__
void PWM_ISR (void) __interrupt (13)
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */
  
    clr_PWMCON0_PWMF;               // clear PWM interrupt flag

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
void main(void)
{

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r test start ...");

    printf ("\n\r PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> ");
    printf ("\n\r               = (24MHz/8)/(999+1)");
    printf ("\n\r               = 3 kHz");

    ENABLE_PWM0_CH2_P10_OUTPUT;
    PWM0_INT_PWM2;
    PWM0_FALLING_INT;           /*Setting Interrupt happen when PWM0 falling signal */
  
    PWM0_CLOCK_DIV_8;
    PWMPH = HIBYTE(999);       /*Setting PWM period  */
    PWMPL = LOBYTE(999);
    PWM2H = HIBYTE(499);       /*PWM0 high duty = 1/2 PWM period */
    PWM2L = LOBYTE(499); 

    ENABLE_PWM0_INTERRUPT;     /*Enable PWM interrupt  */
    ENABLE_GLOBAL_INTERRUPT;
    set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
    while(1);
}
