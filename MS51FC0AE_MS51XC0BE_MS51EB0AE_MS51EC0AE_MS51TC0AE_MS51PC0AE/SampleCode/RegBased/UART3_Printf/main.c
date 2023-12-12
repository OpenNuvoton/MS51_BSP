/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/************************************************************************************************************/
/* FUNCTION_PURPOSE: define UART3 MFP                                                                       */
/************************************************************************************************************/
#define     UART3_P12_P11

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main (void) 
{

/* Modify HIRC to 24MHz is for UART baud rate deviation not over 1% */
    MODIFY_HIRC(HIRC_24);

  /* UART3 initial */
#ifdef          UART3_P12_P11
    P12_QUASI_MODE;
    ENABLE_UART3_TXD_P12;
#elif  defined   UART3_P15_P25
    P15_QUASI_MODE;
    ENABLE_UART3_TXD_P15;
#elif  defined   UART3_P05_P34
    P05_QUASI_MODE;
    ENABLE_UART3_TXD_P05;
#endif

    UART3_Open(24000000,115200);
    while(1)
    {
      printf("\n Hello world!");
      Timer0_Delay(24000000,300,1000);
    }
}