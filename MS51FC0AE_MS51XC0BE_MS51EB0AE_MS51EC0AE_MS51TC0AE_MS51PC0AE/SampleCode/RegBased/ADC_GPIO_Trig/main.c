/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

BIT adcintflag;
/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
#if defined __C51__
void ADC_ISR (void) interrupt 11
#elif defined __ICC8051__
#pragma vector=0x5B
__interrupt void ADC_ISR(void)
#elif defined __SDCC__
void ADC_ISR (void) __interrupt (11)
#endif
{
    PUSH_SFRS;
    
    clr_ADCCON0_ADCF;                               //clear ADC interrupt flag
    adcintflag = 1;
    
    POP_SFRS;
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");
    
/*---------------------------------------------------------------*/
/* ADC port trig initial setting toggle P0.4 to start ADC        */
/*---------------------------------------------------------------*/
    ENABLE_ADC_CH0;                              // Enable AIN0 P1.7 as ADC pin
    ADC_ConvertTime(ADC_CH0,2,7);
    P04_INPUT_MODE;
    P04_FALLINGEDGE_TRIG_ADC;                      // P0.4 falling edge as adc start trig signal
/* Enable ADC interrupt */
    ENABLE_ADC_INTERRUPT;                                  // Enable ADC interrupt (if use interrupt)
    ENABLE_GLOBAL_INTERRUPT;
    
/* Trig P04 falling edge to start adc, no need set ADCS bit */
    adcintflag = 0;
    while(1)
    {
      if (adcintflag)
      {
#if defined __C51__
          printf ("\n ADCRH Value = 0x%bx",ADCRH);
          printf (" ADCRL Value = 0x%bx",ADCRL);// Wait ADC interrupt
#elif defined __ICC8051__
          printf ("\n ADCRH Value = 0x%hx",ADCRH);
          printf (" ADCRL Value = 0x%hx",ADCRL);// Wait ADC interrupt
#elif defined __SDCC__
          printf ("\n ADCRH Value = 0x%hx",ADCRH);
          printf (" ADCRL Value = 0x%hx",ADCRL);// Wait ADC interrupt
#endif
          adcintflag = 0;
      }
    }
}


