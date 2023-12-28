/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#if 0 
/**
 * @brief       Watchdog time Interrupt Vector demo  
 * @param       none
 * @details     none
 * @note        none
 */
#if defined __C51__
void WDT_ISR (void)   interrupt 10
#elif defined __ICC8051__
#pragma vector=0x53
__interrupt void WDT_ISR(void)
#elif defined __SDCC__
void WDT_ISR (void)   __interrupt (10)
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */
    clr_WDCON_WDTF;
    if (SFRS_TMP)                 /* for SFRS page */
    {
      ENABLE_SFR_PAGE1;
    }
}
#endif

/**
 * @brief       Watchdog time delay setting 
 * @param       u8WDTDIV WKT counter divider select  (1/4/8/16/32/64/128/256) 
 * @return      none
 * @details     none
 * @note        none
 * @example     WDT_Open(256);
 */
 void WDT_Open(uint16_t u8WDTDIV)
{
    SFRS=0;
    BIT_TMP=EA;
    EA=0;
    switch (u8WDTDIV)
    {
        case 1: TA=0xAA;TA=0x55;WDCON&=0xF8; break;
        case 4: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x01; break;
        case 8: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x02; break;
        case 16: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x03; break;
        case 32: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x04; break;
        case 64: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x05; break;
        case 128: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x06; break;
        case 256: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x07; break;
        default: break;
    }
    EA = BIT_TMP;
    set_WDCON_WIDPD;
    set_WDCON_WDTR;
}

/**
 * @brief       Watchdog time interrupt setting 
 * @param       u8WDTINT (Enable/Disable) 
 * @return      none
 * @details     none
 * @note        none
 * @example      WDT_Interrupt(Enable);
 */
void WDT_Interrupt(uint8_t u8WDTINT)
{
    switch (u8WDTINT)
    {
        case Disable: clr_EIE_EWDT; break;    
        case Enable: set_EIE_EWDT; break;
    }
}

/**
 * @brief       Watchdog Clear Counter process
 * @param       none
 * @return      none
 * @details     none
 * @note        none
 * @example     WDT_Clear();
 */
void WDT_Clear(void)
{
      WDT_COUNTER_CLEAR;                  /* Clear WDT counter */ 
      while(WDCON&SET_BIT6);              /* Check for the WDT counter cleared */
}
