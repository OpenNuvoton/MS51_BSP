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
  * MG51 power down code for test power down current, BOD disabled.
******************************/
void main (void) 
{

/* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...");


/* Quasi mode better for power down power comsuption (necessary) */
    ALL_GPIO_QUASI_MODE;
    P0=0;
    P1=0;
    P2=0;
/* clock only for reference, real chip please don't output clock (necessary)*/
    set_CKCON_CLOEN;
/*MUST Disable BOD to low power (necessary) */
    BOD_DISABLE;              //BOD enable power down current please check datasheet DC charactor.

/* Real into power down mode (necessary) */
    set_PCON_PD;
    while(1);
  
}



