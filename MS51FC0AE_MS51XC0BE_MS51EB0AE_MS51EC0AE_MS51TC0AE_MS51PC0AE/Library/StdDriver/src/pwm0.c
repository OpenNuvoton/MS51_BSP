/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/****** PWM0 SETTING ********/
/**
* @brief This function config PWM clock base
* @param[in] u8PWMCLKSource PWM0 clock source from HIRC or TIMER1.
                  - \ref  PWM_FSYS
                  - \ref  PWM_TIMER1
* @param[in] u8PWM0CLKDIV the divider value of PWM clock.  - \ref (1\2\4\8\16\32\64\128)
* @return none
* @note
* @example PWM0_ClockSource(PWM0_HIRC,128);
 */
void PWM0_ClockSource(uint8_t u8PWMCLKSource, uint8_t u8PWM0CLKDIV)
{
    switch (u8PWMCLKSource)
    {
        case PWM_FSYS:
            clr_CKCON_PWMCKS;
            break;

        case PWM_TIMER1:
            set_CKCON_PWMCKS;
            break;
    }

    switch (u8PWM0CLKDIV)
    {
        case 1:
            PWM0_CLOCK_DIV_1;
            break;

        case 2:
            PWM0_CLOCK_DIV_2;
            break;

        case 4:
            PWM0_CLOCK_DIV_4;
            break;

        case 8:
            PWM0_CLOCK_DIV_8;
            break;

        case 16:
            PWM0_CLOCK_DIV_16;
            break;

        case 32:
            PWM0_CLOCK_DIV_32;
            break;

        case 64:
            PWM0_CLOCK_DIV_64;
            break;

        case 128:
            PWM0_CLOCK_DIV_128;
            break;
    }
}

/**
* @brief This function config PWM generator
* @param[in] u8ChannelNum PWM channel number. Valid values are between 0~5
* @param[in] u8OPMode PWM run mode select from Independent, Complementary or Synchronized mode.
* @param[in] u8PwmType select Edge-Aligned Type or Center-Aligned Type
* @param[in] u32PWM0Frequency Target generator frequency, note the actually PWM period is 16bit value. from 0x0000 ~ 0xFFFF
* @param[in] u16DutyCycle Target generator duty cycle percentage. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
* @return none
* @note  none
* @example PWM0_ConfigOutputChannel(0,Independent,EdgeAligned,0x6FF,10);
 */
void PWM0_ConfigOutputChannel(uint8_t u8PWM0ChannelNum,
                              uint8_t u8PWM0OPMode,
                              uint8_t u8PWM0PwmType,
                              uint16_t u16PWM0Frequency,
                              uint16_t u16PWM0DutyCycle)
{
    SFRS = 0;
    switch (u8PWM0OPMode)
    {
        case Independent:   PWM0CON1 &= 0x3F; break;
        case Complementary: PWM0CON1 &= 0x3F; PWM0CON1 |= 0x40; break;
        case Synchronous:   PWM0CON1 &= 0x3F; PWM0CON1 |= 0x80; break;
    }
    switch (u8PWM0PwmType)
    {
        case EdgeAligned:   PWM0CON1 &= 0xEF; break;
        case CenterAligned: PWM0CON1 |= 0x10; break;
    }
    switch (u8PWM0ChannelNum)
    {
        case 0: PWM0C0H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8; PWM0C0L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);break;
        case 1: PWM0C1H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8; PWM0C1L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);break;
        case 2: PWM0C2H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8; PWM0C2L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);break;
        case 3: PWM0C3H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8; PWM0C3L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);break;
        case 4: SFRS=1;PWM0C4H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8;PWM0C4L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);SFRS=0;break;
        case 5: SFRS=1;PWM0C5H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8;PWM0C5L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);SFRS=0;break;
    }
    PWM0PH = u16PWM0Frequency >> 8;
    PWM0PL = u16PWM0Frequency;
}

/**
* @brief This function config PWM0 each channel duty relaod value
* @param[in] u8ChannelNum PWM channel number. Valid values are between 0~5
* @param[in] u16DutyCycle Target generator duty cycle percentage. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
* @return none
* @note  none
* @example PWM0_ChannelDuty(0,Independent,EdgeAligned,0x6FF,10);
 */
void PWM0_ChannelDuty(uint8_t u8PWM0ChannelNum,
                      uint16_t u16PWM0DutyCycle)
{
    uint16_t u16PWM0Frequency;

    SFRS = 0;
    u16PWM0Frequency = (PWM0PH<<8);
    u16PWM0Frequency |= PWM0PL;
    switch (u8PWM0ChannelNum)
    {
        case 0: PWM0C0H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8; PWM0C0L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);break;
        case 1: PWM0C1H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8; PWM0C1L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);break;
        case 2: PWM0C2H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8; PWM0C2L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);break;
        case 3: PWM0C3H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8; PWM0C3L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);break;
        case 4: SFRS=1;PWM0C4H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8;PWM0C4L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);SFRS=0;break;
        case 5: SFRS=1;PWM0C5H=(u16PWM0Frequency/100UL*u16PWM0DutyCycle)>>8;PWM0C5L=(u16PWM0Frequency/100UL*u16PWM0DutyCycle);SFRS=0;break;
    }
}

/**
* @brief This function config PWM Complementary pair inset dead zone time
* @param[in] u8PWM0Pair PWM0 channel pair need insert pair define. (PWM0_CH01 / PWM0_CH23 / PWM0_CH45 / PWM0_ALL)
* @param[in] u8PWM0DZValue the insert value.  PWM dead-time = (u8PWM0DZValue+1)/Fsys
* @return none
* @note
* @example PWM0_DeadZoneEnable(PWM0_CH01,0x110);
 */
void PWM0_DeadZoneEnable(uint8_t u8PWM0Pair, uint16_t u16PWM0DZValue)
{
    SFRS = 0;
    BIT_TMP = EA;
    EA = 0;
    TA_REG_TMP = u16PWM0DZValue & 0x0100 >> 4;

    switch (u8PWM0Pair)
    {
        case PWM0_CH01:
            TA_REG_TMP |= 0x01;
            break;

        case PWM0_CH23:
            TA_REG_TMP |= 0x02;
            break;

        case PWM0_CH45:
            TA_REG_TMP |= 0x04;
            break;

        case PWM0_ALL:
            TA_REG_TMP |= 0x07;
            break;
    }
    TA = 0xAA;
    TA = 0x55;
    PWM0DTEN = TA_REG_TMP;

    TA_REG_TMP = u16PWM0DZValue&0x00FF;
    TA = 0xAA;
    TA = 0x55;
    PWM0DTCNT = TA_REG_TMP;
    EA = BIT_TMP;
}

/**
* @brief This function disable all PWM Complementary pair inset dead zone time
* @param[in] none
* @return none
* @note
* @example PWM0_DeadZone_ALL_Disable();
*/
void PWM0_DeadZone_ALL_Disable(void)
{
    SFRS = 0x01;
    TA = 0xAA;
    TA = 0x55;
    PWM0DTEN = 0x00;
    EA = BIT_TMP;
}

/**
* @brief This function action all PWM run
* @param[in] none
* @return none
* @note
* @example PWM0_RUN();
*/
void PWM0_RUN(void)
{
    set_PWM0CON0_PWM0RUN;
}

/**
* @brief This function action all PWM stop run
* @param[in] none
* @return none
* @note
* @example PWM0_RUN();
*/
void PWM0_STOP(void)
{
    clr_PWM0CON0_PWM0RUN;
}


/**
* @brief This function action PWM value reload
* @param[in] none
* @return none
* @note        
* @example PWM0_Reload();
*/
void PWM0_Reload(void)
{
    set_PWM0CON0_LOAD;
}


