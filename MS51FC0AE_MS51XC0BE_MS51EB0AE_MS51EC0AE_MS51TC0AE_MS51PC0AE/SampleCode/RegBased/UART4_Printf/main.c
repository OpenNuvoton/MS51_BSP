/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"


/**
 * @brief       Main loop
 * @param       None
 * @return      None
 * @details     UART4 printf send data.
 */
void main (void) 
{

/* Modify HIRC to 24MHz is for UART baud rate deviation not over 1% */
    MODIFY_HIRC(HIRC_24);

    P23_QUASI_MODE;                              /* Set UART4_TXD pin P2.3 as Quasi mode */
    ENABLE_UART4_TXD_P23;
    UART4_Open(24000000,115200);

    while(1)
    {
      printf("\n Hello world!");
      Timer0_Delay(24000000,300,1000);
    }
}