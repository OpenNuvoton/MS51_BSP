/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

BIT   SPCHECKFLAG;
#if defined __C51__
uint8_t xdata sppage_buffer[127];
uint8_t xd_sp_tmp[127];

#elif defined __ICC8051__
uint8_t __xdata sppage_buffer[127];
uint8_t __xdata xd_sp_tmp[127];

#elif defined __SDCC__
uint8_t __xdata sppage_buffer[127];
uint8_t __xdata xd_sp_tmp[127];
#endif

void WriteDataToSPOnePage(uint8_t u8_addr, uint8_t *pDat, uint16_t num);
/**
 * @brief       Read Dataflash
 * @param       Dataflash start address
 * @return      Dataflash Value
 * @details     None
 */
#if defined __C51__
uint8_t Read_SPROM_BYTE(const uint8_t code *u8_addr)
#elif defined __ICC8051__
uint8_t Read_SPROM_BYTE(const uint8_t __code *u8_addr)
#elif defined __SDCC__
uint8_t Read_SPROM_BYTE(const uint8_t __code *u8_addr)
#endif
{
    uint8_t rdata;
    set_IAPUEN_SPMEN;
    rdata = *(0xFF80+u8_addr);
    return rdata;
}

/**
 * @brief       Write SPROM as EEPROM, 
 * @param       u16EPAddr the 9bit SPROM start address. Any of SPROM address can be defined as start address escept last byte.
 * @param       u8EPData the 8bit value need storage in (0x3800)
 * @return      none
 * @details     Storage dataflash page data into XRAM, modify data in XRAM, Erase dataflash page, writer updated XRAM data into dataflash
 */
void Read_SPROM_DATAFLASH_ARRAY(uint16_t u8_addr, uint8_t *pDat, uint16_t num)
{
    uint16_t i;

    set_IAPUEN_SPMEN;
    for (i = 0; i < num; i++)
    {
#if defined __C51__
        pDat[i] = *(uint8_t code *)(u8_addr+0xFF80 + i);
#elif defined __ICC8051__
        pDat[i] = *(uint8_t __code *)(u8_addr+0xFF80 + i);
#elif defined __SDCC__
        pDat[i] = *(uint8_t __code *)(u8_addr+0xFF80 + i);
#endif
    }
}

/**
 * @brief       Write SPROM as EEPROM with array format
 * @param       u8_addr the 8bit EEPROM start address. Any of APROM address can be defined as start address 
 * @param       pDat the 8bit value need storage in 
 * @param       num the number that need to write.
 * @return      none
 */
uint8_t Write_SPROM_DATAFLASH_ARRAY(uint8_t u8_addr, uint8_t *pDat, uint16_t num)
{
    SPCHECKFLAG = 0;
    WriteDataToSPOnePage(u8_addr,pDat,num);
    return SPCHECKFLAG;
}
//-------------------------------------------------------------------------
void WriteDataToSPOnePage(uint8_t u8_addr, uint8_t *pDat, uint16_t num)
{
#if defined __C51__
    uint8_t code *pCode;
#elif defined __ICC8051__
    uint8_t __code *pCode;
#elif defined __SDCC__
    uint8_t __code *pCode;
#endif
    uint8_t i,checkdatatemp;

    set_CHPCON_IAPEN;
    set_IAPUEN_SPMEN;
    set_IAPUEN_SPUEN;
    
#if defined __C51__
    pCode = (uint8_t code *)u8_addr;
#elif defined __ICC8051__
    pCode = (uint8_t __code *)u8_addr;
#elif defined __SDCC__
    pCode = (uint8_t __code *)u8_addr;
#endif

    for(i=0;i<127;i++)
    {
#if defined __C51__
        xd_sp_tmp[i] = Read_SPROM_BYTE((uint8_t code *)i);
#elif defined __ICC8051__
        xd_sp_tmp[i] = Read_SPROM_BYTE((uint8_t __code *)i);
#elif defined __SDCC__
        xd_sp_tmp[i] = Read_SPROM_BYTE((uint8_t __code *)i);
#endif
    }
    for(i=0;i<num;i++)
    {
        xd_sp_tmp[u8_addr+i] = pDat[i];
    }

    IAPCN = PAGE_ERASE_SPROM;
    IAPAL = 0x80;
    IAPAH = 0x01;
    IAPFD = 0xFF;
    set_IAPTRG_IAPGO; 

    for(i=0;i<127;i++)
    {
        IAPCN =BYTE_PROGRAM_SPROM;
        IAPFD = xd_sp_tmp[i];
        set_IAPTRG_IAPGO;
        IAPCN =BYTE_READ_SPROM;
        IAPFD = 0xFF;
        set_IAPTRG_IAPGO;
        checkdatatemp = IAPFD;
        if (checkdatatemp!=xd_sp_tmp[i])
        {
             SPCHECKFLAG = 1;
             goto WriteDataToSPEnd;
        }
        IAPAL++;
    }
    for(i=0;i<127;i++)
    {
      if(pCode[i]!=xd_sp_tmp[i])break;
    }
WriteDataToSPEnd:
    clr_IAPUEN_SPUEN;
    clr_CHPCON_IAPEN;
}


