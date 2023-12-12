/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"
#include "isp_uart1.h"


/******************************
  * @brief     UART1 interrupt.
  * @param[in] None.
  * @return    None.
******************************/
#if defined __C51__
void UART1_ISR(void) interrupt 15
#elif defined __ICC8051__
#pragma vector=0x7B
__interrupt void UART1_ISR(void)
#elif defined __SDCC__
void UART1_ISR(void) __interrupt (15)
#endif
{
    uint8_t   vo8temp;

    SFRS=0;
    if (RI_1 == 1)
    {
      vo8temp =  SBUF_1; 
      uart_rcvbuf[bufhead++] = vo8temp;
      clr_SCON_1_RI_1;                                         // Clear RI (Receive Interrupt).
    }
    if (TI_1 == 1)
    {
        clr_SCON_1_TI_1;                                         // Clear TI (Transmit Interrupt).
    }
    if(bufhead ==1)
    {
      g_timer1Over=0;
      g_timer1Counter=90; //for check uart timeout using
    }
  if(bufhead == 64)
    {
      bUartDataReady = TRUE;
      g_timer1Counter=0;
      g_timer1Over=0;
      bufhead = 0;
    }
}

/******************************
  * @brief     Timer0 interrupt.
  * @param[in] None.
  * @return    None.
******************************/
#if defined __C51__
void Timer0_ISR (void) interrupt 1
#elif defined __ICC8051__
#pragma vector=0x0B
__interrupt void Timer0_ISR(void)
#elif defined __SDCC__
void Timer0_ISR (void) __interrupt (1)
#endif
{

if(g_timer0Counter)
  {
  g_timer0Counter--;
    if(!g_timer0Counter)
    {
    g_timer0Over=1;
    }
  }

  if(g_timer1Counter)
  {
  g_timer1Counter--;
    if(!g_timer1Counter)
    {
    g_timer1Over=1;
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
  uint8_t   vo8temp;
  uint16_t  vo16temp;
    set_CHPCON_IAPEN;
    MODIFY_HIRC_24();
    UART1_ini_115200_24MHz();
   //uart initial for ISP programmer GUI, always use 115200 baudrate
    TM0_ini();

    g_timer0Over=0;
    g_timer0Counter=5000;
    g_progarmflag=0;

while(1)
{
        if(bUartDataReady == TRUE)
        {
          EA=0; //DISABLE ALL INTERRUPT
          if(g_progarmflag==1)
          {
            for(count=8;count<64;count++)
            {
              IAPCN = BYTE_PROGRAM_AP;          //program byte
              IAPAL = flash_address&0xff;
              IAPAH = (flash_address>>8)&0xff;
              IAPFD=uart_rcvbuf[count];
              trig_IAPGO;
          
              IAPCN = BYTE_READ_AP;              //program byte verify
              trig_IAPGO;
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
                g_progarmflag=0;
                g_timer0Over =1;
                goto END_2;
              }
            } 
END_2:                
            Package_checksum();
            uart_txbuf[8]=g_totalchecksum&0xff;
            uart_txbuf[9]=(g_totalchecksum>>8)&0xff;
            Send_64byte_To_UART1();
            
          }
            
          switch(uart_rcvbuf[0])
          {                
            case CMD_CONNECT:
            case CMD_SYNC_PACKNO:
            {
              Package_checksum();
              Send_64byte_To_UART1();    
              g_timer0Counter=0; //clear timer 0 for no reset
              g_timer0Over=0;
            break;
            }

            case CMD_GET_FWVER:
            {
              Package_checksum();
              uart_txbuf[8]=FW_VERSION;
              Send_64byte_To_UART1();  
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
              Send_64byte_To_UART1();  
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
                trig_IAPGO;
              }            
              
              Package_checksum();
              Send_64byte_To_UART1();  
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
              Send_64byte_To_UART1();  
            break;
            }
            
            case CMD_UPDATE_CONFIG:
            {
              recv_CONF0 = uart_rcvbuf[8];
              recv_CONF1 = uart_rcvbuf[9];
              recv_CONF2 = uart_rcvbuf[10];
              recv_CONF4 = uart_rcvbuf[12];
/*Erase CONFIG */              
//              set_CHPCON_IAPEN;
              set_IAPUEN_CFUEN;
              IAPCN = PAGE_ERASE_CONFIG;
              IAPAL = 0x00;
              IAPAH = 0x00;
              IAPFD = 0xFF;
              trig_IAPGO;
/*Program CONFIG*/  
              IAPCN = BYTE_PROGRAM_CONFIG;
              IAPAL = 0x00;
              IAPAH = 0x00;
              IAPFD = recv_CONF0;
              trig_IAPGO;
              IAPFD = recv_CONF1;
              IAPAL = 0x01;
              trig_IAPGO;
              IAPAL = 0x02;
              IAPFD = recv_CONF2;
              trig_IAPGO;
              IAPAL = 0x04;
              IAPFD = recv_CONF4;
              trig_IAPGO;
              clr_IAPUEN_CFUEN;
/*Read new CONFIG*/  
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
              Send_64byte_To_UART1();  
              break;
            }
            
            case CMD_UPDATE_APROM:            
            {
//              set_CHPCON_IAPEN;
              set_IAPUEN_APUEN;
              IAPFD = 0xFF;          //Erase must set IAPFD = 0xFF
              IAPCN = PAGE_ERASE_AP;
              
              for(flash_address=0x0000;flash_address<APROM_SIZE/PAGE_SIZE;flash_address++)
              {        
                IAPAL = LOBYTE(flash_address*PAGE_SIZE);
                IAPAH = HIBYTE(flash_address*PAGE_SIZE);
                trig_IAPGO;
              }            
              
              g_totalchecksum=0;
              flash_address=0;
              AP_size=0;
              AP_size=uart_rcvbuf[12];
              vo8temp = uart_rcvbuf[13]; 
              AP_size|=(vo8temp<<8);  
              g_progarmflag=1;

              for(count=16;count<64;count++)
              {
                IAPCN = BYTE_PROGRAM_AP;
                IAPAL = flash_address&0xff;
                IAPAH = (flash_address>>8)&0xff;
                IAPFD=uart_rcvbuf[count];
                clr_CHPCON_IAPFF;
                trig_IAPGO;                              
      
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
                  g_progarmflag=0;
                   goto END_1;          
                }
              }
END_1:                
              Package_checksum();
              uart_txbuf[8]=g_totalchecksum&0xff;
              uart_txbuf[9]=(g_totalchecksum>>8)&0xff;
              Send_64byte_To_UART1();  
              break;
            }
          }  
          bUartDataReady = FALSE;
          bufhead = 0;            
          EA=1;
      }
      //For connect timer out  
      if(g_timer0Over==1)
      {       
       goto _APROM;
      }
      
      //for uart time out or buffer error
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
    TA = 0xAA;
    TA = 0x55;
    CHPCON = 0x00;                  //set boot from AP
    TA = 0xAA;
    TA = 0x55;
    CHPCON = 0x80;                   //software reset enable

    /* Trap the CPU */
    while(1);  
}




