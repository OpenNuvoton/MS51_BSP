/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"
#include "isp_i2c.h"

//#define  isp_with_wdt

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

#if defined __C51__
void I2C_ISR(void) interrupt 6
#elif defined __ICC8051__
#pragma vector=0x33
__interrupt void I2C_ISR(void)
#elif defined __SDCC__
void I2C_ISR(void) __interrupt (6)
#endif
{
    static uint8_t _bISPDataReady;
    uint8_t u8data,temp8;

    if (I2STAT == 0x60) {                    /* Own SLA+W has been receive; ACK has been return */
        bI2CDataReady = 0;
        bISPDataReady = 0;
        g_u8SlvDataLen = 0;
        //I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
        AA=1;
    } else if (I2STAT == 0x80)                 /* Previously address with own SLA address
                                                   Data has been received; ACK has been returned*/
    {
        temp8 = g_u8SlvDataLen;
        rx_buf[temp8] = I2DAT;
        g_u8SlvDataLen++;
        g_u8SlvDataLen &= 0x3F;
        bI2CDataReady = (g_u8SlvDataLen == 0);

        if (g_u8SlvDataLen == 0x3F) {
            //I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI);
        } else {
            //I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
          AA=1;
        }
    } else if (I2STAT == 0xA8) {             /* Own SLA+R has been receive; ACK has been return */
        g_u8SlvDataLen = 0;
        _bISPDataReady = bISPDataReady;

        if (_bISPDataReady == 0) {
            u8data = 0xCC;
        } else {
            u8data = tx_buf[g_u8SlvDataLen];
        }


        I2DAT=u8data;
        g_u8SlvDataLen++;
       // I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
        AA=1;
    } else if (I2STAT == 0xB8) {
        if (_bISPDataReady == 0) {
            u8data = 0xDD;
        } else {
            u8data = tx_buf[g_u8SlvDataLen];
        }


        I2DAT=u8data;
        g_u8SlvDataLen++;
        g_u8SlvDataLen &= 0x3F;

        if (g_u8SlvDataLen == 0x00) {
           // I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI);
        } else {
          //  I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
          AA=1;
        }
    } else if (I2STAT == 0xC8) {
       // I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
      AA=1;
    } else if (I2STAT == 0xC0)                 /* Data byte or last data in I2CDAT has been transmitted
                                                   Not ACK has been received */
    {
       // I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
      AA=1;
    } else if (I2STAT == 0x88)                 /* Previously addressed with own SLA address; NOT ACK has
                                                   been returned */
    {
        temp8 = g_u8SlvDataLen;
        rx_buf[temp8] = I2DAT;
        g_u8SlvDataLen++;
        bI2CDataReady = (g_u8SlvDataLen == 64);
        g_u8SlvDataLen = 0;
      //  I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
      AA=1;
    } else if (I2STAT == 0xA0)                 /* A STOP or repeated START has been received while still
                                                   addressed as Slave/Receiver*/
    {
        g_u8SlvDataLen = 0;
        //I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
      AA=1;
    } else {
        /* TO DO */
        // printf("Status 0x%x is NOT processed\n", u32Status);
    }
    SI = 0;

}


/**
 * @brief       Main loop
 * @param       None
 * @return      None
 * @details     ISP through I2C .
 */
void main (void)
{
    uint8_t  temp8;
    uint16_t  temp16;
    
    set_CHPCON_IAPEN;

    Init_I2C(); 
    bI2CDataReady=0;
    
    TM0_ini();  
    g_timer0Over=0;
    g_timer0Counter=5000;
    g_progarmflag=0;
    count = 0;

while(1)
{
        //if(bUartDataReady == TRUE)
        if(bI2CDataReady == TRUE)
        {
          EA=0; //DISABLE ALL INTERRUPT
          if(g_progarmflag==1)
          {
            for(count=8;count<64;count++)
            {
              IAPCN = BYTE_PROGRAM_AP;          //program byte
              IAPAL = flash_address&0xff;
              IAPAH = (flash_address>>8)&0xff;
              IAPFD=rx_buf[count];
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              trig_IAPGO;
#endif
          
              IAPCN = BYTE_READ_AP;              //program byte verify
              set_IAPTRG_IAPGO;
              temp8 = rx_buf[count];
              if(IAPFD != temp8)
              while(1);                          
              if (CHPCON==0x43)              //if error flag set, program error stop ISP
              while(1);
              
              g_totalchecksum = g_totalchecksum + temp8;
              flash_address++;

              temp16 = AP_size;
              if(flash_address == temp16)
              {
                g_progarmflag=0;
				g_timer0Over =1;
                 goto END_2;

              }
            } 
END_2:                
            Package_checksum();
            tx_buf[8]=g_totalchecksum&0xff;
            tx_buf[9]=(g_totalchecksum>>8)&0xff;

            bISPDataReady = 1;
          }
            
          switch(rx_buf[0])
          {                
            case CMD_CONNECT:
            case CMD_SYNC_PACKNO:
            {
              Package_checksum();

              bISPDataReady = 1;              
              g_timer0Counter=0; //clear timer 0 for no reset
              g_timer0Over=0;
            break;
            }
                        
            case CMD_GET_FWVER:            
            {
              Package_checksum();
              tx_buf[8]=FW_VERSION;  

              bISPDataReady = 1;
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
              tx_buf[8]=DID_lowB;  
              tx_buf[9]=DID_highB;  
              tx_buf[10]=PID_lowB;  
              tx_buf[11]=PID_highB;  

              bISPDataReady = 1; 
            break;
            }
            case CMD_ERASE_ALL:
            {
              set_CHPCON_IAPEN;
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
              bISPDataReady = 1; 
              break;
            }
            case CMD_READ_CONFIG:
            {
              READ_CONFIG();
              Package_checksum();
              tx_buf[8]=CONF0;  
              tx_buf[9]=CONF1;  
              tx_buf[10]=CONF2;  
              tx_buf[11]=0xff;  
              tx_buf[12]=CONF4;  
              tx_buf[13]=0xff;  
              tx_buf[14]=0xff;
              tx_buf[15]=0xff;
              bISPDataReady = 1;
            break;
            }
            
            case CMD_UPDATE_CONFIG:
            {
              recv_CONF0 = rx_buf[8];
              recv_CONF1 = rx_buf[9];
              recv_CONF2 = rx_buf[10];
              recv_CONF4 = rx_buf[12];
/*Erase CONFIG */              
              set_CHPCON_IAPEN;
              set_IAPUEN_CFUEN;
              IAPCN = PAGE_ERASE_CONFIG;
              IAPAL = 0x00;
              IAPAH = 0x00;
              IAPFD = 0xFF;
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              trig_IAPGO;
#endif

/*Program CONFIG*/  
              IAPCN = BYTE_PROGRAM_CONFIG;
              IAPFD = recv_CONF0;
              set_IAPTRG_IAPGO;
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
/*Read new CONFIG*/  
              READ_CONFIG();
              
              Package_checksum();
              tx_buf[8]=CONF0;  
              tx_buf[9]=CONF1;  
              tx_buf[10]=CONF2;  
              tx_buf[11]=0xff;  
              tx_buf[12]=CONF4;  
              tx_buf[13]=0xff;  
              tx_buf[14]=0xff;
              tx_buf[15]=0xff;
              bISPDataReady = 1;
              break;
            }
            
            case CMD_UPDATE_APROM:
            {
              set_CHPCON_IAPEN;
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

              g_totalchecksum=0;
              flash_address=0;
              AP_size=0;
              AP_size=rx_buf[12];
              temp16 = (rx_buf[13]<<8); 
              AP_size |= temp16;
              g_progarmflag=1;

              for(count=16;count<64;count++)
              {
                IAPCN = BYTE_PROGRAM_AP;
                IAPAL = flash_address&0xff;
                IAPAH = (flash_address>>8)&0xff;
                IAPFD=rx_buf[count];
                clr_CHPCON_IAPFF;
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              trig_IAPGO;
#endif
      
                IAPCN = BYTE_READ_AP;                //program byte verify
                set_IAPTRG_IAPGO;
                temp8 = rx_buf[count];
                if(IAPFD != temp8)
                while(1); 
                if (CHPCON==0x43)                //if error flag set, program error stop ISP
                while(1);
                
                g_totalchecksum = g_totalchecksum + temp8;
                flash_address++;

                temp16 = AP_size;                
                if(flash_address == temp16)
                {
                  g_progarmflag=0;
                   goto END_1;
                }
              }
END_1:                
              Package_checksum();
              tx_buf[8]=g_totalchecksum&0xff;
              tx_buf[9]=(g_totalchecksum>>8)&0xff;

              bISPDataReady = 1;
              break;
            }
          }  
          bI2CDataReady = FALSE;
          EA=1;
      }
      //For connect timer out  
      if(g_timer0Over==1)
      {       
       goto _APROM;
      }
}   


_APROM:
    EA = 0;
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


