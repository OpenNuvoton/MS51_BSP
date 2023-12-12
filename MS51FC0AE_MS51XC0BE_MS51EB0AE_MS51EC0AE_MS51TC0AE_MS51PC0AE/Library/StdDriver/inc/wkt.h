/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
void WKT_AutoReload_Interrupt_Initial_S(uint16_t u16WKTRLData);
void WKT_AutoReload_Interrupt_Initial_MS(uint16_t u16WKTRLData);
void WKT_Open(uint16_t u16WKTDIV, uint16_t u16WKTRLData);
void WKT_Interrupt(uint8_t u8WKTINT);
void WKT_Close(void);
