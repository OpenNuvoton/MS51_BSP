/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#if defined __C51__
extern uint8_t xdata IAPSPDataBuf[127];
#elif defined __ICC8051__
extern uint8_t __xdata IAPSPDataBuf[127];
#elif defined __SDCC__
extern uint8_t __xdata IAPSPDataBuf[127];
#endif

void Erase_SPROM(void);
void Erase_Verify_SPROM(uint16_t u16IAPDataSize);
void Program_SPROM(uint16_t u16IAPDataSize);
void Read_Verify_SPROM( uint16_t u16IAPDataSize);

