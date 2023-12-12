/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define UART3_TXD   0
#define UART3_RXD   1


extern BIT uart3rvflag;
extern uint8_t uart3rvbuffer;

void UART3_Open(uint32_t u32SysClock, uint32_t u32Baudrate);
void UART3_Receive_10byte(void);
extern uint8_t UART3_Receive_Data(void);
void UART3_Send_Data(uint8_t c);
void UART3_Interrupt(uint8_t u8UART3INTSel,uint8_t u8UART3INTStatus);
