/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define PWM1     1
#define PWM2     2
#define PWM3     3

#define CH0_P23   0
#define CH0_P12   1
#define CH1_P22   2
#define CH1_P14   3
#define CH1_P11   4
                   
#define CH0_P21   0
#define CH0_P10   1
#define CH0_P05   2
#define CH1_P30   3
#define CH1_P31   4
#define CH1_P00   5
#define CH1_P04   6
                   
#define CH0_P32   0
#define CH0_P01   1
#define CH0_P17   2
#define CH1_P34   3
#define CH1_P15   4
#define CH1_P03   5



void PWM123_ClockSource(uint8_t u8PWMNum, uint8_t u8PWMCLKDIV);
void PWM123_ConfigOutputChannel(uint8_t u8PWMNum,
                                uint8_t u8PWMoutputSel,
                                uint16_t u16PWMFrequency,
                                uint16_t u16PWMDutyCycle);

void PWM_ALL_RUN(void);
void PWM1_RUN(void);
void PWM2_RUN(void);
void PWM3_RUN(void);
void PWM1_Reload(void);
void PWM2_Reload(void);
void PWM3_Reload(void);
