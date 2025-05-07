/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define UART2_TXD   0
#define UART2_RXD   1

#define SC0PEVEN     0
#define SC0PODD      1

extern BIT uart2rvflag;
extern uint8_t uart2rvbuffer;

void UART2_Open(uint32_t u32SysClock, uint32_t u32Baudrate);
void UART2_Receive_10byte(void);
extern uint8_t UART2_Receive_Data(void);
void UART2_Send_Data(uint8_t c);
void UART2_Interrupt(uint8_t u8UART2INTSel,uint8_t u8UART2INTStatus);
void UART2_Parity(uint8_t u8PStatus, uint8_t u8PEvenOdd);