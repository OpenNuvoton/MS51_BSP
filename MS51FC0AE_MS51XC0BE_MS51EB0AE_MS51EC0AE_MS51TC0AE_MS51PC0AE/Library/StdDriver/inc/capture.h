/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define IC0    0
#define IC1    1
#define IC2    2

#define CaptureFalling    0
#define CaptureRising     1
#define CaptureEither     2

void TIMER2_Capture(uint8_t u8CAPSource, uint8_t u8CAPLevel, uint8_t u8TM2DIV);
void TIMER2_Capture_Interrupt(uint8_t u8CAPINT);