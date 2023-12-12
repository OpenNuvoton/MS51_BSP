/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#if defined __C51__
double Bandgap_Voltage,VDD_Voltage; 
#elif defined __ICC8051__
double Bandgap_Voltage,VDD_Voltage; 
#elif defined __SDCC__
float  Bandgap_Voltage,VDD_Voltage;
#endif

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    uint16_t ADC_BG_Result;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...");

/* ADC sampling timing setting for Bandgap*/  
    ENABLE_ADC_BANDGAP;
    ADCCON1|=0x30;            /* clock divider */
    ADCCON2|=0x0E;            /* AQT time */
/*start bandgap ADC */
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;
    while(ADCF == 0);
/* ADC convert current Bandgap value */
    ADC_BG_Result = ADCRH<<4 ;
    ADC_BG_Result = ADC_BG_Result|(ADCRL&0x0F);
    DISABLE_ADC;              /*Disable ADCEN each time after ADC trig */

/*                  VDD  Now                         READ_BANDGAP() VALUE              */
/*    ------------------------------------- = ----------------------------------       */
/*    3072mV(Storage value test condition)      NOW ADC Bandgap convert reuslt         */
      VDD_Voltage = ((float)READ_BANDGAP())/((float)ADC_BG_Result)*3072;

/*            Bandgap real voltage                    READ_BANDGAP() VALUE             */
/*    ------------------------------------- = ----------------------------------       */
/*    3072mV(Storage value test condition)              4096(12bit ADC)                */
      Bandgap_Voltage = ((float)READ_BANDGAP())*3/4;

/*printf result value */

#if defined __SDCC__
    printf_fast_f ("\n\r BG Voltage = %f", Bandgap_Voltage);
    printf_tiny (" mV \r");
    printf_fast_f ("\n\r VDD voltage = %f", VDD_Voltage);
    printf_tiny (" mV \r");
#else
    printf ("\n\r BG Voltage = %f", Bandgap_Voltage);
    printf (" mV \r");
    printf ("\n\r VDD voltage = %f", VDD_Voltage);
    printf (" mV \r");
#endif
    while(1);

}



