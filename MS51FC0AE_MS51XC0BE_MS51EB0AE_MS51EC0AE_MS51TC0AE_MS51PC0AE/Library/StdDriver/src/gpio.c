/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

 /**
  * @brief GPIO Pull up or Pull down enable setting
  * @param[in] u8Port Decides the GPIO port number Port0 ~ Port5
  * @param[in] u8PinMask Decides  bit of the port (SET_BIT0~SET_BIT7 use "|" to define multi bit).
  * @param[in] u8PullMode Decides the GPIO Pull up or pull down (PullUp/PullDown)
  * @return  None
  * @note none
  * @exmaple :   GPIO_Pull_Enable(P1,SET_BIT0|SET_BIT5|SET_BIT7,PullUp);
  */
void GPIO_Pull_Enable(uint8_t u8Port, uint8_t u8PinMask, uint8_t u8PullMode)
{
  SFRS=2;
  switch (u8PullMode)
  {
    case PULLUP:
        switch(u8Port)
        {
          case Port0:  P0UP |= u8PinMask;  break;
          case Port1:  P1UP |= u8PinMask;  break;
          case Port2:  P2UP |= u8PinMask;  break;
          case Port3:  P3UP |= u8PinMask;  break;
        }
    break;
    case PULLDOWN:
        switch(u8Port)
        {
          case Port0:  P0DW |= u8PinMask;  break;
          case Port1:  P1DW |= u8PinMask;  break;
          case Port2:  P2DW |= u8PinMask;  break;
          case Port3:  P3DW |= u8PinMask;  break;
        }
    break;
    }
}


 /**
  * @brief GPIO Pull up or Pull down disable 
  * @param[in] u8Port Decides the GPIO port number Port0 ~ Port5
  * @param[in] u8PinMask Decides  bit of the port (SET_BIT0~SET_BIT7 use "|" to define multi bit).
  * @param[in] u8PullMode Decides the GPIO Pull up or pull down (PullUp/PullDown)
  * @return  None
  * @note none
  * @exmaple :   GPIO_Pull_Enable(P1,CLR_BIT0&CLR_BIT5,PullUp);
  */
void GPIO_Pull_Disable(uint8_t u8Port, uint8_t u8PinMask, uint8_t u8PullMode)
{
  SFRS=2;
  switch (u8PullMode)
  {
    case PullUp:
        switch(u8Port)
        {
          case Port0:  P0UP &= ~u8PinMask;  break;
          case Port1:  P1UP &= ~u8PinMask;  break;
          case Port2:  P2UP &= ~u8PinMask;  break;
          case Port3:  P3UP &= ~u8PinMask;  break;
        }
    break;
    case PullDown:
        switch(u8Port)
        {
          case Port0:  P0DW &= ~u8PinMask;  break;
          case Port1:  P1DW &= ~u8PinMask;  break;
          case Port2:  P2DW &= ~u8PinMask;  break;
          case Port3:  P3DW &= ~u8PinMask;  break;
        }
    break;
    }
}


 /**
  * @brief GPIO mode setting
  * @param[in] u8Port Decides the GPIO port number Port0 ~ Port5
  * @param[in] u8PinMask Decides  bit of the port ( from SET_BIT0~SET_BIT7 use "|" to define multi bit)
  * @param[in] u8Mode Decides the GPIO mode GPIO_MODE_INPUT / GPIO_MODE_PUSHPULL / GPIO_MODE_QUASI / GPIO_MODE_OPENDRAI for mode to select.
  * @return  None
  * @note Confirm multi function pin is defined as GPIO first. call function_define_MG51_64K.h to define.
  * @exmaple :   GPIO_SetMode(Port1,BIT0,GPIO_MODE_QUASI);
  */
void GPIO_SetMode(uint8_t u8Port, uint8_t u8PinMask, uint8_t u8Mode)
{
    uint8_t u8PnM1, u8PnM2;
    u8PnM1=0;
	u8PnM2 =0;
	
    switch(u8Port)
    {
        case Port0:  SFRS=0; u8PnM1 = P0M1;  u8PnM2 = P0M2;  break;
        case Port1:  SFRS=0; u8PnM1 = P1M1;  u8PnM2 = P1M2;  break;
        case Port2:  SFRS=2; u8PnM1 = P2M1;  u8PnM2 = P2M2;  break;
        case Port3:  SFRS=0; u8PnM1 = P3M1;  u8PnM2 = P3M2;  break;
    }
    switch(u8Mode)
    {
        case GPIO_MODE_QUASI:
            u8PnM1 &= u8PinMask;
            u8PnM2 &= u8PinMask;
            break;
        case GPIO_MODE_PUSHPULL:
            u8PnM1 &= ~u8PinMask;
            u8PnM2 |= u8PinMask;
            break;
        case GPIO_MODE_INPUT:
            u8PnM1 |= u8PinMask; 
            u8PnM2 &= ~u8PinMask;
            break;
        case GPIO_MODE_OPENDRAIN:
            u8PnM1 |= u8PinMask;
            u8PnM2 |= u8PinMask;
            break;
    }
    switch(u8Port)
    {
        case Port0:  SFRS=0; P0M1 = u8PnM1;  P0M2 = u8PnM2;  break;
        case Port1:  SFRS=0; P1M1 = u8PnM1;  P1M2 = u8PnM2;  break;
        case Port2:  SFRS=2; P2M1 = u8PnM1;  P2M2 = u8PnM2;  break;
        case Port3:  SFRS=0; P3M1 = u8PnM1;  P3M2 = u8PnM2;  break;
    }
}


 /**
  * @brief GPIO Schmitt Triggered Input enable / disable. 
  * @param[in] u8Port Decides the GPIO port number 
  *                  - \ref Port 0
  *                  - \ref Port 1
  *                  - \ref Port 2
  *                  - \ref Port 3
  *                  - \ref Port 4
  *                  - \ref Port 5
  * @param[in] u8PinMask Decides  bit of the port (SET_BIT0~SET_BIT7 use "|" to define multi bit).
  *                  - \ref SET_BIT0
  *                  - \ref SET_BIT1
  *                  - \ref SET_BIT2
  *                  - \ref SET_BIT3
  *                  - \ref SET_BIT4
  *                  - \ref SET_BIT5
  *                  - \ref SET_BIT6
  *                  - \ref SET_BIT7
  *                  - \ref SET_BIT0|SET_BIT7
  *                  - \ref 0x81
  * @param[in] u8SStauts Decides the GPIO Schmitt Triggered status
  *                  - \ref Enable
  *                  - \ref Disable
  * @return  None
  * @note none
  * @exmaple :   GPIO_Pull_Enable(P1,SET_BIT0 | SET_BIT5,PullUp);
  */
void GPIO_SchmittTrigger(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8SStauts)
{
  SFRS=1;
  switch (u8SStauts)
  {
    case Enable:
        switch(u8Port)
        {
          case Port0:  P0S |= u8PinMask;  break;
          case Port1:  P1S |= u8PinMask;  break;
          case Port2:  SFRS=2; P2S |= u8PinMask;  break;
          case Port3:  P3S |= u8PinMask;  break;
        }
    break;
    case Disable:
        switch(u8Port)
        {
          case Port0:  P0S &= ~u8PinMask;  break;
          case Port1:  P1S &= ~u8PinMask;  break;
          case Port2:  SFRS=2; P2S &= ~u8PinMask;  break;
          case Port3:  P3S &= ~u8PinMask;  break;
        }
    break;
    }
POP_SFRS;
}

 /**
  * @brief GPIO Slew rate Status enable / disable. 
  * @param[in] u8Port Decides the GPIO port number 
  *                  - \ref Port 0
  *                  - \ref Port 1
  *                  - \ref Port 2
  *                  - \ref Port 3
  * @param[in] u8PinMask Decides  bit of the port (SET_BIT0~SET_BIT7 use "|" to define multi bit).
  *                  - \ref SET_BIT0
  *                  - \ref SET_BIT1
  *                  - \ref SET_BIT2
  *                  - \ref SET_BIT3
  *                  - \ref SET_BIT4
  *                  - \ref SET_BIT5
  *                  - \ref SET_BIT6
  *                  - \ref SET_BIT7
  *                  - \ref SET_BIT0|SET_BIT7
  * @param[in] u8SRStauts Decides the GPIO Slew rate status
  *                  - \ref Enable
  *                  - \ref Disable
  * @return  None
  * @note none
  * @exmaple :   GPIO_Pull_Enable(P1,SET_BIT0 | SET_BIT5,PullUp);
  */
void GPIO_SlewRate(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8SRStauts)
{
  SFRS=1;
  switch (u8SRStauts)
  {
    case Enable:
        switch(u8Port)
        {
          case Port0:  P0SR |= u8PinMask;  break;
          case Port1:  P1SR |= u8PinMask;  break;
          case Port2:  SFRS=2; P2SR |= u8PinMask;  break;
          case Port3:  P3SR |= u8PinMask;  break;
        }
    break;
    case Disable:
        switch(u8Port)
        {
          case Port0:  P0SR &= ~u8PinMask;  break;
          case Port1:  P1SR &= ~u8PinMask;  break;
          case Port2:  SFRS=2;P2SR &= ~u8PinMask;  break;
          case Port3:  P3SR &= ~u8PinMask;  break;
        }
    break;
    }
}
