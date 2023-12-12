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
  SFRS=1;
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
  SFRS=1;
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
  * @note Confirm multi function pin is defined as GPIO first. call function_define_MS51_32K.h to define.
  * @exmaple :   GPIO_SetMode(Port1,BIT0,GPIO_MODE_QUASI);
  */
void GPIO_SetMode(uint8_t u8Port, uint8_t u8PinMask, uint8_t u8Mode)
{
    uint8_t u8PnM1=0, u8PnM2 =0;

    SFRS = 1;
    switch(u8Port)
    {
        case Port0:  u8PnM1 = P0M1;  u8PnM2 = P0M2;  break;
        case Port1:  u8PnM1 = P1M1;  u8PnM2 = P1M2;  break;
        case Port2:  u8PnM1 = P2M1;  u8PnM2 = P2M2;  break;
        case Port3:  u8PnM1 = P3M1;  u8PnM2 = P3M2;  break;
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
        case Port0:  P0M1 = u8PnM1;  P0M2 = u8PnM2;  break;
        case Port1:  P1M1 = u8PnM1;  P1M2 = u8PnM2;  break;
        case Port2:  P2M1 = u8PnM1;  P2M2 = u8PnM2;  break;
        case Port3:  P3M1 = u8PnM1;  P3M2 = u8PnM2;  break;

    }
}
