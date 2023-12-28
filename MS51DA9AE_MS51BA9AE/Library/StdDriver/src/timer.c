/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#if defined __C51__
uint32_t data TIMER0CT,TIMER1CT,TIMER2CT,TIMER3CT;
uint8_t data TH0TMP,TL0TMP,TH1TMP,TL1TMP;

#elif defined __ICC8051__
uint32_t __data TIMER0CT,TIMER1CT,TIMER2CT,TIMER3CT;
uint8_t __data TH0TMP,TL0TMP,TH1TMP,TL1TMP;

#elif defined __SDCC__
uint32_t __data TIMER0CT,TIMER1CT,TIMER2CT,TIMER3CT;
uint8_t __data TH0TMP,TL0TMP,TH1TMP,TL1TMP;
#endif

/**
  * @brief Timer0 delay interrupt initial setting and timer 0 interrupt vector 
  * @param[in] u8SYSCLK define Fsys clock value base on Fsys value.
  *                       - \ref 24 (HIRC 24MHz )
  *                       - \ref 16 (HIRC 16MHz)
  *                       - \ref 8  (MIRC 8MHz or HIRC with clock divider)
  * @param[in] u6DLYUnit define delay time base is (us). 
  *                       - \ref value range is 100 ~ 32768.   [100us ~ 32ms ] for 24MHz
  *                       - \ref value range is 100 ~ 65536.for 8MHz  (use MIRC) 
  *                       - \note The minimum delay value not less than 100us, the maxima value base on Fsys
  *                       - \example 6400 = 6.4ms.
  * @ref     Delay time max. value calculate = 65535 * DIV / Fsys 
  * @return  None 
  * @note    This API needs to be integrated with Timer0 interrupt subroutine.
  * @exmaple :Timer0_AutoReload_Interrupt_Initial(24,1000);    // Fsys is 24MHz and timer base is 1ms
*/
#if 0   /* Interrup Vector demo */
#if defined __C51__
void Timer0_ISR (void) interrupt 1              // vector=0x0B 
#elif defined __ICC8051__
#pragma vector=0x0B                             // Interrupt 1 
__interrupt void Timer0_ISR(void)
#elif defined __SDCC__
void Timer0_ISR (void) __interrupt (1)          // vector=0x0B
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */
      SFRS = 0;
/* reload counter value */
      TH0 = TH0TMP;
      TL0 = TL0TMP;
/* clear flag */
      clr_TCON_TF0;

    if (SFRS_TMP)                 /* for SFRS page */
    {
      ENABLE_SFR_PAGE1;
    }
}
#endif

void Timer0_AutoReload_Interrupt_Initial(uint8_t u8SYSCLK, uint32_t u32DLYUnit)
{
    TIMER0_FSYS_DIV12;                               /* T0M=0, Timer0 Clock = Fsys/12   */
    ENABLE_TIMER0_MODE1;                             /* Timer0 as 16-bits mode           */
    TIMER0CT = 65535ul-(u8SYSCLK*u32DLYUnit/12ul);
    TH0TMP = HIBYTE(TIMER0CT);
    TL0TMP = LOBYTE(TIMER0CT);
    TH0 = TH0TMP;
    TL0 = TL0TMP;
    clr_TCON_TF0;
    set_TCON_TR0;                                    /* Start Timer0 */
    ENABLE_TIMER0_INTERRUPT;                         /* Enable timer0 Interrupt */
}

void  Timer0_ReloadCounter(void)
{
    clr_TCON_TR0;
    TH0 = TH0TMP;
    TL0 = TL0TMP;
    clr_TCON_TF0;
    set_TCON_TR0;
}
/**
  * @brief Timer1 delay interrupt initial setting and timer 1 interrupt vector  
  * @param[in] u8SYSCLK define Fsys clock value base on Fsys value.
  *                       - \ref 24 (HIRC 24MHz )
  *                       - \ref 16 (HIRC 16MHz)
  *                       - \ref 8  (MIRC 8MHz or HIRC with clock divider)
  * @param[in] u6DLYUnit define delay time base is (us). 
  *                       - \ref value range is 100 ~ 32768.   [100us ~ 32ms ] for 24MHz
  *                       - \ref value range is 100 ~ 65536.   [100us ~ 65ms ] for 8MHz  (use MIRC) 
  *                       - \note The minimum delay value not less than 100us, the maxima value base on Fsys
  *                       - \example 6400 = 6.4ms.
  * @ref     Delay time max. value calculate = 65535 * DIV / Fsys 
  * @return  None 
  * @note    This API needs to be integrated with Timer1 interrupt subroutine.
  * @exmaple :Timer1_AutoReload_Interrupt_Initial(24,1000);    // Fsys is 24MHz and timer base is 1ms
*/
#if 0
#if defined __C51__
void Timer1_ISR (void) interrupt 3             // vector=0x1B
#elif defined __ICC8051__
#pragma vector=0x1B                            // Interrupt 3
__interrupt void Timer1_ISR(void)
#elif defined __SDCC__
void Timer1_ISR (void) __interrupt (3)         // vector=0x1B
#endif
{ 
    SFRS_TMP = SFRS;              /* for SFRS page */
/* Reload counter value */
    TH1 = TH1TMP;
    TL1 = TL1TMP;
/* Clear flag */
    clr_TCON_TF1;

    if (SFRS_TMP)                 /* for SFRS page */
    {
      ENABLE_SFR_PAGE1;
    }
}
#endif

void Timer1_AutoReload_Interrupt_Initial(uint8_t u8SYSCLK, uint32_t u32DLYUnit)
{
    TIMER1_FSYS_DIV12;                               /* T1M=0, Timer1 Clock = Fsys/12   */
    ENABLE_TIMER1_MODE1;                             /* Timer 1 as 16-bits mode           */
    TIMER1CT = 65535ul-(u8SYSCLK*u32DLYUnit/12ul);
    TH1TMP = HIBYTE(TIMER1CT);
    TL1TMP = LOBYTE(TIMER1CT);
    TH1 = TH1TMP;
    TL1 = TL1TMP;
    clr_TCON_TF1;
    set_TCON_TR1;                                    /* Start Timer1 */
    ENABLE_TIMER1_INTERRUPT;                         /* Enable timer1 Interrupt */
}

void  Timer1_ReloadCounter(void)
{
    clr_TCON_TR1;
    TH1 = TH1TMP;
    TL1 = TL1TMP;
    clr_TCON_TF1;
    set_TCON_TR1;
}
/**
  * @brief Timer2 delay interrupt initial setting and timer 1 interrupt vector  
  * @param[in] u32SYSCLK define Fsys clock value. for example 8, use the real Fsys value.
  *                       - \ref 24 (HIRC 24MHz )
  *                       - \ref 16 (HIRC 16MHz)
  *                       - \ref 8  (MIRC 8MHz or HIRC with clock divider)
  * @param[in] u6DLYUnit define delay time base is us. the minimum delay value not less than 100us, the maxima value base on u32SYSCLK
  *                       - \ref  value range is 100 ~ 699050.  [100us ~ 699ms ]  for 24MHz (use HIRC)
  *                       - \ref  value range is 100 ~ 2097120. [100us ~ 2.1s ] for 8MHz  (use MIRC)
  *                       - \note The minimum delay value not less than 100us, the maxima value base on Fsys
  *                       - \example 6400 = 6.4ms.
  * @ref     Delay time max. value calculate = 65535 * DIV / Fsys 
  * @return  None
  * @note    Timer 2 divider fixed with 256.
  * @note    This API needs to be integrated with Timer1 interrupt subroutine.
  * @exmaple :  Timer2_AutoReload_Interrupt_Initial(24,105000);   // Means Fsys is 24MHz and time base is 105ms
*/
#if 0    
#if defined __C51__
void Timer2_ISR(void)  interrupt 5
#elif defined __ICC8051__
#pragma vector=0x2B                             /* interrupt 5 */
__interrupt void Timer2_ISR(void)
#elif defined __SDCC__
void Timer2_ISR(void)  __interrupt (5)
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */
    clr_T2CON_TF2;

    if (SFRS_TMP)                 /* for SFRS page */
    {
      ENABLE_SFR_PAGE1;
    }
}
#endif

void Timer2_AutoReload_Interrupt_Initial(uint8_t u8SYSCLK, uint32_t u32DLYUnit)
{
    TIMER2_AUTO_RELOAD_DELAY_MODE;
    TIMER2_DIV_256;                 /* fix divider 256 */
    TIMER2CT = 65535ul-(u8SYSCLK*u32DLYUnit/256ul);
    TH2 = HIBYTE(TIMER2CT);
    TL2 = LOBYTE(TIMER2CT);
    RCMP2H = HIBYTE(TIMER2CT);
    RCMP2L = LOBYTE(TIMER2CT);
    clr_T2CON_TF2;
    set_T2CON_TR2;                                   /* Start Timer2  */
    ENABLE_TIMER2_INTERRUPT;                         /* Enable timer2 Interrupt */
}

/**
  * @brief Timer3 delay interrupt initial setting and timer 1 interrupt vector  
  * @param[in] u8SYSCLK define Fsys clock value. for example 24, use the real Fsys value.
  *                       - \ref 24 (HIRC 24MHz )
  *                       - \ref 16 (HIRC 16MHz)
  *                       - \ref 8  (HIRC 8MHz or after clock divider)
  * @param[in] u6DLYUnit define delay time base is (us). 
  *                       - \ref value range is 100 ~ 349525 for 24MHz (use HIRC) 
  *                       - \note The minimum delay value not less than 100us, the maxima value base on Fsys
  *                       - \example 6400 = 6.4ms.
  * @ref     Delay time max. value calculate = 65535 * DIV / Fsys 
  * @return  None
  * @note    Timer3 divider fixed with 128. 
  * @note    This API needs to be integrated with Timer1 interrupt subroutine.
  * @exmaple :  Timer3_AutoReload_Interrupt_Initial(24,105000);   // Means Fsys is 24MHz and time base is 105ms
*/
#if 0
#if defined __C51__
void Timer3_ISR(void)     interrupt  16
#elif defined __ICC8051__
#pragma vector=0x83                             /* interrupt 16 */
__interrupt void Timer3_ISR(void)
#elif defined __SDCC__
void Timer3_ISR(void)   __interrupt  (16)
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */
    clr_T3CON_TF3;

    if (SFRS_TMP)                 /* for SFRS page */
    {
      ENABLE_SFR_PAGE1;
    }
}
#endif 

void Timer3_AutoReload_Interrupt_Initial(uint8_t u8SYSCLK, uint32_t u32DLYUnit)
{
    SFRS = 0;
    TIMER3_DIV_128;                                   /*  Timer 3 divider fixed with 128.*/
    TIMER2CT = 65535ul-(u8SYSCLK*u32DLYUnit/128ul);
    TIMER2CT &= 0xFFFF;
    RH3 = HIBYTE(TIMER2CT);
    RL3 = LOBYTE(TIMER2CT);
    clr_T3CON_TF3;
    set_T3CON_TR3;                                   /* Trigger Timer3  */
    ENABLE_TIMER3_INTERRUPT;                         /* Enable timer3 Interrupt */
}

