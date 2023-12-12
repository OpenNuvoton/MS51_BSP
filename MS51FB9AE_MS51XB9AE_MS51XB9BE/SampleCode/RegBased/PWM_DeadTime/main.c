/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/******************************
  * @brief     Main loop.
  * @param[in] None.
  * @return    None.
******************************/
void main(void)
{
/* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...");

    printf ("\n\r PWM frequency   = Fpwm/((PWMPH,PWMPL)+1) = (24MHz/8)/(0x7CF+1) = 1.5KHz (1ms)");
    printf ("\n\r PWM4 high duty  = PWM4H,PWM4L = 0x01CF = 1/4 PWM period");
    printf ("\n\r PWM0 high duty  = PWM0H,PMW0L = 0x03CF = 1/2 PWM period");
    printf ("\n\r Dead time       = 0x1FF <PDTEN.4+PDTCNT[7:0]>/Fsys = 0x1FF/Fsys = 512/24M = 21.3 us (max value)");

    P12_QUASI_MODE;
    P11_QUASI_MODE;
    P01_QUASI_MODE;
    P15_QUASI_MODE;

    ENABLE_PWM0_CH0_P12_OUTPUT;
    ENABLE_PWM0_CH1_P11_OUTPUT;
    ENABLE_PWM0_CH4_P01_OUTPUT;
    ENABLE_PWM0_CH5_P15_OUTPUT;
  
    PWM0_COMPLEMENTARY_MODE;          //Only this mode support deat time function
    PWM0_CLOCK_DIV_8;
    PWMPH = 0x07;
    PWMPL = 0xCF;

    PWM0H = 0x03;
    PWM0L = 0xCF;
    ENABLE_SFR_PAGE1;                    // PWM4 and PWM5 duty value need set SFPPAGE 1
    PWM4H = 0x01;
    PWM4L = 0xCF;
    ENABLE_SFR_PAGE0;
    
    printf ("\n\r Please always setting Dead time if needed before PWM run.  ");
    PWM0_DeadZoneEnable(PWM0_CH01,0x100);      //value never over 0x1FF

    set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
    while(1);    
}
