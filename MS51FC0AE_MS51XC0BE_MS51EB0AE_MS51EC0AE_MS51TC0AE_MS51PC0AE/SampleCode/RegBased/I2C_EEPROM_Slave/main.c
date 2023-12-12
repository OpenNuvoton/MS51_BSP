/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#define I2C_SLAVE_ADDRESS         0xA0
#define LOOP_SIZE                 10

#define SDA                       P14
#define SCL                       P13

uint8_t  data_received[34], data_num;
uint16_t  u16PageOffset_HB,u16ReadAddress;
BIT  I2CWOVERFLAG;

/**
  * @brief     I2C interrupt vector.
  * @param[in] Vector 0x38 (6).
  * @return    None.
*/
#if defined __C51__
void I2C0_ISR(void) interrupt 6
#elif defined __ICC8051__
#pragma vector=0x33
__interrupt void I2C_ISR(void)
#elif defined __SDCC__
void I2C0_ISR(void) __interrupt (6)
#endif
{
    PUSH_SFRS;             /* for SFRS page */
    SFRS = 0;

    if (I2STAT == 0x00)
    {
        set_I2CON_STO;
        while(STO);
    }
    else if (I2STAT == 0x60)
    {
        set_I2CON_AA;
    }
    else if (I2STAT == 0x68)
    {
        clr_I2CON_AA;
    }
    else if (I2STAT == 0x80)
    {
        data_received[data_num] = I2DAT;
        u16ReadAddress = (data_received[0]<<8) + data_received[1];  //This for read process
        data_num++;
        if (data_num == 32)   /* 2 byte address + 30 bytes Data */
        {
            clr_I2CON_AA;
        }
        else
        {
            set_I2CON_AA;
        }
    }
    else if (I2STAT == 0x88)
    {
        data_received[data_num] = I2DAT;
        data_num = 0;
        clr_I2CON_AA;
    }
    else if (I2STAT == 0xA0)
    {
        if (data_num>20)
        {
            I2CWOVERFLAG = 1 ;
        }
        data_num =0;
        set_I2CON_AA;
    }
    else if (I2STAT == 0xA8)
    {
#if defined __C51__
            I2DAT = Read_APROM_BYTE((uint16_t code *)(u16ReadAddress+data_num));
#elif defined __ICC8051__
            I2DAT = Read_APROM_BYTE((uint16_t __code*)(u16ReadAddress+data_num));
#elif defined __SDCC__
            I2DAT = Read_APROM_BYTE((uint16_t __code*)(u16ReadAddress+data_num));
#endif
            data_num++;
            set_I2CON_AA;
    }
    else if (I2STAT == 0xB8)
    {
#if defined __C51__
            I2DAT = Read_APROM_BYTE((uint16_t code *)(u16ReadAddress+data_num));
#elif defined __ICC8051__
            I2DAT = Read_APROM_BYTE((uint16_t __code*)(u16ReadAddress+data_num));
#elif defined __SDCC__
            I2DAT = Read_APROM_BYTE((uint16_t __code*)(u16ReadAddress+data_num));
#endif
            data_num++;
            set_I2CON_AA;
    }
    else if (I2STAT == 0xC0)
    {
            data_num = 0;
            set_I2CON_AA;
    }
    else if (I2STAT == 0xC8)
    {
            set_I2CON_AA;
    }

    I2C0_SI_Check();

    POP_SFRS;
}

//========================================================================================================
void Init_I2C_Slave_Interrupt(void)
{
    P13_OPENDRAIN_MODE;          /* External pull high resister in circuit */
    P14_OPENDRAIN_MODE;          /* External pull high resister in circuit */
    set_P1S_3;                   /* Setting schmit tigger mode */
    set_P1S_4;                   /* Setting schmit tigger mode */

    SDA = 1;                     /* set SDA and SCL pins high */
    SCL = 1;

    I2C_Slave_Open(I2C_SLAVE_ADDRESS) ;
    I2C_Interrupt(ENABLE);
}


/******************************
  * @brief     Main loop.
  * @param[in] None.
  * @return    None.
******************************/
void main(void)
{

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();

  /* Initial I2C function */
    I2CWOVERFLAG = 0;
    Init_I2C_Slave_Interrupt();                                 //initial I2C circuit
    EA =1;

    while (1)
    {
         if (I2CWOVERFLAG )
        {
           /* After receive storage in dataflash */
           u16PageOffset_HB =  (data_received[0]<<8) + data_received[1];
           Write_DATAFLASH_ARRAY(u16PageOffset_HB, data_received+2, 32);
           I2CWOVERFLAG = 0;
        }
     }

}
