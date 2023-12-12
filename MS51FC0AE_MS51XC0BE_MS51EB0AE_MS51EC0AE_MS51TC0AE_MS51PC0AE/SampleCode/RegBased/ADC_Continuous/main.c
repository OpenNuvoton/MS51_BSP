/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#if defined __C51__
uint8_t xdata ResultTable[256] _at_ 0x300;
#elif defined __ICC8051__
uint8_t __xdata ResultTable[256];
#elif defined __SDCC__
uint8_t __at 0x300 ResultTable[256] ;
#endif

BIT  ADC_CONT_FINAL_FLAG;

/**
 * @brief       ADC Interrupt Subroutine
 * @param       None
 * @return      None
 * @details     Set ADC continus finished flag.
 */
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

    clr_ADCCON0_ADCF;
    ADC_CONT_FINAL_FLAG = 1;

    POP_SFRS;
}

/**
 * @brief       ADC continus mode main loop
 * @param       None
 * @return      None
 * @details     None
 */
void main (void) 
{
    uint8_t i;
    uint16_t temp;
/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
  
/*loop clear XRAM area . */   
    for (i=0;i<192;i++)
    {
        ResultTable[i] =0;
    }
/* ADC continus mode setting . 
   *include adc.c for ADC initial setting
*/
    ENABLE_ADC_CONTINUES_MODE;                         /* Opend ADC as continous mode */
    ENABLE_ADC_CH0;                                    /* and input from AIN0 P1.7  */
    ADC_InitialContinous(0x300,128);                   /* Define data restore in RAM start address and ADC total sample number */
    ADC_ConvertTime(ADC_CH0,2,7);                      /*  ADC sampling clock = Fsys/4, sampling timer select longest value is 7     */
    
    clr_ADCCON0_ADCF;
    ENABLE_ADC_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    
    set_ADCCON0_ADCS;                                  // Trig ADCS bit to start ADC 

/* ADC finished and print the result from XRAM. */
    while(1)
    {
      if (ADC_CONT_FINAL_FLAG)
      {
            DISABLE_ADC;
             for(i=0;i<128;i++)
            {
              temp=(ResultTable[i]<<4)+(ResultTable[i/2+128]&0x0F);
              SFRS = 0;

#if defined __C51__
              printf ("\n ADC No.%bD",i);
              printf (" = 0x%02X ", temp);
#elif defined __ICC8051__
              printf ("\n ADC No.%hX",i);
#elif defined __SDCC__
              printf ("\n ADC No.%hX",i);
#endif
              printf (" = 0x%02X ", temp);

              i++;
              temp=(ResultTable[i]<<4)+((ResultTable[(i-1)/2+128]>>4)&0x0F);
#if defined __C51__
              printf ("\n ADC No.%bD",i);
              printf (" = 0x%02X ", temp);
#elif defined __ICC8051__
              printf ("\n ADC No.%hX",i);
#elif defined __SDCC__
              printf ("\n ADC No.%hX",i);
#endif
              printf (" = 0x%02X ", temp);
              if(i==127)
              ADC_CONT_FINAL_FLAG=0;
            }
        }
      }        
}
