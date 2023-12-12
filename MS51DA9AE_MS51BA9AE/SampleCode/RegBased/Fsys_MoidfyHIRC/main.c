/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/* PLEASE first setting CONFIG P2.0 as notmal GPIO not reset pin*/ 
void main(void)
{
  P11_PUSHPULL_MODE;
  GPIO_LED_QUASI_MODE;
  set_CKCON_CLOEN;
/* clock out about  100khz base on HIRC div 160 */
  CKDIV = 0X50;
  while (P20)
  {
    MODIFY_HIRC(HIRC_16);
    GPIO_LED = 1;
    Timer0_Delay(16000000,5,1000);
    GPIO_LED = 0;
    Timer0_Delay(16000000,5,1000);
  }
/* HIRC modify to 24MHz  */
  MODIFY_HIRC(HIRC_24);
  while(1);
  
}
