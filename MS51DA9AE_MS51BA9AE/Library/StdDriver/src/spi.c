/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

/****************************************************************/
void Spi_Write_Byte(uint8_t u8SpiWB)
{
    SPDR = u8SpiWB;
    while(!(SPSR&0x80));
    clr_SPSR_SPIF;
}
/****************************************************************/
uint8_t Spi_Read_Byte(uint8_t u8SpiWB)
{
    uint8_t u8SpiRB;
    SPDR = u8SpiWB;
    while(!(SPSR&0x80));
    u8SpiRB = SPDR;
    clr_SPSR_SPIF;
    return u8SpiRB;
}
