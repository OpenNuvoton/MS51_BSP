/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

BIT PRINTFG, uart0_receive_flag, uart1_receive_flag;
uint8_t uart0_receive_data, uart1_receive_data;

#if 0
/* UART0 interrupt vector demo */
#if defined __C51__
void Serial_ISR(void)  interrupt 4
#elif defined __ICC8051__
#pragma vector=0x23
__interrupt void SerialPort0_ISR(void)
#elif defined __SDCC__
void Serial_ISR(void) __interrupt (4)
#endif
{
    PUSH_SFRS;
    if (RI)
    {
        uart0_receive_flag = 1;
        uart0_receive_data = SBUF;
        clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }

    if (TI)
    {
        if (!PRINTFG)
        {
            TI = 0;
        }
    }
    POP_SFRS;
}  


/* UART1 interrupt vector demo */
#if defined __C51__
void SerialPort1_ISR(void) interrupt 15
#elif defined __ICC8051__
#pragma vector=0x7B
__interrupt void SerialPort1_ISR(void)
#elif defined __SDCC__
void SerialPort1_ISR(void) __interrupt (15)
#endif
{
    PUSH_SFRS;

    if (RI_1 == 1)
    {
        clr_SCON_1_RI_1;                             /* clear reception flag for next reception */
        uart1_receive_data = SBUF_1;
        uart1_receive_flag = 1;
    }

    if (TI_1 == 1)
    {
        if (!PRINTFG)
        {
            clr_SCON_1_TI_1;                             /* if emission occur */
        }
    }
    POP_SFRS;
}  
#endif 

void UART_Open(uint32_t u32SysClock, uint8_t u8UARTPort, uint32_t u32Baudrate)
{
     SFRS = 0;
     switch (u8UARTPort)
    {
        case UART0_Timer1:
            SCON = 0x50;            //UART0 Mode1,REN=1,TI=1
            TMOD |= 0x20;           //Timer1 Mode1
            set_PCON_SMOD;          //UART0 Double Rate Enable
            set_CKCON_T1M;
            clr_T3CON_BRCK;          //Serial port 0 baud rate clock source = Timer1
            TH1 = 256 - (u32SysClock / 16 / u32Baudrate);
            set_TCON_TR1;
            set_IE_ES;
            break;

        case UART0_Timer3:
            SCON = 0x50;          //UART0 Mode1,REN=1,TI=1
            set_PCON_SMOD;        //UART0 Double Rate Enable
            T3CON &= 0xF8;        //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
            set_T3CON_BRCK;        //UART0 baud rate clock source = Timer3
            RH3    = HIBYTE(65536 - (u32SysClock / 16 / u32Baudrate));
            RL3    = LOBYTE(65536 - (u32SysClock / 16 / u32Baudrate));
            set_T3CON_TR3;         //Trigger Timer3
            set_IE_ES;
            break;

        case UART1_Timer3:
            SCON_1 = 0x50;          //UART1 Mode1,REN_1=1,TI_1=1
            T3CON = 0x80;           //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1), UART1 in MODE 1
            RH3    = HIBYTE(65536 - (u32SysClock/16/u32Baudrate));  
            RL3    = LOBYTE(65536 - (u32SysClock/16/u32Baudrate));     
            set_T3CON_TR3;             //Trigger Timer3
            set_EIE1_ES_1;
            break;
    }
 }

uint8_t Receive_Data(uint8_t UARTPort)
{
    uint8_t c;

    c = 0;
    SFRS = 0;
    switch (UARTPort)
    {
        case UART0:
            while (!RI);
            c = SBUF;
            RI = 0;
            break;

        case UART1:
            while (!RI_1);
            c = SBUF_1;
            RI_1 = 0;
            break;
    }

    return (c);
}

void UART_Send_Data(uint8_t UARTPort, uint8_t c)
{
    PUSH_SFRS;
    SFRS = 0;
    switch (UARTPort)
    {
        case UART0:
          TI=0;
          SBUF = c;
          while(!TI);
        break;
        case UART1:
          TI_1=0;
          SBUF_1 = c;
          while(!TI_1);
        break;
    }
    POP_SFRS;
}


void Enable_UART0_VCOM_printf_24M_115200(void)
{
    P06_QUASI_MODE;
    UART_Open(24000000,UART0_Timer1,115200);
    ENABLE_UART0_PRINTF;
    DISABLE_UART0_INTERRUPT;
}
