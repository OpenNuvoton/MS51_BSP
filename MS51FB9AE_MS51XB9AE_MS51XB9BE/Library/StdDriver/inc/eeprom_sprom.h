/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#if defined __C51__
extern uint8_t Read_SPROM_BYTE(uint8_t code *u8_addr);
#elif defined __ICC8051__
extern uint8_t Read_SPROM_BYTE(const uint8_t __code *u8_addr);
#elif defined __SDCC__
extern uint8_t Read_SPROM_BYTE(const uint8_t __code *u8_addr);
#endif

extern uint8_t Write_SPROM_DATAFLASH_ARRAY(uint8_t u8_addr, uint8_t *pDat, uint16_t num);
void Read_SPROM_DATAFLASH_ARRAY(uint16_t u16_addr, uint8_t *pDat, uint16_t num);