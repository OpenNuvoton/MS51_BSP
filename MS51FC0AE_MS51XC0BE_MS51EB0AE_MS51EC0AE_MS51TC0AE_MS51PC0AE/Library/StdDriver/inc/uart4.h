/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define UART4_TXD   0
#define UART4_RXD   1

#define SC2PEVEN     0
#define SC2PODD      1

extern BIT uart4rvflag;
extern uint8_t uart4rvbuffer;

void UART4_Open(uint32_t u32SysClock, uint32_t u32Baudrate);
void UART4_Receive_10byte(void);
extern uint8_t UART4_Receive_Data(void);
void UART4_Send_Data(uint8_t c);
void UART4_Interrupt(uint8_t u8UART4INTSel,uint8_t u8UART4INTStatus);
void UART4_Parity(uint8_t u8PStatus, uint8_t u8PEvenOdd);