/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#define EEPROM_ADDRESS          0xA0
#define I2C_WR                     0
#define I2C_RD                     1

#define LOOP_SIZE                 10

uint16_t Tx_Addr, Rx_Addr;
uint8_t Tx_Dat, Rx_Dat;
BIT Write_End_Flag, Read_End_Flag, addr_flag;

void (*I2C_Func)(void);

#if defined __C51__
void I2C_ISR(void) interrupt 6
#elif defined __ICC8051__
#pragma vector=0x33
__interrupt void I2C_ISR(void)
#elif defined __SDCC__
void I2C_ISR(void) __interrupt (6)        // Vector @  0x33
#endif
{
    I2C_Func();
}

/*========================================================================================================*/
void I2C0_Master_Tx_Isr(void)
{
    static uint8_t addr_flag;
    static uint8_t count;

    PUSH_SFRS;
    SFRS = 0;
	
  /* Bus error */
    if (I2STAT == 0x00)
    {
       set_I2CON_STO;
    }

  /* I2C start */    
    else if (I2STAT == 0x08)
    {
        clr_I2CON_STA;
        I2DAT = (EEPROM_ADDRESS | I2C_WR);
    }

  /* Master Transmit Address ACK  */
    else if (I2STAT == 0x18)
    {
        I2DAT = HIBYTE(Rx_Addr);          //address high byte of I2C EEPROM
        addr_flag = 1;
    }

   /* Master Transmit Data ACK  */
    else if (I2STAT == 0x28)
    {
        if(addr_flag)
        {
             I2DAT = LOBYTE(Tx_Addr);      //address low byte of I2C EEPROM
             addr_flag = 0;
             count = 0;
        }
        else
        {
             if(count == 0)
             {
                  I2DAT = Tx_Dat;
                  count++;
             }
             else
             {
                  Write_End_Flag = 1;
                  set_I2CON_STO;
             }
        }
    }

    I2C0_SI_Check();
    POP_SFRS;
}

/*========================================================================================================*/
void I2C0_Master_Rx_Isr(void)
{


    PUSH_SFRS;

    SFRS = 0;
    switch (I2STAT)
    {
       /* Bus error */
       case 0x00: set_I2CON_STO; break;

      /* I2C start */
       case 0x08:
            clr_I2CON_STA;
            I2DAT = (EEPROM_ADDRESS | I2C_WR);
       break;

       /* Master Transmit Address ACK  */
       case 0x18:
            I2DAT = HIBYTE(Rx_Addr);          //address high byte of I2C EEPROM
            addr_flag = 1;
       break;

       /* Master Transmit Data ACK */ 
       case 0x28:
            if(addr_flag==1)
            {
                I2DAT = LOBYTE(Rx_Addr);       //address low byte of I2C EEPROM
                addr_flag = 0;
            }
            else
            {
                set_I2CON_STA;
            }
       break;  

       /* Master Repeat Start  */
       case 0x10: 
           clr_I2CON_STA;
           I2DAT = (EEPROM_ADDRESS | I2C_RD);
       break;

      /* Master Receive Address ACK  */
       case 0x40:  set_I2CON_AA; break;
       
      /* Master Receive Data ACK  */
       case 0x50:
            Rx_Dat = I2DAT;
            set_I2CON_STO;
            Read_End_Flag = 1;
       break;
    }

    I2C0_SI_Check();

POP_SFRS;
}


//========================================================================================================
uint8_t I2C0_Write(uint16_t u16I2Caddr, uint8_t u8I2Cdat)
{
    uint32_t count = 0;

    I2C_Func = I2C0_Master_Tx_Isr;
    Tx_Addr = u16I2Caddr;
    Tx_Dat = u8I2Cdat;

    set_I2CON_STA;             /* Start transmit */
    while(1)
    {
        count++;
        if(Write_End_Flag == 1)
        {
            return 1;
        }
        
        if(count > 100000)
        {
            return 0;
        }
    }
}

/*========================================================================================================*/
uint8_t I2C0_Read(uint16_t u8I2Caddr, uint8_t *u8I2Cdat)
{
    uint32_t count;
    count = 0;
    Read_End_Flag = 0;
    I2C_Func = I2C0_Master_Rx_Isr;
    Rx_Addr = u8I2Caddr;
  
    SFRS=0; printf ("\n Receive data from n24LC64" );
    set_I2CON_STA; 
    
    while(1)
    {
        count++;
        if(Read_End_Flag == 1)
        {
            *u8I2Cdat = Rx_Dat;
            return 1;
        }
        
        if(count > 100000)
        {
            return 0;
        }
    }
}
/*========================================================================================================*/
void Init_I2C(void)
{

    MODIFY_HIRC(HIRC_24);

    /* Set I2C GPIO */
    P13_OPENDRAIN_MODE;          /* External pull high resister in circuit */
    P14_OPENDRAIN_MODE;          /* External pull high resister in circuit */
    set_P1S_3;                   /* Setting schmit tigger mode */
    set_P1S_4;                   /* Setting schmit tigger mode */

    /* Set I2C clock rate and enable, base on 24M i2c clock is 100k */
     I2C_Master_Open(24000000,100000);
    /* Set I2C Interrupt enable*/
     I2C_Interrupt(ENABLE);
     EA=1;
}

/*========================================================================================================*/
void main(void)
{
    uint8_t dat;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n I2C EEPROM intial...");
    Init_I2C();  

        if(I2C0_Write(0x0000, 0x55) == 1)
        {
            Timer0_Delay(24000000,5,1000);
            if(I2C0_Read(0x0000, &dat) == 1)
            {
                if(dat == 0x55)
                {
                    SFRS=0; printf("\n EEPROM write and read Pass! ");
                }
                else
                {
                    printf("\n FAIL! ");
                }
            }
        }

        I2C_Close(); 

        while(1);

}

