/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"


BIT  EECHECKFLAG;
#if defined __C51__
volatile uint8_t xdata page_buffer[128];
volatile uint8_t xdata xd_tmp[128];

#elif defined __ICC8051__
uint8_t __xdata page_buffer[128];
uint8_t __xdata xd_tmp[128];

#elif defined __SDCC__
uint8_t __xdata page_buffer[128];
uint8_t __xdata xd_tmp[128];
#endif

uint8_t WriteDataToOnePage(uint16_t u16_addr,const uint8_t *pDat,uint8_t num);

/**
 * @brief       Write Dataflash as EEPROM, 
 * @param       u16EPAddr the 16bit EEPROM start address. Any of APROM address can be defined as start address (0x3800)
 * @param       u8EPData the 8bit value need storage in (0x3800)
 * @return      none
 * @details     Storage dataflash page data into XRAM, modify data in XRAM, Erase dataflash page, writer updated XRAM data into dataflash
 */
uint8_t Write_DATAFLASH_BYTE(uint16_t u16EPAddr, uint8_t u8EPData)
{
    uint8_t   looptmp,RAMtmp,checkdatatemp;
    uint16_t  u16_addrl_r;

    EECHECKFLAG = 0;
  /* Check page start address  */
    u16_addrl_r=(u16EPAddr/128)*128;
  /*Save APROM data to XRAM0  */
    for(looptmp=0;looptmp<0x80;looptmp++)
    {
#if defined __C51__
        RAMtmp = Read_APROM_BYTE((uint16_t code *)(u16_addrl_r+looptmp));
#elif defined __ICC8051__
        RAMtmp = Read_APROM_BYTE((uint16_t __code *)(u16_addrl_r+looptmp));
#elif defined __SDCC__
        RAMtmp = Read_APROM_BYTE((uint16_t __code *)(u16_addrl_r+looptmp));
#endif
        page_buffer[looptmp]=RAMtmp;
    }
  /* Modify customer data in XRAM */
    page_buffer[u16EPAddr&0x7f] = u8EPData;

  /* Erase APROM DATAFLASH page  */
    IAPAL = u16_addrl_r&0xff;
    IAPAH = (u16_addrl_r>>8)&0xff;
    IAPFD = 0xFF;
    set_CHPCON_IAPEN; 
    set_IAPUEN_APUEN;
    IAPCN = PAGE_ERASE_APROM;
    set_IAPTRG_IAPGO; 

  /* Save changed RAM data to APROM DATAFLASH  */

    for(looptmp=0;looptmp<0x80;looptmp++)
    {
        IAPAL = (u16_addrl_r&0xff)+looptmp;
        IAPAH = (u16_addrl_r>>8)&0xff;
        IAPCN = BYTE_PROGRAM_APROM;
        IAPFD = page_buffer[looptmp];
        set_IAPTRG_IAPGO;
        IAPCN = BYTE_READ_APROM;
        IAPFD = 0xFF;
        set_IAPTRG_IAPGO;
        checkdatatemp = IAPFD;
        if (checkdatatemp!= page_buffer[looptmp])
        {
          EECHECKFLAG = 1;
          goto WriteByteEnd;
        }
    }
WriteByteEnd:
    clr_IAPUEN_APUEN;
    clr_CHPCON_IAPEN;
    
    return EECHECKFLAG;
}


/**
 * @brief       Read Dataflash as array format 
 * @param       u16_addr the 16bit EEPROM start address. Any of APROM address can be defined as start address
 * @param       *pDat the 8bit value
 * @param       num the number that need read.
 * @return      storage the data into pDat[i] array.
 */
void Read_DATAFLASH_ARRAY(uint16_t u16_addr, uint8_t *pDat, uint16_t num)
{
    uint16_t i;

    for(i=0;i<num;i++)
    {
#if defined __C51__
        pDat[i] = *(uint8_t code *)(u16_addr+i);
#elif defined __ICC8051__
        pDat[i] = *(uint8_t __code *)(u16_addr+i);
#elif defined __SDCC__
        pDat[i] = *(uint8_t __code *)(u16_addr+i);
#endif
    }
}


/**
 * @brief       Write Dataflash as EEPROM with array format
 * @param       u16_addr the 16bit EEPROM start address. Any of APROM address can be defined as start address 
 * @param       pDat the 8bit value need storage in 
 * @param       num the number that need to write.
 * @return      none
 */
uint8_t  Write_DATAFLASH_ARRAY(uint16_t u16_addr, uint8_t *pDat, uint16_t num)
{
    uint8_t CPageAddr,EPageAddr,cnt;

    EECHECKFLAG=0;
    CPageAddr=u16_addr>>7;
    EPageAddr=(u16_addr+num)>>7;
    while(CPageAddr!=EPageAddr)
    {
        cnt=WriteDataToOnePage(u16_addr,pDat,128);
        u16_addr+=cnt;
        pDat+=cnt;
        num-=cnt;
        CPageAddr=u16_addr>>7;
    }
    if(num)
    {
        WriteDataToOnePage(u16_addr,pDat,num);
    }
    return EECHECKFLAG;
}

//---------------------------------------------------------------------------------
uint8_t WriteDataToOnePage(uint16_t u16_addr,const uint8_t *pDat,uint8_t num)
{
  
#if defined __C51__
  uint8_t code *pCode;
#elif defined __ICC8051__
  uint8_t __code *pCode;
#elif defined __SDCC__
  uint8_t __code *pCode;
#endif
  uint8_t i,offset,checkdatatemp;

    set_CHPCON_IAPEN; 
    set_IAPUEN_APUEN;

    offset=u16_addr&0x007F;
    i = PAGE_SIZE - offset;
    if(num>i)num=i;
#if defined __C51__
    pCode = (uint8_t code *)u16_addr;
#elif defined __ICC8051__
    pCode = (uint8_t __code *)u16_addr;
#elif defined __SDCC__
    pCode = (uint8_t __code *)u16_addr;
#endif

    for(i=0;i<num;i++)
    {
        if(pCode[i]!=0xFF)break;
    }
    if(i==num)
    {

        IAPAL = u16_addr;
        IAPAH = u16_addr>>8;
        for(i=0;i<num;i++)
        {
          IAPCN =BYTE_PROGRAM_APROM;
          IAPFD = pDat[i];
          set_IAPTRG_IAPGO;
          IAPCN =BYTE_PROGRAM_APROM;
          IAPFD = 0xFF;
          set_IAPTRG_IAPGO;
          checkdatatemp = IAPFD;
          if (checkdatatemp!=pDat[i])
          {
            EECHECKFLAG = 1; 
            goto WriteDataEnd;
          }
          IAPAL++;
        }
        for(i=0;i<num;i++)
        {
          if(pCode[i]!=pDat[i])break;
        }
        if(i!=num) goto WriteDataToPage20;
    }
    else
    {
WriteDataToPage20:
#if defined __C51__
        pCode = (uint8_t code *)(u16_addr&0xff80);
#elif defined __ICC8051__
        pCode = (uint8_t __code *)(u16_addr&0xff80);
#elif defined __SDCC__
        pCode = (uint8_t __code *)(u16_addr&0xff80);
#endif

        for(i=0;i<128;i++)
        {
          xd_tmp[i] = pCode[i];
        }
        for(i=0;i<num;i++)
        {
          xd_tmp[offset+i] = pDat[i];
        }
        do
        {
          IAPAL = (u16_addr&0xff80);
          IAPAH = u16_addr>>8;
          IAPCN = PAGE_ERASE_APROM;
          IAPFD = 0xFF;  
          set_IAPTRG_IAPGO; 
          for(i=0;i<128;i++)
          {
            IAPCN =BYTE_PROGRAM_APROM;
            IAPFD = xd_tmp[i];
            set_IAPTRG_IAPGO;
            IAPCN =BYTE_READ_APROM;
            IAPFD = 0xFF;
            set_IAPTRG_IAPGO;
            checkdatatemp = IAPFD;
            if (checkdatatemp!=xd_tmp[i])
            {
              EECHECKFLAG = 1; 
              goto WriteDataEnd;
            }
            IAPAL++;
          }
          for(i=0;i<128;i++)
          {
            if(pCode[i]!=xd_tmp[i])break;
          }
        }while(i!=128);
    }
WriteDataEnd:
    clr_CHPCON_IAPEN;

    return num;
}
