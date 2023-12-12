/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"
#include "isp_i2c.h"

#define   SDA   P04
#define   SCL   P03
#define  ADDR_SLA              0xC0 //0x60<<1

BIT volatile bI2CDataReady;
BIT volatile bISPDataReady;//for ack
BIT volatile g_timer0Over;
BIT volatile g_timer1Over;
BIT volatile g_progarmflag;
BIT BIT_TMP;

#if defined __C51__
xdata volatile uint8_t rx_buf[64];
xdata volatile uint8_t tx_buf[64];
data volatile uint16_t flash_address;
data volatile uint16_t AP_size;
data volatile uint8_t g_timer1Counter;
data volatile uint8_t count;
data volatile uint16_t g_timer0Counter;
data volatile uint32_t g_checksum;
data volatile uint32_t g_totalchecksum;
data volatile uint8_t g_u8SlvDataLen;

data uint8_t PID_highB,PID_lowB,DID_highB,DID_lowB,CONF0,CONF1,CONF2,CONF4;
data uint8_t recv_CONF0,recv_CONF1,recv_CONF2,recv_CONF4;

#elif defined __ICC8051__
__xdata volatile uint8_t rx_buf[64];
__xdata volatile uint8_t tx_buf[64];
__data volatile uint16_t flash_address;
__data volatile uint16_t AP_size;
__data volatile uint8_t g_timer1Counter;
__data volatile uint8_t count;
__data volatile uint16_t g_timer0Counter;
__data volatile uint32_t g_checksum;
__data volatile uint32_t g_totalchecksum;
__data volatile uint8_t g_u8SlvDataLen;

__data uint8_t PID_highB,PID_lowB,DID_highB,DID_lowB,CONF0,CONF1,CONF2,CONF4;
__data uint8_t recv_CONF0,recv_CONF1,recv_CONF2,recv_CONF4;

#elif defined __SDCC__
__xdata volatile uint8_t rx_buf[64];
__xdata volatile uint8_t tx_buf[64];
__data volatile uint16_t flash_address;
__data volatile uint16_t AP_size;
__data volatile uint8_t g_timer1Counter;
__data volatile uint8_t count;
__data volatile uint16_t g_timer0Counter;
__data volatile uint32_t g_checksum;
__data volatile uint32_t g_totalchecksum;
__data volatile uint8_t g_u8SlvDataLen;

__data uint8_t PID_highB,PID_lowB,DID_highB,DID_lowB,CONF0,CONF1,CONF2,CONF4;
__data uint8_t recv_CONF0,recv_CONF1,recv_CONF2,recv_CONF4;
#endif

void READ_ID(void)
{
    set_CHPCON_IAPEN;
    IAPCN = READ_DID;
    IAPAH = 0x00;
    IAPAL = 0x00;
    trig_IAPGO;
    DID_lowB = IAPFD;
    IAPAL = 0x01;
    trig_IAPGO;
    DID_highB = IAPFD;
    IAPAL = 0x02;
    trig_IAPGO;
    PID_lowB = IAPFD;
    IAPAL = 0x03;
    trig_IAPGO;
    PID_highB = IAPFD;
}
void READ_CONFIG(void)
{
    IAPCN = BYTE_READ_CONFIG;
    IAPAL = 0x00;
    IAPAH = 0x00;
    trig_IAPGO;
    CONF0 = IAPFD;
    IAPAL = 0x01;
    trig_IAPGO;
    CONF1 = IAPFD;
    IAPAL = 0x02;
    trig_IAPGO;
    CONF2 = IAPFD;
    IAPAL = 0x04;
    trig_IAPGO;
    CONF4 = IAPFD;
    clr_CHPCON_IAPEN;
}

void TM0_ini(void)
{    
  TH0=TL0=0;    //interrupt timer 140us
  set_TCON_TR0;      //Start timer0
  set_IPH_PSH;       // Serial port 0 interrupt level2
  set_IE_ET0;
}

void Package_checksum(void)
{
   uint32_t  temp32;
   
   temp32=0;
   for(count=0;count<64;count++)
  {
    temp32 = temp32 + rx_buf[count];    
  }
  g_checksum = temp32;
  
  tx_buf[0]=g_checksum&0xff;
  tx_buf[1]=(g_checksum>>8)&0xff;
  tx_buf[4]=rx_buf[4]+1;
  tx_buf[5]=rx_buf[5];
  if(tx_buf[4]==0x00)
  tx_buf[5]++;
}

void Init_I2C(void)
{
    P13_OPENDRAIN_MODE;                         //set SCL (P13) is Opendrain mode
    P14_OPENDRAIN_MODE;                         //set SDA (P14) is Opendrain mode
    
    P14 = 1 ;                                  //SDA = 1; set SDA and SCL pins high
    P13 = 1;                                   //SCL = 1;
    set_EIE_EI2C;                               //enable I2C interrupt by setting IE1 bit 0
    set_I2CON_I2CEN;                              //enable I2C circuit 
    I2ADDR = ADDR_SLA;                    //define own slave address    
    SI = 0;
    AA = 1;
    EA=1;
}

