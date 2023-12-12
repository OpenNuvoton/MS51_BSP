/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

extern uint8_t  Write_DATAFLASH_BYTE(uint16_t u16EPAddr, uint8_t u8EPData);
extern uint8_t  Write_DATAFLASH_ARRAY(uint16_t u16_addr, uint8_t *pDat, uint16_t num);
void  Read_DATAFLASH_ARRAY(uint16_t u16_addr, uint8_t *pDat, uint16_t num);

