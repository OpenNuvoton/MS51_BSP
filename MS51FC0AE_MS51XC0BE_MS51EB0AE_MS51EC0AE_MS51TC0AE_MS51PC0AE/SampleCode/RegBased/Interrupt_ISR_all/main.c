/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"


/*---------------------------------------------*/
void main(void)
{ 
    MODIFY_HIRC(HIRC_24);

    Set_Interrupt_Priority_Level(INT_WDT, 0);
    Set_Interrupt_Priority_Level(INT_ADC, 1);
    SET_INT_PWM_LEVEL3;

    while(1);
}
/* Check isr.c for full interrupt vector      */
