/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"
#include "isp_uart0.h"

#if defined __C51__
xdata uint16_t start_address,u16_addr;
#elif defined __ICC8051__
__xdata uint16_t start_address,u16_addr;
#elif defined __SDCC__
__xdata uint16_t start_address,u16_addr;
#endif

uint8_t  vo8temp;
uint16_t vo16temp;
uint32_t vo32temp;

/****************************************
  * @brief     UART interrupt subroutine.
  * @param[in] None.
  * @return    None.
****************************************/
#if defined __C51__
void Serial_ISR(void) interrupt 4
#elif defined __ICC8051__
#pragma vector=0x23
__interrupt void UART0_ISR(void)
#elif defined __SDCC__
void Serial_ISR(void) __interrupt (4)
#endif
{
    uint8_t  votemp;
    
    if (RI == 1)
    {
        votemp = SBUF;
        uart_rcvbuf[bufhead++] =  votemp;
        clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }
    if (TI == 1)
    {
        clr_SCON_TI;                                         // Clear TI (Transmit Interrupt).
    }
    if (bufhead == 1)
    {
        g_timer1Over = 0;
        g_timer1Counter = 90; //for check uart timeout using
    }
    if (bufhead == 64)
    {
        bUartDataReady = TRUE;
        g_timer1Counter = 0;
        g_timer1Over = 0;
        bufhead = 0;
    }
}

/****************************************
  * @brief     Timer0 interrupt subroutine.
  * @param[in] None.
  * @return    None.
****************************************/
#if defined __C51__
void Timer0_ISR(void) interrupt 1
#elif defined __ICC8051__
#pragma vector=0x0B
__interrupt void Timer0_ISR(void)
#elif defined __SDCC__
void Timer0_ISR(void) __interrupt (1)
#endif
{
    if (g_timer0Counter)
    {
        g_timer0Counter--;
        if (!g_timer0Counter)
        {
            g_timer0Over = 1;
        }
    }
    if (g_timer1Counter)
    {
        g_timer1Counter--;
        if (!g_timer1Counter)
        {
            g_timer1Over = 1;
        }
    }
}


/******************************
  * @brief     Main loop.
  * @param[in] None.
  * @return    None.
******************************/
void main (void)
{
  
    set_CHPCON_IAPEN;
    MODIFY_HIRC_24();
#ifdef  isp_with_wdt
    TA=0x55;TA=0xAA;WDCON=0x07;
#endif
//uart initial for ISP programmer GUI, always use 115200 baudrate
  UART0_ini_115200_24MHz();
  TM0_ini();

  g_timer0Over=0;
  g_timer0Counter=Timer0Out_Counter;
  g_programflag=0;

while(1)
{
        if(bUartDataReady == TRUE)
        {
          EA=0; //DISABLE ALL INTERRUPT
          if(g_programflag==1)
          {
            for(count=8;count<64;count++)
            {
              IAPCN = BYTE_PROGRAM_AP;          //program byte
              IAPAL = flash_address&0xff;
              IAPAH = (flash_address>>8)&0xff;
              IAPFD=uart_rcvbuf[count];
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              trig_IAPGO;
#endif
          
              IAPCN = BYTE_READ_AP;              //program byte verify
              vo8temp = uart_rcvbuf[count];
              if(IAPFD!=vo8temp)
              while(1);                          
              if (CHPCON==0x43)              //if error flag set, program error stop ISP
              while(1);

              g_totalchecksum += vo8temp;
              flash_address++;
              vo16temp = AP_size;
              if(flash_address==vo16temp)
              {
                 g_programflag=0;
                 g_timer0Over =1;
                 goto END_2;
              }
            } 
END_2:
            Package_checksum();
            uart_txbuf[8]=g_totalchecksum&0xff;
            uart_txbuf[9]=(g_totalchecksum>>8)&0xff;
            Send_64byte_To_UART0();
          }
            
          switch(uart_rcvbuf[0])
          {
            case CMD_CONNECT:
            case CMD_SYNC_PACKNO:
            {
              Package_checksum();
              Send_64byte_To_UART0();    
              g_timer0Counter=0; //clear timer 0 for no reset
              g_timer0Over=0;
              break;
            }

            case CMD_GET_FWVER:
            {
              Package_checksum();
              uart_txbuf[8]=FW_VERSION;
              Send_64byte_To_UART0();
              break;
            }
            
            case CMD_RUN_APROM:
            {
              goto _APROM;
              break;
            }

            //please for ISP programmer GUI, ID always use following rule to transmit.
            case CMD_GET_DEVICEID:
            {
              READ_ID();
              Package_checksum();
              uart_txbuf[8]=DID_lowB;  
              uart_txbuf[9]=DID_highB;  
              uart_txbuf[10]=PID_lowB;  
              uart_txbuf[11]=PID_highB;  
              Send_64byte_To_UART0();  
              break;
            }

            case CMD_ERASE_ALL:
            {
              set_IAPUEN_APUEN;
              IAPFD = 0xFF;          //Erase must set IAPFD = 0xFF
              IAPCN = PAGE_ERASE_AP;
              for(flash_address=0x0000;flash_address<APROM_SIZE/PAGE_SIZE;flash_address++)
              {        
                IAPAL = LOBYTE(flash_address*PAGE_SIZE);
                IAPAH = HIBYTE(flash_address*PAGE_SIZE);
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              trig_IAPGO;
#endif
              }
              Package_checksum();
              Send_64byte_To_UART0();  
              break;
            }

            case CMD_READ_CONFIG:
            {
              READ_CONFIG();
              Package_checksum();
              uart_txbuf[8]=CONF0;
              uart_txbuf[9]=CONF1;
              uart_txbuf[10]=CONF2;
              uart_txbuf[11]=0xff;
              uart_txbuf[12]=CONF4;
              uart_txbuf[13]=0xff;
              uart_txbuf[14]=0xff;
              uart_txbuf[15]=0xff;
              Send_64byte_To_UART0();
            break;
            }
            
            case CMD_UPDATE_CONFIG:
            {
              recv_CONF0 = uart_rcvbuf[8];
              recv_CONF1 = uart_rcvbuf[9];
              recv_CONF2 = uart_rcvbuf[10];
              recv_CONF4 = uart_rcvbuf[12];

              set_IAPUEN_CFUEN;                  /*Erase CONFIG */
              IAPCN = PAGE_ERASE_CONFIG;
              IAPAL = 0x00;
              IAPAH = 0x00;
              IAPFD = 0xFF;
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              trig_IAPGO;
#endif
              IAPCN = BYTE_PROGRAM_CONFIG;        /*Program CONFIG*/ 
              IAPFD = recv_CONF0;
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              trig_IAPGO;
#endif
              IAPFD = recv_CONF1;
              IAPAL = 0x01;
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              trig_IAPGO;
#endif
              IAPAL = 0x02;
              IAPFD = recv_CONF2;
  #ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              trig_IAPGO;
#endif
              IAPAL = 0x04;
              IAPFD = recv_CONF4;
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              trig_IAPGO;
#endif
              clr_IAPUEN_CFUEN;

              READ_CONFIG();                        /*Read new CONFIG*/  
              Package_checksum();
              uart_txbuf[8]=CONF0;
              uart_txbuf[9]=CONF1;
              uart_txbuf[10]=CONF2;
              uart_txbuf[11]=0xff;
              uart_txbuf[12]=CONF4;
              uart_txbuf[13]=0xff;
              uart_txbuf[14]=0xff;
              uart_txbuf[15]=0xff;
              Send_64byte_To_UART0();
              break;
            }

            case CMD_UPDATE_APROM:
            {
              set_IAPUEN_APUEN;
              IAPFD = 0xFF;          //Erase must set IAPFD = 0xFF
              IAPCN = PAGE_ERASE_AP;
              
              start_address = 0;
              start_address = uart_rcvbuf[8];
              start_address |= ((uart_rcvbuf[9]<<8)&0xFF00);
              AP_size = 0;
              AP_size = uart_rcvbuf[12];
              vo8temp = uart_rcvbuf[13];
              AP_size |= ((vo8temp<<8)&0xFF00);

              u16_addr = start_address + AP_size;
              flash_address = (start_address&0xFF00);
 
              while(flash_address< u16_addr)
              {
                IAPAL = LOBYTE(flash_address);
                IAPAH = HIBYTE(flash_address);
#ifdef isp_with_wdt
                set_IAPTRG_IAPGO_WDCLR;
#else
                trig_IAPGO;
#endif
                flash_address += PAGE_SIZE;
              }
              
              g_totalchecksum = 0;
              flash_address = start_address;
              g_programflag = 1;

              for(count=16;count<64;count++)
              {
                IAPCN = BYTE_PROGRAM_AP;
                IAPAL = flash_address&0xff;
                IAPAH = (flash_address>>8)&0xff;
                IAPFD = uart_rcvbuf[count];
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              trig_IAPGO;
#endif
                IAPCN = BYTE_READ_AP;                //program byte verify
                trig_IAPGO;
                vo8temp = uart_rcvbuf[count];
                if(IAPFD!=vo8temp)
                while(1);
                if (CHPCON==0x43)                //if error flag set, program error stop ISP
                while(1);

                g_totalchecksum += vo8temp;
                flash_address++;
                vo16temp = AP_size;
                if(flash_address==vo16temp)
                {
                  g_programflag=0;
                   goto END_1;
                }
              }
END_1:                
              Package_checksum();
              uart_txbuf[8]=g_totalchecksum&0xff;
              uart_txbuf[9]=(g_totalchecksum>>8)&0xff;
              Send_64byte_To_UART0();  
              break;
            }
          }  
          bUartDataReady = FALSE;
          bufhead = 0;

          EA=1;
      }
      /*For connect timer out   */
      if(g_timer0Over==1)
      {
        CALL_NOP;
        goto _APROM;
      }
      
      /*for uart time out or buffer error  */
       if(g_timer1Over==1)
      {
       if((bufhead<64)&&(bufhead>0)||(bufhead>64))
         {
             bufhead=0;
         }
      }  
}   

_APROM:
    MODIFY_HIRC_16();
    clr_CHPCON_IAPEN;
    TA = 0xAA; TA = 0x55; CHPCON = 0x80;                   //software reset enable boot from APROM
    /* Trap the CPU */
    while(1);  
}


