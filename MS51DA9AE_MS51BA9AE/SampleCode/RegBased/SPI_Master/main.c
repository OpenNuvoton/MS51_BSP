/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#define  slave_interrupt

/*---------------------------------------------------------------------------------------------------------*/
void SPI_Error(void)
{
    printf ("\n SPI transfer error! ");
    while(1);                                       // SPI error
}

/*---------------------------------------------------------------------------------------------------------*/
void SPI_Initial(void)
{      
    P05_QUASI_MODE;                                  // P05 (SS) Quasi mode
    P10_QUASI_MODE;                                  // P10 (SPCLK) Quasi mode
    P00_QUASI_MODE;                                  // P00 (MOSI) Quasi mode
    P01_QUASI_MODE;                                  // P01 (MISO) Quasi mode
    
    set_SPSR_DISMODF;                                // SS General purpose I/O ( No Mode Fault ) 
    clr_SPCR_SSOE;
   
    clr_SPCR_LSBFE;                                  // MSB first

    clr_SPCR_CPOL;                                   // The SPI clock is low in idle mode
    clr_SPCR_CPHA;                                   // The data is sample on the second edge of SPI clock 
    
    set_SPCR_MSTR;                                   // SPI in Master mode 
    SPICLK_FSYS_DIV16;                                    // Select SPI clock 
    set_SPCR_SPIEN;                                  // Enable SPI function 
    clr_SPSR_SPIF;
}
/*---------------------------------------------------------------------------------------------------------*/
void Start_SPI_process(uint8_t *pu8MID, uint8_t *pu8DID)
{
    SS_PIN = 0;

    Spi_Write_Byte(0x90);
    if(SPDR != 0x4E)
       SPI_Error(); 

#ifdef slave_interrupt                      /* if slave is interrupt mode, add delay to wait */
    _delay_();                              /* remark #define slave interrupt for normal polling transmittion */
#endif

    Spi_Write_Byte(0x01);
    if(SPDR != 0x55)
       SPI_Error();

#ifdef slave_interrupt
    _delay_();
#endif

    Spi_Write_Byte(0x02);
    if(SPDR != 0x56)
       SPI_Error();

#ifdef slave_interrupt
    _delay_();
#endif

    Spi_Write_Byte(0x03);
    if(SPDR != 0x4F)
       SPI_Error();

#ifdef slave_interrupt
    _delay_();
#endif

    Spi_Write_Byte(0x04);
    if(SPDR != 0x54)
       SPI_Error();

#ifdef slave_interrupt
    _delay_();
#endif

   /* Slave Polling receive data */
    *pu8MID = Spi_Read_Byte(0xFF);                             // Receive Slave 1st DATA from Slave
    *pu8DID = Spi_Read_Byte(0xFF);                             // Receive Slave 2nd DATA from Slave

    SS_PIN = 1;    
}

/******************************
  * @brief     Main loop.
  * @param[in] None.
  * @return    None.
******************************/
void main(void)
{
    uint8_t u8MID,u8DID;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();

    SPI_Initial();
    Start_SPI_process(&u8MID,&u8DID);
  
    if((u8MID != 0x4F)&&(u8DID != 0x4E))
        SPI_Error();

    printf ("\n SPI transfer done! ");
    while(1);                                    // SPI transmission finish and P0.6 flash
}

