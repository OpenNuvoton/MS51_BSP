/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#if defined __C51__
code char       u8Transmit_Data[5] = {0x4E, 0x55, 0x56, 0x4F, 0x54};
#elif defined __ICC8051__
const __code char       u8Transmit_Data[5] = {0x4E, 0x55, 0x56, 0x4F, 0x54};
#elif defined __SDCC__
__code char     u8Transmit_Data[5] = {0x4E, 0x55, 0x56, 0x4F, 0x54};
#endif

uint8_t   u8Receive_Data[5];
uint8_t   u8CNT = 0;
BIT       SPI_Send_Flag, SPI_Receive_Finish_Flag;

//-----------------------------------------------------------------------------------------------------------
void SPI_Error(void)
{
    while (1);
}
//-----------------------------------------------------------------------------------------------------------
void SPI_Initial(void)
{ 
    P15_QUASI_MODE;                                  //P15 (SS) Quasi mode
    P10_QUASI_MODE;                                  //P10 (SPCLK) Quasi mode
    P00_QUASI_MODE;                                  //P00 (MOSI) Quasi mode
    P01_QUASI_MODE;                                  //P01 (MISO) Quasi mode;

    clr_SPCR_MSTR;                                   // SPI in Slave mode 
    clr_SPCR_LSBFE;                                  // MSB first 

    clr_SPCR_CPOL;                                   // The SPI clock is low in idle mode
    set_SPCR_CPHA;                                   // The data is sample on the second edge of SPI clock     
       
    set_SPCR_SPIEN;                                  // Enable SPI function
    
    clr_SPSR_SPIF;                                   // Clear SPI flag
    SPDR = u8Transmit_Data[0];
}

//-----------------------------------------------------------------------------------------------------------

void Slave_Polling_Receive_Data(void)
{
      u8Receive_Data[0] = Spi_Read_Byte(u8Transmit_Data[0]);
      u8Receive_Data[1] = Spi_Read_Byte(u8Transmit_Data[1]);
      u8Receive_Data[2] = Spi_Read_Byte(u8Transmit_Data[2]);
      u8Receive_Data[3] = Spi_Read_Byte(u8Transmit_Data[3]);
      u8Receive_Data[4] = Spi_Read_Byte(u8Transmit_Data[4]);
}
//-----------------------------------------------------------------------------------------------------------
void Slave_Polling_Send_Data(void)
{

    DISABLE_SPI0_INTERRUPT;
    SPI_Send_Flag = 1;

    Spi_Write_Byte(0x4F);
    Spi_Write_Byte(0x4E);

    ENABLE_SPI0_INTERRUPT;
}
//-----------------------------------------------------------------------------------------------------------

void main(void)
{   
    SPI_Initial();
    /* Slave interrupt receive data */
    Slave_Polling_Receive_Data();           // Wait Slave receive data from master use the interrupt

    /* Slave interrupt receive data */
    Slave_Polling_Send_Data();                  // Slave transmit data to master
    clr_SPSR_SPIF;
    SPDR = 0x00;

    if(u8Receive_Data[0] != 0x90)               // Receive 1st DATA form master 
        SPI_Error(); 
    if(u8Receive_Data[1] != 0x01)               // Receive 2nd DATA form master 
        SPI_Error();
    if(u8Receive_Data[2] != 0x02)               // Receive 3rd DATA form master 
        SPI_Error();
    if(u8Receive_Data[3] != 0x03)               // Receive 4th DATA form master 
        SPI_Error();
    if(u8Receive_Data[4] != 0x04)               // Receive 5th DATA form master 
        SPI_Error();

    while(1);                                    // SPI transmission finish
}

