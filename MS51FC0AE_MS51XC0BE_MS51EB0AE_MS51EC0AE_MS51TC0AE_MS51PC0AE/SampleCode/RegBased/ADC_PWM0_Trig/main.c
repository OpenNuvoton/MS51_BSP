/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
#if defined __C51__
void ADC_ISR (void) interrupt 11
#elif defined __ICC8051__
#pragma vector=0x5B
__interrupt void ADC_ISR (void)
#elif defined __SDCC__
void ADC_ISR (void) __interrupt (11)
#endif
{
    PUSH_SFRS;              /* for SFRS page */

    clr_ADCCON0_ADCF;       /* Clear ADC interrupt flag  */
    GPIO_LED ^= 1;          /* Check the P3.0 toggle at falling edge of PWM  */

    POP_SFRS;               /* for SFRS page */
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{

    GPIO_LED_QUASI_MODE;
/* Initial UART0 for printf */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");
/*-------------------------------------------------
  ADC trig initial setting
  Please modify #if value to open diffent type
--------------------------------------------------*/
#if 1
/* By PWM falling edge */
    ENABLE_PWM0_CH0_P12_OUTPUT;
    ENABLE_ADC_AIN0;                            /*  Enable AIN0 P1.7 as ADC input */
    PWM0_FALLINGEDGE_TRIG_ADC;  
#endif    
#if 0
/* By PWM rising edge */
    ENABLE_PWM0_CH0_P12_OUTPUT;
    ENABLE_ADC_AIN0;                            /*  Enable AIN0 P1.7 as ADC input */
    PWM0_RISINGEDGE_TRIG_ADC;
#endif    
#if 0
/* By PWM central point */
    ENABLE_PWM0_CH0_P12_OUTPUT;
    ENABLE_ADC_AIN0;                            /*  Enable AIN0 P1.7 as ADC input */
    PWM_CENTER_TYPE;
    PWM0_CENTRAL_TRIG_ADC;  
#endif  
#if 0
/* By PWM end point */
    ENABLE_PWM0_P12_OUTPUT;
    ENABLE_ADC_AIN0;                            /* Enable AIN0 P1.7 as ADC input */
    PWM_CENTER_TYPE;
    PWM0_END_TRIG_ADC;
#endif  
  
/* Setting PWM value */
    PWM0PH = 0x07;                                /* Setting PWM value   */        
    PWM0PL = 0xFF;
    PWM0C0H = 0x02;
    PWM0C0L = 0xFF;
    set_PWM0CON0_LOAD;                           /*  PWM run */
    set_PWM0CON0_PWM0RUN;
/* Setting ADC */
    ENABLE_ADC_INTERRUPT;                       /*  Enable ADC interrupt (if use interrupt) */
    ENABLE_GLOBAL_INTERRUPT;  
    while(1);

}


