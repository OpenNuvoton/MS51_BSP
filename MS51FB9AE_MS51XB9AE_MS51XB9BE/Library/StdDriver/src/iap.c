/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#if defined __C51__
uint8_t xdata DIDBuffer[2];
uint8_t xdata PIDBuffer[2];
uint8_t xdata UIDBuffer[12];
uint8_t xdata UCIDBuffer[12];
uint8_t xdata IAPDataBuf[128];
uint8_t xdata IAPCFBuf[5];
BIT  ConfigModifyFlag;

#elif defined __ICC8051__
uint8_t __xdata DIDBuffer[2];
uint8_t __xdata PIDBuffer[2];
uint8_t __xdata UIDBuffer[12];
uint8_t __xdata UCIDBuffer[12];
uint8_t __xdata IAPDataBuf[128];
uint8_t __xdata IAPCFBuf[5];
BIT  ConfigModifyFlag;

#elif defined __SDCC__
__xdata volatile uint8_t DIDBuffer[2];
__xdata volatile uint8_t PIDBuffer[2];
__xdata volatile uint8_t UIDBuffer[12];
__xdata volatile uint8_t UCIDBuffer[12];
__xdata volatile uint8_t IAPDataBuf[128];
__xdata volatile uint8_t IAPCFBuf[5];
BIT  ConfigModifyFlag;
#endif


/**
 * @brief       Erase LDROM  
 * @param       u16IAPStartAddress #include "ms51_8k.h" LDROM area start address
 * @param       u16IAPDataSize #include "ms51_8k.h" LDROM need be erase bytes size
 * @return      none
 * @details     Page erase LDROM area base on data start address 
 * @example      Erase_LDROM(0x0000,2048);
 */
void Erase_LDROM(uint16_t u16IAPStartAddress,uint16_t u16IAPDataSize)
{   
    uint16_t u16Count;

    set_CHPCON_IAPEN;                    // Enable IAP function
    set_IAPUEN_LDUEN;                    //  LDROM modify Enable
    IAPFD = 0xFF;                        // IMPORTANT !! To erase function must setting IAPFD = 0xFF 
    IAPCN = PAGE_ERASE_LDROM;
    for(u16Count=0x0000;u16Count<(u16IAPDataSize/PAGE_SIZE);u16Count++)            // Loop page erase LDROM special #include "ms51_8k.h" address area.
    {        
        IAPAL = LOBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        IAPAH = HIBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        set_IAPTRG_IAPGO_WDCLR;
    } 
    clr_IAPUEN_LDUEN;                    // Disable LDROM modify 
    clr_CHPCON_IAPEN;                    // Disable IAP
}

/**
 * @brief       LDROM blank check
 * @param       u16IAPStartAddress #include "ms51_8k.h" LDROM area start address
 * @param       u16IAPDataSize #include "ms51_8k.h" LDROM need be erase bytes size
 * @return      none
 * @details     Check each byte of LDROM is FFH or not.
 * @example      LDROM_BlanckCheck(0x0000,2048);
 */
void Erase_Verify_LDROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize)
{   
    uint16_t u16Count;
    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_LDROM;

    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;    
        set_IAPTRG_IAPGO;
        if(IAPFD != 0xFF)
          while(1);
        IAPAL++;
        if(IAPAL == 0x00)
          IAPAH++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       LDROM program loop
 * @param       u16IAPStartAddress #include "ms51_8k.h" LDROM area start address
 * @param       u16IAPDataSize #include "ms51_8k.h" LDROM need be erase bytes size
 * @return      none
 * @details     Copy IAPDataBuf to LDROM
 * @example      LDROM_Program(0x0000,1024);
 */
void Program_LDROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize)
{   
    uint16_t u16Count;

    set_CHPCON_IAPEN;
    set_IAPUEN_LDUEN;    
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_PROGRAM_LDROM;
    
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = IAPDataBuf[u16Count];     
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_IAPUEN_LDUEN;
    clr_CHPCON_IAPEN;
}


/**
 * @brief       LDROM check loop
 * @param       u16IAPStartAddress #include "ms51_8k.h" LDROM area start address
 * @param       u16IAPDataSize #include "ms51_8k.h" LDROM need be erase bytes size
 * @return      none
 * @details     Check with XRAM IAPDataBuf with LDROM
 * @example      LDROM_Program_Verify(0x0000,1024);
 */
void Program_Verify_LDROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize)
{   
    uint16_t u16Count;

    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_LDROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        if (IAPFD != IAPDataBuf[u16Count])    
            while(1);
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Erase APROM  
 * @param       u16IAPStartAddress #include "ms51_8k.h" APROM area start address
 * @param       u16IAPDataSize #include "ms51_8k.h" LDROM need be erase bytes size
 * @return      none
 * @details     Page erase APROM area base on data start address 
 * @example      Erase_APROM(0x0000,2048);
 */
void Erase_APROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize)
{   
    uint16_t u16Count;

    set_CHPCON_IAPEN;                    // Enable IAP function
    set_IAPUEN_APUEN;                    // APROM modify Enable
    IAPFD = 0xFF;                        // IMPORTANT !! To erase function must setting IAPFD = 0xFF 
    IAPCN = PAGE_ERASE_APROM;
    for(u16Count=0x0000;u16Count<u16IAPDataSize/PAGE_SIZE;u16Count++)            // Loop page erase APROM special #include "ms51_8k.h" address area.
    {        
        IAPAL = LOBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        IAPAH = HIBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        set_IAPTRG_IAPGO_WDCLR; 
    } 
    clr_IAPUEN_APUEN;                    // Disable APROM modify 
    clr_CHPCON_IAPEN;                    // Disable IAP
}

/**
 * @brief       APROM blank check
 * @param       u16IAPStartAddress #include "ms51_8k.h" APROM area start address
 * @param       u16IAPDataSize #include "ms51_8k.h" APROM need be erase bytes size
 * @return      none
 * @details     Check each byte of APPROM is FFH or not.
 * @example      APROM_Blank_Check(0x0000,2048);
 */
void Erase_Verify_APROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize)
{   
    uint16_t u16Count;
  
    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_APROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;    
        set_IAPTRG_IAPGO;
        if(IAPFD != 0xFF)
          while(1);
        IAPAL++;
        if(IAPAL == 0x00)
          IAPAH++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       APROM program loop
 * @param       u16IAPStartAddress #include "ms51_8k.h" APROM area start address
 * @param       u16IAPDataSize #include "ms51_8k.h" APROM need be erase bytes size
 * @return      none
 * @details     Copy APDataBuf to APROM
 * @example      APROM_Program(0x0000,1024);
 */
void Program_APROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize)
{   
    uint16_t u16Count;

    set_CHPCON_IAPEN;
    set_IAPUEN_APUEN;    
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_PROGRAM_APROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD=IAPDataBuf[u16Count];
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_IAPUEN_APUEN;
    clr_CHPCON_IAPEN;
}


/**
 * @brief       APROM check loop
 * @param       u16IAPStartAddress #include "ms51_8k.h" APROM area start address
 * @param       u16IAPDataSize #include "ms51_8k.h" APROM need be erase bytes size
 * @return      none
 * @details     Check with XRAM IAPDataBuf with APROM
 * @example      APROM_Program_Verify(0x0000,1024);
 */
void Program_Verify_APROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize)
{   
    uint16_t u16Count;

    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_APROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        if (IAPFD != IAPDataBuf[u16Count])
            while(1);
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_CHPCON_IAPEN;
}


/**
 * @brief       Modify CONFIG  
 * @param       u8CF0,u8CF1,u8CF2,u8CF3,u8CF4,
 * @return      none
 * @details     1. Check the CONFIG setting and now CONFIG value, if this value is matched do not change, close Modify.
                2. if value not match save old config define in XRAM, erase config and program as param define, if fail load saved config and program to recover.    
                3. All interrupt is disabled in modify CONFIG process.
 * @example     Modify_CONFIG(0xEF,0xFB,0xEF,0xFF,0xFF);
 */
void Modify_CONFIG(uint8_t u8CF0,uint8_t u8CF1,uint8_t u8CF2,uint8_t u8CF3,uint8_t u8CF4)
{   
    uint8_t u8Count;

    if(PCON&SET_BIT4)        /* Check with power on flag. Only the first power on check with CONFIG */
    {
        BIT_TMP = EA;
        EA = 0;

        set_CHPCON_IAPEN;                    // Enable IAP function
        IAPCN = BYTE_READ_CONFIG;
        IAPAH = 0x00;
        /* Check CONFIG setting data */
        IAPAL = 0;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF0)
          goto COPRST;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF1)
          goto COPRST;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF2)
          goto COPRST;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF3)
          goto COPRST;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF4)
          goto COPRST;
        goto CFCLOSE;
        /* Loop save original CONFIG data in XRAM  */

COPRST:
        ConfigModifyFlag = 1;                // CONFIG modify flag set.
        for(u8Count=0;u8Count<5;u8Count++)
        {
            IAPAL = u8Count;
            set_IAPTRG_IAPGO;
            IAPCFBuf[u8Count] = IAPFD;
        }
        /* Erase CONFIG setting    */
        set_IAPUEN_CFUEN;                    // CONFIG modify Enable
        IAPFD = 0xFF;                        // IMPORTANT !! To erase function must setting IAPFD = 0xFF
        IAPCN = PAGE_ERASE_CONFIG;
        IAPAL = 0x00;
        set_IAPTRG_IAPGO_WDCLR;
        /* Modify CONFIG setting as customer define */
        IAPCN = BYTE_PROGRAM_CONFIG;
        IAPFD = u8CF0;
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        IAPFD = u8CF1;
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        IAPFD = u8CF2;
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        IAPFD = u8CF3;
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        IAPFD = u8CF4;
        set_IAPTRG_IAPGO_WDCLR;
        clr_IAPUEN_CFUEN;
        /* Check programed data, if not match, program the storaged before data.  */
        IAPCN = BYTE_READ_CONFIG;
        IAPAL = 0x00;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF0)
          goto MDCFEND;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF1)
          goto MDCFEND;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF2)
          goto MDCFEND;
        IAPAL++;
        set_IAPTRG_IAPGO;
        if (IAPFD != u8CF3)
          goto MDCFEND;
        IAPAL++;
        set_IAPTRG_IAPGO; 
        if (IAPFD != u8CF4)
          goto MDCFEND;
        goto CFCLOSE;
MDCFEND:
        for(u8Count=0;u8Count<5;u8Count++)    // Loop save CONFIG data in XRAM
        {
            IAPAL = u8Count;
            IAPFD = IAPCFBuf[u8Count];
            set_IAPTRG_IAPGO_WDCLR;
        }
CFCLOSE:
        clr_IAPUEN_CFUEN;                    // Disable APROM modify
        clr_CHPCON_IAPEN;                    // Disable IAP

        EA = BIT_TMP;
        PCON&=CLR_BIT4;                      // Clear power on flag to avoid software reset modify CONFIG again. */

    }
}

/**
 * @brief       Read CONFIG
 * @param       None,
 * @return      none
 * @details     1. Check the CONFIG setting and now CONFIG value, if this value is matched do not change, close Modify.
                2. if value not match save old config define in XRAM, erase config and program as param define, if fail load saved config and program to recover.
                3. All interrupt is disabled in modify CONFIG process.
 * @example     Read_CONFIG();
 */
void Read_CONFIG(void)
{
    uint8_t u8Count;

        set_CHPCON_IAPEN;                    // Enable IAP function
        IAPCN = BYTE_READ_CONFIG;
        IAPAH = 0x00;
        /* Loop save original CONFIG data in XRAM  */
        for(u8Count=0;u8Count<5;u8Count++)
        {
            IAPAL = u8Count;
            set_IAPTRG_IAPGO_WDCLR;
            IAPCFBuf[u8Count] = IAPFD;
        }
        clr_CHPCON_IAPEN;                    // Disable IAP
}


/**
 * @brief       Read UID loop
 * @param       none
 * @return      none
 * @details     IAP command read UID area storage data in XRAM LIB_UIDBuffer[0:8]
 * @example      UID_Read();
*/
void Read_UID(void)
{   
    uint8_t u8Count;
    printf ("\n\r IAPFD loop ");
    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    for(u8Count=0;u8Count<12;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        UIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Read UCID loop
 * @param       none
 * @return      none
 * @details     IAP command read UCID area storage data in XRAM UCIDBuffer[0:8]
 * @example      UCID_Read();
 */
void Read_UCID(void)
{   
    uint8_t u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x20;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    for(u8Count=0;u8Count<12;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        UCIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}


/**
 * @brief       Read DID loop
 * @param       none
 * @return      none
 * @details     IAP command read DID area storage data in XRAM LIB_UIDBuffer[0:1]
 * @example     DID_Read();
*/
void Read_DID(void)
{   
    uint8_t u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = 0x00;
    IAPCN = READ_DID;
    for(u8Count=0;u8Count<2;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        DIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Read PID loop
 * @param       none
 * @return      none
* @details      IAP command read PID area storage data in XRAM LIB_PIDBuffer[0:1]
 * @example     PID_Read();
*/
void Read_PID(void)
{   
    uint8_t u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x02;
    IAPAH = 0x00;
    IAPCN = READ_DID;
    for(u8Count=0;u8Count<2;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        PIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}
