/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#define TIMER0        0
#define TIMER1        1
#define TIMER2        2
#define TIMER3        3


#define UNIT_1US      0
#define UNIT_10US     1
#define UNIT_100US   2
#define UNIT_1MS     3
#define UNIT_10MS     4
#define UNIT_100MS    5
#define UNIT_1S       6

void Timer0_Delay(uint32_t u32SYSCLK, uint16_t u16CNT, uint16_t u16DLYUnit);
void Timer1_Delay(uint32_t u32SYSCLK, uint16_t u16CNT, uint16_t u16DLYUnit);
void Timer2_Delay(uint32_t u32SYSCLK, uint16_t u16TMDIV, uint16_t u16CNT, uint32_t u32DLYUnit);
void Timer3_Delay(uint32_t u32SYSCLK, uint8_t u8TMDIV, uint16_t u16CNT, uint32_t u32DLYUnit);

