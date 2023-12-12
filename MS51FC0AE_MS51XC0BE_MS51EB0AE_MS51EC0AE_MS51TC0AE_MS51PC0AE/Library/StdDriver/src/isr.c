/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2024 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 ISR all list
//***********************************************************************************************************
#include "numicro_8051.h"


#if 0 

/*all interrupt subroutine list */

//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void INT0_ISR(void) interrupt 0          // Vector @  0x03

#elif defined __ICC8051__
#pragma vector=0x03
__interrupt void INT0_ISR(void)

#elif defined __SDCC__
void INT0_ISR(void) __interrupt (0)          // Vector @  0x03
#endif
{
    PUSH_SFRS;
    clr_TCON_IE0;
    POP_SFRS;
}

//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void Timer0_ISR(void) interrupt 1        // Vector @  0x0B

#elif defined __ICC8051__
#pragma vector=0x0B
__interrupt void Timer0_ISR(void)

#elif defined __SDCC__
void Timer0_ISR(void) __interrupt (1)         // Vector @  0x0B
#endif
{
    PUSH_SFRS;
    clr_TCON_TF0;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void INT1_ISR(void) interrupt 2          // Vector @  0x13

#elif defined __ICC8051__
#pragma vector=0x13
__interrupt void INT1_ISR(void)

#elif defined __SDCC__
void INT1_ISR(void) __interrupt (2)          // Vector @  0x13
#endif
{
    PUSH_SFRS;
    clr_TCON_IE1;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
#endifvoid Timer1_ISR(void) interrupt 3        // Vector @  0x1B
#elif defined __ICC8051__
#pragma vector=0x1B
__interrupt void Timer1_ISR(void)
#elif defined __SDCC__
void Timer1_ISR(void) __interrupt (3)        // Vector @  0x1B
#endif
{
    PUSH_SFRS;
    clr_TCON_TF1;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
#endifvoid UART0_ISR(void) interrupt 4         // Vector @  0x23

#elif defined __ICC8051__
#pragma vector=0x23
__interrupt void UART0_ISR(void)

#elif defined __SDCC__
void UART0_ISR(void) __interrupt (4)         // Vector @  0x23
#endif
{
    PUSH_SFRS;
    clr_SCON_RI;
    clr_SCON_TI;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void Timer2_ISR(void) interrupt 5        // Vector @  0x2B

#elif defined __ICC8051__
#pragma vector=0x2B
__interrupt void Timer2_ISR(void)

#elif defined __SDCC__
void Timer2_ISR(void) __interrupt (5)        // Vector @  0x2B
#endif
{
    PUSH_SFRS;
    clr_T2CON_TF2;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void I2C_ISR(void) interrupt 6           // Vector @  0x33

#elif defined __ICC8051__
#pragma vector=0x33
__interrupt void I2C_ISR(void)

#elif defined __SDCC__
void I2C_ISR(void) __interrupt (6)        // Vector @  0x33
#endif
{
    PUSH_SFRS;
    clr_I2CON_SI;

    POP_SFRS;
}//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void Pin_INT_ISR(void) interrupt 7       // Vector @  0x3B

#elif defined __ICC8051__
#pragma vector=0x3B
__interrupt void Pin_INT_ISR(void)

#elif defined __SDCC__
void Pin_INT_ISR(void) __interrupt (7)       // Vector @  0x3B
#endif
{
     PUSH_SFRS;
     PIF = 0;
     POP_SFRS;
}//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void BOD_ISR(void) interrupt 8           // Vector @  0x43

#elif defined __ICC8051__
#pragma vector=0x43
__interrupt void BOD_ISR(void)

#elif defined __SDCC__
void BOD_ISR(void) __interrupt (8)           // Vector @  0x43
#endif
{
     PUSH_SFRS;
     clr_BODCON0_BOF;
     POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void SPI_ISR(void) interrupt 9           // Vector @  0x4B

#elif defined __ICC8051__
#pragma vector=0x4B
__interrupt void SPI_ISR (void)

#elif defined __SDCC__
void SPI_ISR(void) __interrupt (9)          // Vector @  0x4B
#endif
{
    PUSH_SFRS;
    clr_SPSR_SPIF;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void WDT_ISR(void) interrupt 10          // Vector @  0x53

#elif defined __ICC8051__
#pragma vector=0x53
__interrupt void WDT_ISR (void)

#elif defined __SDCC__
void WDT_ISR(void) __interrupt (10)          // Vector @  0x53
#endif
{
    PUSH_SFRS;
    clr_WDCON_WDTF;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void ADC_ISR(void) interrupt 11          // Vector @  0x5B

#elif defined __ICC8051__
#pragma vector=0x5B
__interrupt void ADC_ISR (void)

#elif defined __SDCC__
void ADC_ISR(void) __interrupt (11)          // Vector @  0x5B
#endif
{
    PUSH_SFRS;
    clr_ADCCON0_ADCF;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void Capture_ISR(void) interrupt 12      // Vector @  0x63

#elif defined __ICC8051__
#pragma vector=0x63
__interrupt void Capture_ISR (void)

#elif defined __SDCC__
void Capture_ISR(void) __interrupt (12)      // Vector @  0x63
#endif
{
    PUSH_SFRS;
    CLEAR_CAPTURE_INTERRUPT_IC0_FLAG;
    CLEAR_CAPTURE_INTERRUPT_IC1_FLAG;
    CLEAR_CAPTURE_INTERRUPT_IC2_FLAG;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void PWM__ISR(void) interrupt 13    // Vector @  0x6B

#elif defined __ICC8051__
#pragma vector=0x6B
__interrupt void PWM_ISR (void)

#elif defined __SDCC__
void Capture_ISR(void) __interrupt (13)      // Vector @  0x6B
#endif
{
     PUSH_SFRS;
     POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void PWM_Brake_ISR(void) interrupt 14    // Vector @  0x73

#elif defined __ICC8051__
#pragma vector=0x73
__interrupt void PWM_Brake_ISR(void)

#elif defined __SDCC__
void PWM_Brake_ISR(void) __interrupt (14)    // Vector @  0x73
#endif
{
     PUSH_SFRS;
     clr_PWM0FBD_FBF;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void UART1_ISR(void) interrupt 15               // Vector @  0x7B

#elif defined __ICC8051__
#pragma vector=0x7B
__interrupt void UART1_ISR(void)

#elif defined __SDCC__
void UART1_ISR(void) __interrupt (15)          // Vector @  0x7B
#endif
{
    PUSH_SFRS;
    clr_SCON_RI_1;
    clr_SCON_TI_1;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void Timer3_ISR(void) interrupt 16          // Vector @  0x83

#elif defined __ICC8051__
#pragma vector=0x2B
__interrupt void Timer2_ISR(void)

#elif defined __SDCC__
void Timer3_ISR(void) __interrupt (16)        // Vector @  0x83
#endif
{
    PUSH_SFRS;
    CLEAR_TIMER3_INTERRUPT_FLAG;
    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void WKT_ISR(void) interrupt 17                 // Vector @  0x8B

#elif defined __ICC8051__
#pragma vector=0x8B
__interrupt void WKT_ISR(void)

#elif defined __SDCC__
void WKT_ISR(void) __interrupt (17)            // Vector @  0x8B
#endif
{
    PUSH_SFRS;
    CLEAR_WKT_INTERRUPT_FLAG;
    POP_SFRS;
}

//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void PWM1_ISR(void) interrupt 18                 // Vector @  0x93

#elif defined __ICC8051__
#pragma vector=0x93
__interrupt void PWM1_ISR(void)

#elif defined __SDCC__
void PWM1_ISR(void) __interrupt (18)            // Vector @  0x93
#endif
{
    PUSH_SFRS;
    CLEAR_PWM1_INTERRUPT_FLAG;
    POP_SFRS;
}

//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void PWM2_ISR(void) interrupt 19                 // Vector @  0x9B

#elif defined __ICC8051__
#pragma vector=0x9B
__interrupt void PWM2_ISR(void)

#elif defined __SDCC__
void PWM2_ISR(void) __interrupt (19)            // Vector @  0x9B
#endif
{
    PUSH_SFRS;
    CLEAR_PWM2_INTERRUPT_FLAG;
    POP_SFRS;
}

//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void PWM3_ISR(void) interrupt 20                 // Vector @  0xA3

#elif defined __ICC8051__
#pragma vector=0xA3
__interrupt void PWM3_ISR(void)

#elif defined __SDCC__
void PWM3_ISR(void) __interrupt (20)            // Vector @  0xA3
#endif
{
    PUSH_SFRS;
    CLEAR_PWM3_INTERRUPT_FLAG;
    POP_SFRS;
}

//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void SMC0_ISR(void) interrupt 21                 // Vector @  0xAB

#elif defined __ICC8051__
#pragma vector=0xAB
__interrupt void SMC0_ISR(void)

#elif defined __SDCC__
void SMC0_ISR(void) __interrupt (21)            // Vector @  0xAB
#endif
{
    PUSH_SFRS;

    POP_SFRS;
}

//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void SMC1_ISR(void) interrupt 22                 // Vector @  0xB3

#elif defined __ICC8051__
#pragma vector=0xB3
__interrupt void SMC1_ISR(void)

#elif defined __SDCC__
void SMC1_ISR(void) __interrupt (22)            // Vector @  0xB3
#endif
{
    PUSH_SFRS;

    POP_SFRS;
}

//-----------------------------------------------------------------------------------------------------------
#if defined __C51__
void SMC2_ISR(void) interrupt 23                 // Vector @  0xBB

#elif defined __ICC8051__
#pragma vector=0xBB
__interrupt void SMC1_ISR(void)

#elif defined __SDCC__
void SMC2_ISR(void) __interrupt (23)            // Vector @  0xBB
#endif
{
    PUSH_SFRS;

    POP_SFRS;
}

#endif
  /**
  * @brief This API configures Interrupt level
  * @param[in] u8InterruptSource . Valid values are the interrupt name:
  *                       - \ref INT_INT0      :
  *                       - \ref INT_BOD        :
  *                       - \ref INT_WDT        :
  *                       - \ref INT_Timer0     :
  *                       - \ref INT_I2C0       :
  *                       - \ref INT_ADC        :
  *                       - \ref INT_INT1       :
  *                       - \ref INT_PIT        :
  *                       - \ref INT_Timer1     :
  *                       - \ref INT_UART0      :
  *                       - \ref INT_PWM0_Brake
  *                       - \ref INT_SPI0       :
  *                       - \ref INT_Timer2     :
  *                       - \ref INT_Capture    :
  *                       - \ref INT_PWM0       : 
  *                       - \ref INT_Timer3     :
  *                       - \ref INT_WKT        :
  *                       - \ref INT_PWM1       :
  *                       - \ref INT_PWM2           :
  *                       - \ref INT_PWM3           :
  *                       - \ref INT_SMC0           :
  *                       - \ref INT_SMC1           :
  *                       - \ref INT_SMC2           :
  * @note      u8u8InterruptPriorityLevel.Valid values are the interrupt level number:
  *                       - \ref 0~3            :
  * @exmaple : Set_Interrupt_Priority_Level(INT_ADC, 1);
  */
void Set_Interrupt_Priority_Level( uint8_t u8InterruptSource, uint8_t u8u8InterruptPriorityLevel)
{
   switch (u8InterruptSource)
   {
        case INT_INT0        :
          switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PX0; clr_IPH_PX0H; break;
            case 1:  clr_IP_PX0; set_IPH_PX0H; break;
            case 2:  set_IP_PX0; clr_IPH_PX0H; break;
            case 3:  clr_IP_PX0; set_IPH_PX0H; break;
          }
        case INT_BOD          :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PBOD; clr_IPH_PBODH; break;
            case 1:  clr_IP_PBOD; set_IPH_PBODH; break;
            case 2:  set_IP_PBOD; clr_IPH_PBODH; break;
            case 3:  set_IP_PBOD; set_IPH_PBODH; break;
          }
        case INT_WDT           :
               switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_EIP_PWDT; clr_EIPH_PWDTH; break;
            case 1:  clr_EIP_PWDT; set_EIPH_PWDTH; break;
            case 2:  set_EIP_PWDT; clr_EIPH_PWDTH; break;
            case 3:  set_EIP_PWDT; set_EIPH_PWDTH; break;
          }        
        case INT_Timer0        :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PT0; clr_IPH_PT0H; break;
            case 1:  clr_IP_PT0; set_IPH_PT0H; break;
            case 2:  set_IP_PT0; clr_IPH_PT0H; break;
            case 3:  set_IP_PT0; set_IPH_PT0H; break;
          }
        case INT_I2C0          :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_EIP_PI2C; clr_EIPH_PI2CH; break;
            case 1:  clr_EIP_PI2C; set_EIPH_PI2CH; break;
            case 2:  set_EIP_PI2C; clr_EIPH_PI2CH; break;
            case 3:  set_EIP_PI2C; set_EIPH_PI2CH; break;
          }
        case INT_ADC           :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PADC; clr_IPH_PADCH; break;
            case 1:  clr_IP_PADC; set_IPH_PADCH; break;
            case 2:  set_IP_PADC; clr_IPH_PADCH; break;
            case 3:  set_IP_PADC; set_IPH_PADCH; break;
          }        
        case INT_INT1        :
          switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PX1; clr_IPH_PX1H; break;
            case 1:  clr_IP_PX1; set_IPH_PX1H; break;
            case 2:  set_IP_PX1; clr_IPH_PX1H; break;
            case 3:  set_IP_PX1; set_IPH_PX1H; break;
          }
        case INT_PIT           :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_EIP_PPI; clr_EIPH_PPIH; break;
            case 1:  clr_EIP_PPI; set_EIPH_PPIH; break;
            case 2:  set_EIP_PPI; clr_EIPH_PPIH; break;
            case 3:  set_EIP_PPI; set_EIPH_PPIH; break;
          }        
        case INT_Timer1        :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PT1; clr_IPH_PT1H; break;
            case 1:  clr_IP_PT1; set_IPH_PT1H; break;
            case 2:  set_IP_PT1; clr_IPH_PT1H; break;
            case 3:  set_IP_PT1; set_IPH_PT1H; break;
          }
        case INT_UART0         :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_IP_PS; clr_IPH_PSH; break;
            case 1:  clr_IP_PS; set_IPH_PSH; break;
            case 2:  set_IP_PS; clr_IPH_PSH; break;
            case 3:  set_IP_PS; set_IPH_PSH; break;
          }        
        case INT_PWM0_Brake :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PFB; clr_EIPH_PFBH; break;
            case 1:  clr_EIP_PFB; set_EIPH_PFBH; break;
            case 2:  set_EIP_PFB; clr_EIPH_PFBH; break;
            case 3:  set_EIP_PFB; set_EIPH_PFBH; break;
          }
        case INT_SPI0          :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PSPI; clr_EIPH_PSPIH; break;
            case 1:  clr_EIP_PSPI; set_EIPH_PSPIH; break;
            case 2:  set_EIP_PSPI; clr_EIPH_PSPIH; break;
            case 3:  set_EIP_PSPI; set_EIPH_PSPIH; break;
          }        
        case INT_Timer2        :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PT2; clr_EIPH_PT2H; break;
            case 1:  clr_EIP_PT2; set_EIPH_PT2H; break;
            case 2:  set_EIP_PT2; clr_EIPH_PT2H; break;
            case 3:  set_EIP_PT2; set_EIPH_PT2H; break;
          }         
        case INT_Capture       :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PCAP; clr_EIPH_PCAPH; break;
            case 1:  clr_EIP_PCAP; set_EIPH_PCAPH; break;
            case 2:  set_EIP_PCAP; clr_EIPH_PCAPH; break;
            case 3:  set_EIP_PCAP; set_EIPH_PCAPH; break;
          }
        case INT_PWM0          :                          
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PPWM; clr_EIPH_PPWMH; break;
            case 1:  clr_EIP_PPWM; set_EIPH_PPWMH; break;
            case 2:  set_EIP_PPWM; clr_EIPH_PPWMH; break;
            case 3:  set_EIP_PPWM; set_EIPH_PPWMH; break;
          }
        case INT_UART1         :
             switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PS_1; clr_EIPH1_PSH_1; break;
            case 1:  clr_EIP1_PS_1; set_EIPH1_PSH_1; break;
            case 2:  set_EIP1_PS_1; clr_EIPH1_PSH_1; break;
            case 3:  set_EIP1_PS_1; set_EIPH1_PSH_1; break;
          }        
        case INT_Timer3        :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PT3; clr_EIPH1_PT3H; break;
            case 1:  clr_EIP1_PT3; set_EIPH1_PT3H; break;
            case 2:  set_EIP1_PT3; clr_EIPH1_PT3H; break;
            case 3:  set_EIP1_PT3; set_EIPH1_PT3H; break;
          } 
        case INT_WKT           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PWKT; clr_EIPH1_PWKTH; break;
            case 1:  clr_EIP1_PWKT; set_EIPH1_PWKTH; break;
            case 2:  set_EIP1_PWKT; clr_EIPH1_PWKTH; break;
            case 3:  set_EIP1_PWKT; set_EIPH1_PWKTH; break;
          }
        case INT_PWM1           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PPWM1; clr_EIPH1_PPWM1H; break;
            case 1:  clr_EIP1_PPWM1; set_EIPH1_PPWM1H; break;
            case 2:  set_EIP1_PPWM1; clr_EIPH1_PPWM1H; break;
            case 3:  set_EIP1_PPWM1; set_EIPH1_PPWM1H; break;
          }
        case INT_PWM2           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PPWM2; clr_EIPH1_PPWM2H; break;
            case 1:  clr_EIP1_PPWM2; set_EIPH1_PPWM2H; break;
            case 2:  set_EIP1_PPWM2; clr_EIPH1_PPWM2H; break;
            case 3:  set_EIP1_PPWM2; set_EIPH1_PPWM2H; break;
          }
          case INT_PWM3           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PPWM3; clr_EIPH1_PPWM3H; break;
            case 1:  clr_EIP1_PPWM3; set_EIPH1_PPWM3H; break;
            case 2:  set_EIP1_PPWM3; clr_EIPH1_PPWM3H; break;
            case 3:  set_EIP1_PPWM3; set_EIPH1_PPWM3H; break;
          }
          case INT_SMC0           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP2_PSC0; clr_EIPH2_PSC0H; break;
            case 1:  clr_EIP2_PSC0; set_EIPH2_PSC0H; break;
            case 2:  set_EIP2_PSC0; clr_EIPH2_PSC0H; break;
            case 3:  set_EIP2_PSC0; set_EIPH2_PSC0H; break;
          }
         case INT_SMC1           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP2_PSC1; clr_EIPH2_PSC1H; break;
            case 1:  clr_EIP2_PSC1; set_EIPH2_PSC1H; break;
            case 2:  set_EIP2_PSC1; clr_EIPH2_PSC1H; break;
            case 3:  set_EIP2_PSC1; set_EIPH2_PSC1H; break;
          }
          case INT_SMC2           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP2_PSC2; clr_EIPH2_PSC2H; break;
            case 1:  clr_EIP2_PSC2; set_EIPH2_PSC2H; break;
            case 2:  set_EIP2_PSC2; clr_EIPH2_PSC2H; break;
            case 3:  set_EIP2_PSC2; set_EIPH2_PSC2H; break;
          }
        break;
   }
 }
