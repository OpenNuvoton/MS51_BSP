/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/**
 * @brief       Timer 2 capture setting 
 * @param       u8CAPSource input capture module select (IC0 / IC1 / IC2)
 * @param       u8CAPLevel input level select  (CaptureFalling/CaptureRising/CaptureEither)
 * @param       u8TM2DIV reload counter value(1~7 = DIV 1/4/16/32/64/128/256/512.) 
 * @return      none
 * @details     none
 * @example     TIMER2_Capture(IC0,CaptureRising,7);
 */
void TIMER2_Capture(uint8_t u8CAPSource, uint8_t u8CAPLevel, uint8_t u8TM2DIV)
{
    SFRS = 0x00;
    T2MOD&=0x0F;
    T2MOD|=(u8TM2DIV<<4);
    T2MOD|=0x88;
    SFRS = 0x01;
    switch (u8CAPSource)
    {
        case IC0:
          switch (u8CAPLevel)
          {
            case CaptureFalling:  CAPCON1&=0xFC; break;
            case CaptureRising:   CAPCON1&=0xFC;CAPCON1|=0x01; break;
            case CaptureEither:   CAPCON1&=0xFC;CAPCON1|=0x02; break;
          }
          set_CAPCON2_ENF0;                 //enable noise filer
          set_CAPCON0_CAPEN0;               //Input capture 0 enable
          SFRS=0;T2MOD&=0xFC;T2MOD|=0x01;   //Set reload
          C0H = 0;
          C0L = 0;
        break;
        case IC1:
          switch (u8CAPLevel)
          {
            case CaptureFalling:  CAPCON1&=0xF3; break;
            case CaptureRising:   CAPCON1&=0xF3;CAPCON1|=0x04; break;
            case CaptureEither:   CAPCON1&=0xF3;CAPCON1|=0x08; break;
          }
          set_CAPCON2_ENF1;
          set_CAPCON0_CAPEN1;
          SFRS=0;T2MOD&=0xFC;T2MOD|=0x02;
          C1H = 0;
          C1L = 0;
        break;
        case IC2:
          switch (u8CAPLevel)
          {
            case CaptureFalling:  CAPCON1&=0xCF; break;
            case CaptureRising:   CAPCON1&=0xCF;CAPCON1|=0x10; break;
            case CaptureEither:   CAPCON1&=0xCF;CAPCON1|=0x20; break;
          }
          set_CAPCON2_ENF2;
          set_CAPCON0_CAPEN2;
          SFRS=0;T2MOD&=0xFC;T2MOD|=0x03;
          C2H = 0;
          C2L = 0;
        break;
    }
    clr_T2CON_TF2;
    set_T2CON_TR2;
}


/**
 * @brief       Timer 2 capture interrupt initial setting 
 * @param       u8CAPINT capture interrupt (Disable / Enable)
 * @return      none
 * @details     none
 * @example      TIMER2_Capture_Interrupt(Enable);
 */
void TIMER2_Capture_Interrupt(uint8_t u8CAPINT)
{
    switch (u8CAPINT)
    {
        case Disable: clr_EIE_ECAP; break;
        case Enable:  set_EIE_ECAP; break;
    }
}
