/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"


#define I2C_CLOCK                 14
#define I2C_SLAVE_ADDRESS         0xA4
#define I2C_WR                    0
#define I2C_RD                    1

#define LOOP_SIZE                 10

BIT   i2cErrorFlag;

#if defined __C51__
void Timer0_ISR (void) interrupt 1        // Vector @  0x0B

#elif defined __ICC8051__
#pragma vector=0x33
__interrupt void Pin_INT_ISR(void)

#elif defined __SDCC__
void Timer0_ISR (void) __interrupt (1)        // Vector @  0x0B
#endif
{
    SFRS_TMP = SFRS;              /* for SFRS page */
      SFRS = 0;
      i2cErrorFlag = 1;
      clr_TCON_TF0;
    if (SFRS_TMP)                 /* for SFRS page */
    {
      ENABLE_SFR_PAGE1;
    }
}
//========================================================================================================
void Init_I2C(void)
{
    P13_OPENDRAIN_MODE;          // Modify SCL pin to Open drain mode. don't forget the pull high resister in circuit
    P14_OPENDRAIN_MODE;          // Modify SDA pin to Open drain mode. don't forget the pull high resister in circuit

    ENABLE_P13_ST_MODE;          //Enable Schemitt trig mode
    ENABLE_P14_ST_MODE;

    /* Set I2C clock rate */
    I2CLK = I2C_CLOCK;
   /* Enable I2C time out divier as clock base is Fsys/4, the time out is about 4ms when Fsys = 16MHz */
    set_I2TOC_DIV;
    clr_I2TOC_I2TOF;
   /* Enable I2C intterupt for I2C time out */
    ENABLE_I2C_INTERRUPT;                               //enable I2C interrupt by setting IE1 bit 0


    /* Enable I2C */
    set_I2CON_I2CEN;
}
//========================================================================================================

//--------------------------------------------------------------------------------------------
//----  Page Write----------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void I2C_Write_Process(uint8_t u8DAT)
{
    uint8_t  u8Count;

    set_I2TOC_I2TOCEN;                           /* Enable I2C time out */

    /* Write Step1 */
    set_I2CON_STA;                              /* Send Start bit to I2C EEPROM */
    clr_I2CON_SI;
    while (!SI)                                /*Check SI set or not  */
    {
      if (i2cErrorFlag)
        goto I2CWRSTOP;
    }
    if (I2STAT != 0x08)                         /*Check status value after every step   */
    {
        i2cErrorFlag=1;
        goto I2CWRSTOP;
    }
    Timer0_AutoReload_Interrupt_CounterClear();

    /* Write Step2 */
    clr_I2CON_STA;                              /*STA=0*/
    I2DAT = (I2C_SLAVE_ADDRESS | I2C_WR);
    clr_I2CON_SI;
    while (!SI);                                /*Check SI set or not */
    if (I2STAT != 0x18)
    {
        i2cErrorFlag=1;
        goto I2CWRSTOP;
    }
    Timer0_AutoReload_Interrupt_CounterClear();

    /* Write Step3 */
    for (u8Count = 0; u8Count < LOOP_SIZE; u8Count++)
    {
        I2DAT = u8DAT;
        clr_I2CON_SI;
        while (!SI);                            /*Check SI set or not*/
        if (I2STAT != 0x28)
        {
            i2cErrorFlag=1;
            goto I2CWRSTOP;
        }
        u8DAT = ~u8DAT;
    }
    Timer0_AutoReload_Interrupt_CounterClear();
    /* Write Step4 */
    I2CWRSTOP:
    if  (i2cErrorFlag)
    {
      printf ("\n I2C write error !");
      i2cErrorFlag = 0;
    }

    set_I2CON_STO;
    clr_I2CON_SI;
    while (STO);                                /* Check STOP signal */
  }
  
//--------------------------------------------------------------------------------------------
//----  Page Read ----------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void I2C_Read_Process(uint8_t u8DAT)
{
    uint8_t  u8Count;

    Timer0_AutoReload_Interrupt_CounterClear();
    /* Read Step1 */
    set_I2CON_STA;
    clr_I2CON_SI;          
    while (!SI);                                //Check SI set or not
	    {
        if (i2cErrorFlag)
        goto I2CRDSTOP;
      }
    if (I2STAT != 0x08)                         //Check status value after every step
    {
        i2cErrorFlag=1;
        goto I2CRDSTOP;
    }
    Timer0_AutoReload_Interrupt_CounterClear();

    /* Step13 */
    clr_I2CON_STA;                                    //STA needs to be cleared after START codition is generated
    I2DAT = (I2C_SLAVE_ADDRESS | I2C_RD);
    clr_I2CON_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x40)              
    {
        i2cErrorFlag=1;
        goto I2CRDSTOP;
    }
    Timer0_AutoReload_Interrupt_CounterClear();

    /* Step14 */
    for (u8Count = 0; u8Count <LOOP_SIZE; u8Count++)
    {
        set_I2CON_AA;
        clr_I2CON_SI;        
        while (!SI);                            //Check SI set or not
        if (I2STAT != 0x50)
        {
            i2cErrorFlag=1;
            goto I2CRDSTOP;
        }
        if (I2DAT != u8DAT)
        {
            i2cErrorFlag=1;
            goto I2CRDSTOP;
        }
        u8DAT = ~u8DAT;
    } 
    Timer0_AutoReload_Interrupt_CounterClear();

    /* Step15 */
    clr_I2CON_AA;
    clr_I2CON_SI;
    while (!SI);                                //Check SI set or not
    if (I2STAT != 0x58)
    {
        i2cErrorFlag=1;
        goto I2CRDSTOP;
    }
    Timer0_AutoReload_Interrupt_CounterClear();

    /* Step16 */
    I2CRDSTOP:
    while (STO);                                /* Check STOP signal */
    {
      printf ("\n I2C read error !");
      i2cErrorFlag = 0;
    }
    set_I2CON_STO;
    clr_I2CON_SI;
    while (STO);                                /* Check STOP signal */
}
//========================================================================================================
void main(void)
{
    /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");

    Init_I2C();                                 /* initial I2C circuit  */
    Timer0_AutoReload_Interrupt_Initial(8,450); /* about 50ms time-out. Always clear counter in transmit */
    ENABLE_GLOBAL_INTERRUPT;

    I2C_Write_Process(0x55);                /* I2C Master will send 10 byte 0x55,0xAA,.... to slave */
    I2C_Read_Process(0x55);

    while (1);
/* =================== */
}

