/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2024 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#define I2C_CLOCK                 13
#define I2C_SLAVE_ADDRESS         0xA4
#define LOOP_SIZE                 10 

#define SDA                       P14
#define SCL                       P13

uint8_t data_received[34], data_num ;

//========================================================================================================
#if defined __C51__
void I2C0_ISR(void) interrupt 6
#elif defined __ICC8051__
#pragma vector=0x33
__interrupt void I2C_ISR(void)
#elif defined __SDCC__
void I2C0_ISR(void) __interrupt (6)
#endif
{
    if (I2STAT == 0x00)
    {
        STO = 1;
        while(STO);
    }
    else if (I2STAT == 0x60)
    {
            AA = 1;
    }
    else if (I2STAT == 0x68)
    {
         P02 = 0;
         while(1);
    }
    else if (I2STAT == 0x80)
    {
         data_received[data_num] = I2DAT;
         data_num++;
         if (data_num == LOOP_SIZE)
         {
             data_num = 0;
             AA = 0;
         }
         else
         {
             AA = 1;
         }
    }
    else if  (I2STAT == 0x88)
    {
            data_received[data_num] = I2DAT;
            data_num = 0;
            AA = 1;
    }
    else if  (I2STAT == 0xA0)
    {
        AA = 1;
    }
    else if  (I2STAT == 0xA8)
    {
        I2DAT = data_received[data_num];
        data_num++;
        AA = 1;
    }
    else if  (I2STAT == 0xB8)
    {
        I2DAT = data_received[data_num];
        data_num++;
        AA = 1;
    }
    else if  (I2STAT == 0xC0)
    {
            AA = 1;
    }
    else if  (I2STAT == 0xC8)
    {
            AA = 1;
    } 
    SI = 0;
}

//========================================================================================================
void Init_I2C_SLAVE(void)
{
    P13_OPENDRAIN_MODE;           /* set SCL (P13) is Open Drain mode, external pull up resister is necessary */
    P14_OPENDRAIN_MODE;           /* set SDA (P14) is Open Drain mode, external pull up resister is necessary */
    set_P1S_3;                    /* Setting schmit tigger mode */
    set_P1S_4;                    /* Setting schmit tigger mode */

    SDA = 1;                      /* set SDA and SCL pins high */
    SCL = 1;

    ENABLE_I2C_INTERRUPT;         /* enable I2C interrupt by setting IE1 bit 0 */
    ENABLE_GLOBAL_INTERRUPT;

    I2C_Slave_Open(0xA4);
}

//========================================================================================================
void main(void)
{

    /* Initial I2C function */
    Init_I2C_SLAVE();            /*initial I2C circuit  */

    while (1);
}

