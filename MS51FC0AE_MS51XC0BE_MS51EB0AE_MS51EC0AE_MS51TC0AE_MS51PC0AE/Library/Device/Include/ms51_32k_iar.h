/*--------------------------------------------------------------------------*/
/* ms51_32k_iar.h                                                           */
/*                                                                          */
/* Header file for Nuvoton MS51 IAR format                                  */
/* -------------------------------------------------------------------------*/

/******************************************************************************/
/*                         Peripheral header files                            */
/******************************************************************************/
#include "sfr_macro_ms51_32k.h"

/*  BYTE Registers  */
/*  SFR page 0      */
__sfr __no_init volatile union
{
  unsigned char P0; /* Port 0 */
  struct /* Port 0 */
  { 
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } P0_bit;
} @ 0x80;
__sfr __no_init volatile unsigned char  SP          @ 0x81;
__sfr __no_init volatile unsigned char  DPL         @ 0x82;
__sfr __no_init volatile unsigned char  DPH         @ 0x83;
__sfr __no_init volatile unsigned char  RCTRIM0     @ 0x84;
__sfr __no_init volatile unsigned char  RCTRIM1     @ 0x85;  
__sfr __no_init volatile unsigned char  RWKL        @ 0x86;
__sfr __no_init volatile unsigned char  PCON        @ 0x87;

__sfr __no_init volatile union
{
  unsigned char TCON; /* Timer Control */
  struct /* Timer Control */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } TCON_bit;
} @ 0x88;                            
__sfr __no_init volatile unsigned char  TMOD        @ 0x89;
__sfr __no_init volatile unsigned char  TL0         @ 0x8A;
__sfr __no_init volatile unsigned char  TL1         @ 0x8B;
__sfr __no_init volatile unsigned char  TH0         @ 0x8C;
__sfr __no_init volatile unsigned char  TH1         @ 0x8D;
__sfr __no_init volatile unsigned char  CKCON       @ 0x8E;
__sfr __no_init volatile unsigned char  WKCON       @ 0x8F;
                                              

__sfr __no_init volatile union
{
  unsigned char P1; /* Port 1 */
  struct /* Port 1 */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;    
  } P1_bit;
} @ 0x90;
__sfr __no_init volatile unsigned char SFRS        @ 0x91; 
__sfr __no_init volatile unsigned char CAPCON0     @ 0x92;
__sfr __no_init volatile unsigned char CAPCON1     @ 0x93;
__sfr __no_init volatile unsigned char CAPCON2     @ 0x94;
__sfr __no_init volatile unsigned char CKDIV       @ 0x95;
__sfr __no_init volatile unsigned char CKSWT       @ 0x96; //TA Protection
__sfr __no_init volatile unsigned char CKEN        @ 0x97; //TA Protection


__sfr __no_init volatile union
{
  unsigned char SCON; /* Serial Control */
  struct /* Serial Control */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } SCON_bit;
} @ 0x98;
__sfr __no_init volatile unsigned char SBUF        @ 0x99;
__sfr __no_init volatile unsigned char SBUF_1      @ 0x9A;
__sfr __no_init volatile unsigned char EIE         @ 0x9B;
__sfr __no_init volatile unsigned char EIE1        @ 0x9C;
__sfr __no_init volatile unsigned char CHPCON      @ 0x9F; //TA Protection
   
__sfr __no_init volatile union
{
  unsigned char P2; /* Port 2 */
  struct /* Port 2 */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } P2_bit;
} @ 0xA0;
__sfr __no_init volatile unsigned char AUXR1       @ 0xA2;
__sfr __no_init volatile unsigned char BODCON0     @ 0xA3; //TA Protection
__sfr __no_init volatile unsigned char IAPTRG      @ 0xA4; //TA Protection
__sfr __no_init volatile unsigned char IAPUEN      @ 0xA5;  //TA Protection
__sfr __no_init volatile unsigned char IAPAL       @ 0xA6;
__sfr __no_init volatile unsigned char IAPAH       @ 0xA7;


__sfr __no_init volatile union
{
  unsigned char IE; /* Interrupt Enable */
  struct /* Interrupt Enable */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } IE_bit;
} @ 0xA8;
__sfr __no_init volatile unsigned char SADDR       @ 0xA9;
__sfr __no_init volatile unsigned char WDCON       @ 0xAA; //TA Protection
__sfr __no_init volatile unsigned char BODCON1     @ 0xAB; //TA Protection
__sfr __no_init volatile unsigned char P3M1        @ 0xAC;
__sfr __no_init volatile unsigned char P3M2        @ 0xAD;
__sfr __no_init volatile unsigned char IAPFD       @ 0xAE;
__sfr __no_init volatile unsigned char IAPCN       @ 0xAF;

__sfr __no_init volatile union
{
  unsigned char P3; /* Port 3 */
  struct /* Port 3 */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } P3_bit;
} @ 0xB0;
__sfr __no_init volatile unsigned char P0M1       @ 0xB1;
__sfr __no_init volatile unsigned char P0M2       @ 0xB2;
__sfr __no_init volatile unsigned char P1M1       @ 0xB3;
__sfr __no_init volatile unsigned char P1M2       @ 0xB4;
__sfr __no_init volatile unsigned char TOE        @ 0xB5; 
__sfr __no_init volatile unsigned char IPH        @ 0xB7;


__sfr __no_init volatile union
{
  unsigned char IP; /* IP  */
  struct /* IP  */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } IP_bit;
} @ 0xB8;
__sfr __no_init volatile unsigned char SADEN       @ 0xB9;
__sfr __no_init volatile unsigned char SADEN_1     @ 0xBA;
__sfr __no_init volatile unsigned char SADDR_1     @ 0xBB;
__sfr __no_init volatile unsigned char I2DAT       @ 0xBC;
__sfr __no_init volatile unsigned char I2STAT      @ 0xBD;
__sfr __no_init volatile unsigned char I2CLK       @ 0xBE;
__sfr __no_init volatile unsigned char I2TOC       @ 0xBF;


__sfr __no_init volatile union
{
  unsigned char I2CON; /* I2CON  */
  struct /* I2CON  */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } I2CON_bit;
} @ 0xC0;
__sfr __no_init volatile unsigned char I2ADDR      @ 0xC1;
__sfr __no_init volatile unsigned char ADCRL       @ 0xC2;
__sfr __no_init volatile unsigned char ADCRH       @ 0xC3;
__sfr __no_init volatile unsigned char T3CON       @ 0xC4;
__sfr __no_init volatile unsigned char RL3         @ 0xC5;
__sfr __no_init volatile unsigned char RH3         @ 0xC6;
__sfr __no_init volatile unsigned char TA          @ 0xC7;


__sfr __no_init volatile union
{
  unsigned char T2CON; /* Timer 2 Control */
  struct /* Timer 2 Control */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } T2CON_bit;
} @ 0xC8;
__sfr __no_init volatile unsigned char T2MOD       @ 0xC9;
__sfr __no_init volatile unsigned char RCMP2L      @ 0xCA;
__sfr __no_init volatile unsigned char RCMP2H      @ 0xCB;
__sfr __no_init volatile unsigned char TL2         @ 0xCC; 
__sfr __no_init volatile unsigned char TH2         @ 0xCD;
__sfr __no_init volatile unsigned char ADCMPL      @ 0xCE;
__sfr __no_init volatile unsigned char ADCMPH      @ 0xCF;

__sfr __no_init volatile union
{
  unsigned char PSW; /* Program Status Word */
  struct /* Program Status Word */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;    
  } PSW_bit;
} @ 0xD0;
__sfr __no_init volatile unsigned char PWM0PH         @ 0xD1;
__sfr __no_init volatile unsigned char PWM0C0H        @ 0xD2;
__sfr __no_init volatile unsigned char PWM0C1H        @ 0xD3;
__sfr __no_init volatile unsigned char PWM0C2H        @ 0xD4;
__sfr __no_init volatile unsigned char PWM0C3H        @ 0xD5;
__sfr __no_init volatile unsigned char PNP            @ 0xD6;
__sfr __no_init volatile unsigned char PWM0FBD        @ 0xD7;


__sfr __no_init volatile union
{
  unsigned char PWM0CON0; /* PWMCON0  */
  struct /* PWMCON0  */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;    
  } PWMCON0_bit;
} @ 0xD8;
__sfr __no_init volatile unsigned char PWM0PL        @ 0xD9;
__sfr __no_init volatile unsigned char PWM0C0L       @ 0xDA;
__sfr __no_init volatile unsigned char PWM0C1L       @ 0xDB;
__sfr __no_init volatile unsigned char PWM0C2L       @ 0xDC;
__sfr __no_init volatile unsigned char PWM0C3L       @ 0xDD;
__sfr __no_init volatile unsigned char PIOCON0       @ 0xDE;
__sfr __no_init volatile unsigned char PWM0CON1      @ 0xDF;


__sfr __no_init volatile union
{
  unsigned char ACC; /* Accumulator */
  struct /* Accumulator */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;    
  } ACC_bit;
} @ 0xE0;
__sfr __no_init volatile unsigned char ADCCON1     @ 0xE1;
__sfr __no_init volatile unsigned char ADCCON2     @ 0xE2;
__sfr __no_init volatile unsigned char ADCDLY      @ 0xE3;
__sfr __no_init volatile unsigned char C0L         @ 0xE4;
__sfr __no_init volatile unsigned char C0H         @ 0xE5;
__sfr __no_init volatile unsigned char C1L         @ 0xE6;
__sfr __no_init volatile unsigned char C1H         @ 0xE7;


__sfr __no_init volatile union
{
  unsigned char ADCCON0; /* ADCCON0  */
  struct /* ADCCON0  */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } ADCCON0_bit;
} @ 0xE8;
__sfr __no_init volatile unsigned char PICON       @ 0xE9;
__sfr __no_init volatile unsigned char PINEN       @ 0xEA;
__sfr __no_init volatile unsigned char PIPEN       @ 0xEB;
__sfr __no_init volatile unsigned char PIF         @ 0xEC;
__sfr __no_init volatile unsigned char C2L         @ 0xED;
__sfr __no_init volatile unsigned char C2H         @ 0xEE;
__sfr __no_init volatile unsigned char EIP         @ 0xEF;


__sfr __no_init volatile union
{
  unsigned char B; /* B Register */
  struct /* B Register */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } B_bit;
} @ 0xF0;
__sfr __no_init volatile unsigned char CAPCON3       @ 0xF1;
__sfr __no_init volatile unsigned char CAPCON4       @ 0xF2;
__sfr __no_init volatile unsigned char SPCR          @ 0xF3;
__sfr __no_init volatile unsigned char SPSR          @ 0xF4;
__sfr __no_init volatile unsigned char SPDR          @ 0xF5;
__sfr __no_init volatile unsigned char AINDIDS0      @ 0xF6;
__sfr __no_init volatile unsigned char EIPH          @ 0xF7;

__sfr __no_init volatile union
{
  unsigned char SCON_1 ; /* SCON_1  Register */
  struct /* SCON_1  Register */
  {
    unsigned char BIT0 : 1;
    unsigned char BIT1 : 1;
    unsigned char BIT2 : 1;
    unsigned char BIT3 : 1;
    unsigned char BIT4 : 1;
    unsigned char BIT5 : 1;
    unsigned char BIT6 : 1;
    unsigned char BIT7 : 1;
  } SCON_1_bit;
} @ 0xF8;
__sfr __no_init volatile unsigned char PWM0DTEN       @ 0xF9; //TA Protection
__sfr __no_init volatile unsigned char PWM0DTCNT      @ 0xFA; //TA Protection
__sfr __no_init volatile unsigned char PWM0MEN        @ 0xFB;
__sfr __no_init volatile unsigned char PWM0MD         @ 0xFC;
__sfr __no_init volatile unsigned char PORDIS         @ 0xFD;
__sfr __no_init volatile unsigned char EIP1           @ 0xFE;
__sfr __no_init volatile unsigned char EIPH1          @ 0xFF;
   
/*  SFR page 1      */
__sfr __no_init volatile unsigned char P3S            @ 0xAC; 
__sfr __no_init volatile unsigned char P3SR           @ 0xAD; 
                                                        
__sfr __no_init volatile unsigned char P0S            @ 0xB1; 
__sfr __no_init volatile unsigned char P0SR           @ 0xB2; 
__sfr __no_init volatile unsigned char P1S            @ 0xB3; 
__sfr __no_init volatile unsigned char P1SR           @ 0xB4; 
__sfr __no_init volatile unsigned char PWM0INTC       @ 0xB7; 
                                                        
__sfr __no_init volatile unsigned char PWM0C4H        @ 0xC4; 
__sfr __no_init volatile unsigned char PWM0C5H        @ 0xC5; 
__sfr __no_init volatile unsigned char PIOCON1        @ 0xC6; 
                                                        
__sfr __no_init volatile unsigned char PWM0C4L        @ 0xCC; 
__sfr __no_init volatile unsigned char PWM0C5L        @ 0xCD; 
                                                        
__sfr __no_init volatile unsigned char SPCR2          @ 0xF3; 
                                      
__sfr __no_init volatile unsigned char LVRDIS         @ 0xFF; 
                                      
/* MS51_32K SFR BYTE page 2  */       
__sfr __no_init volatile unsigned char ADCBAL         @ 0x84; 
__sfr __no_init volatile unsigned char ADCBAH         @ 0x85; 
__sfr __no_init volatile unsigned char ADCCON3        @ 0x86; 
                                      
__sfr __no_init volatile unsigned char P2M1           @ 0x89; 
__sfr __no_init volatile unsigned char P2M2           @ 0x8A; 
__sfr __no_init volatile unsigned char P2SR           @ 0x8B; 
__sfr __no_init volatile unsigned char P2S            @ 0x8C; 
__sfr __no_init volatile unsigned char ADCSN          @ 0x8D; 
__sfr __no_init volatile unsigned char ADCCN          @ 0x8E; 
__sfr __no_init volatile unsigned char ADCSR          @ 0x8F; 
                                      
__sfr __no_init volatile unsigned char P0UP           @ 0x92; 
__sfr __no_init volatile unsigned char P1UP           @ 0x93; 
__sfr __no_init volatile unsigned char P2UP           @ 0x94; 
__sfr __no_init volatile unsigned char P3UP           @ 0x95; 
__sfr __no_init volatile unsigned char RWKH           @ 0x97; 
                                      
__sfr __no_init volatile unsigned char AINDIDS1       @ 0x99; 
__sfr __no_init volatile unsigned char P0DW           @ 0x9A; 
__sfr __no_init volatile unsigned char P1DW           @ 0x9B; 
__sfr __no_init volatile unsigned char P2DW           @ 0x9C; 
__sfr __no_init volatile unsigned char P3DW           @ 0x9D; 
                                      
__sfr __no_init volatile unsigned char AUXR2          @ 0xA1; 
__sfr __no_init volatile unsigned char AUXR3          @ 0xA2; 
__sfr __no_init volatile unsigned char AUXR4          @ 0xA3; 
__sfr __no_init volatile unsigned char AUXR5          @ 0xA4; 
__sfr __no_init volatile unsigned char AUXR6          @ 0xA5; 
__sfr __no_init volatile unsigned char AUXR7          @ 0xA6; 
__sfr __no_init volatile unsigned char AUXR8          @ 0xA7; 
                                      
__sfr __no_init volatile unsigned char PWM1PH         @ 0xA9; 
__sfr __no_init volatile unsigned char PWM1C0H        @ 0xAA; 
__sfr __no_init volatile unsigned char PWM1C1H        @ 0xAB; 
__sfr __no_init volatile unsigned char PWM1MD         @ 0xAC; 
__sfr __no_init volatile unsigned char PWM1MEN        @ 0xAD; 
                                      
__sfr __no_init volatile unsigned char PWM1PL         @ 0xB1; 
__sfr __no_init volatile unsigned char PWM1C0L        @ 0xB2; 
__sfr __no_init volatile unsigned char PWM1C1L        @ 0xB3; 
__sfr __no_init volatile unsigned char PWM1CON0       @ 0xB4; 
__sfr __no_init volatile unsigned char PWM1CON1       @ 0xB5; 
__sfr __no_init volatile unsigned char PWM1INTC       @ 0xB6; 
__sfr __no_init volatile unsigned char PIOCON2        @ 0xB7; 
                                      
__sfr __no_init volatile unsigned char PWM2PH         @ 0xB9; 
__sfr __no_init volatile unsigned char PWM2C0H        @ 0xBA; 
__sfr __no_init volatile unsigned char PWM2C1H        @ 0xBB; 
__sfr __no_init volatile unsigned char PWM2MD         @ 0xBC; 
__sfr __no_init volatile unsigned char PWM2MEN        @ 0xBD; 
                                      
__sfr __no_init volatile unsigned char PWM2PL         @ 0xC1; 
__sfr __no_init volatile unsigned char PWM2C0L        @ 0xC2; 
__sfr __no_init volatile unsigned char PWM2C1L        @ 0xC3; 
__sfr __no_init volatile unsigned char PWM2CON0       @ 0xC4; 
__sfr __no_init volatile unsigned char PWM2CON1       @ 0xC5; 
__sfr __no_init volatile unsigned char PWM2INTC       @ 0xC6; 
                                      
__sfr __no_init volatile unsigned char PWM3PH         @ 0xC9; 
__sfr __no_init volatile unsigned char PWM3C0H        @ 0xCA; 
__sfr __no_init volatile unsigned char PWM3C1H        @ 0xCB; 
__sfr __no_init volatile unsigned char PWM3MD         @ 0xCC; 
__sfr __no_init volatile unsigned char PWM3MEN        @ 0xCD; 
__sfr __no_init volatile unsigned char EIP2           @ 0xCE; 
__sfr __no_init volatile unsigned char EIPH2          @ 0xCF; 
                                      
__sfr __no_init volatile unsigned char PWM3PL         @ 0xD1; 
__sfr __no_init volatile unsigned char PWM3C0L        @ 0xD2; 
__sfr __no_init volatile unsigned char PWM3C1L        @ 0xD3; 
__sfr __no_init volatile unsigned char PWM3CON0       @ 0xD4; 
__sfr __no_init volatile unsigned char PWM3CON1       @ 0xD5; 
__sfr __no_init volatile unsigned char PWM3INTC       @ 0xD6; 
__sfr __no_init volatile unsigned char XTLCON         @ 0xD7; 
                                      
__sfr __no_init volatile unsigned char SC0DR          @ 0xD9; 
__sfr __no_init volatile unsigned char SC0EGT         @ 0xDA; 
__sfr __no_init volatile unsigned char SC0ETURD0      @ 0xDB; 
__sfr __no_init volatile unsigned char SC0ETURD1      @ 0xDC; 
__sfr __no_init volatile unsigned char SC0IE          @ 0xDD; 
__sfr __no_init volatile unsigned char SC0IS          @ 0xDE; 
__sfr __no_init volatile unsigned char SC0TSR         @ 0xDF; 
                                      
__sfr __no_init volatile unsigned char SC1DR          @ 0xE1; 
__sfr __no_init volatile unsigned char SC1EGT         @ 0xE2; 
__sfr __no_init volatile unsigned char SC1ETURD0      @ 0xE3; 
__sfr __no_init volatile unsigned char SC1ETURD1      @ 0xE4; 
__sfr __no_init volatile unsigned char SC1IE          @ 0xE5; 
__sfr __no_init volatile unsigned char SC1IS          @ 0xE6; 
__sfr __no_init volatile unsigned char SC1TSR         @ 0xE7; 
                                      
__sfr __no_init volatile unsigned char SC2DR          @ 0xE9; 
__sfr __no_init volatile unsigned char SC2EGT         @ 0xEA; 
__sfr __no_init volatile unsigned char SC2ETURD0      @ 0xEB; 
__sfr __no_init volatile unsigned char SC2ETURD1      @ 0xEC; 
__sfr __no_init volatile unsigned char SC2IE          @ 0xED; 
__sfr __no_init volatile unsigned char SC2IS          @ 0xEE; 
__sfr __no_init volatile unsigned char SC2TSR         @ 0xEF; 
                                      
__sfr __no_init volatile unsigned char SC0CR0         @ 0xF1; 
__sfr __no_init volatile unsigned char SC0CR1         @ 0xF2; 
__sfr __no_init volatile unsigned char SC1CR0         @ 0xF3; 
__sfr __no_init volatile unsigned char SC1CR1         @ 0xF4; 
__sfr __no_init volatile unsigned char SC2CR0         @ 0xF5; 
__sfr __no_init volatile unsigned char SC2CR1         @ 0xF6; 
__sfr __no_init volatile unsigned char PIPS7          @ 0xF7; 
                                      
__sfr __no_init volatile unsigned char PIPS0          @ 0xF9; 
__sfr __no_init volatile unsigned char PIPS1          @ 0xFA; 
__sfr __no_init volatile unsigned char PIPS2          @ 0xFB; 
__sfr __no_init volatile unsigned char PIPS3          @ 0xFC; 
__sfr __no_init volatile unsigned char PIPS4          @ 0xFD; 
__sfr __no_init volatile unsigned char PIPS5          @ 0xFE; 
__sfr __no_init volatile unsigned char PIPS6          @ 0xFF; 



/*  BIT Registers  */
/*  P0  */
#define P07         P0_bit.BIT7
#define P06         P0_bit.BIT6
#define P05         P0_bit.BIT5
#define P04         P0_bit.BIT4
#define P03         P0_bit.BIT3
#define P02         P0_bit.BIT2
#define P01         P0_bit.BIT1
#define P00         P0_bit.BIT0

/*  TCON  */
#define TF1         TCON_bit.BIT7
#define TR1         TCON_bit.BIT6
#define TF0         TCON_bit.BIT5
#define TR0         TCON_bit.BIT4
#define IE1         TCON_bit.BIT3
#define IT1         TCON_bit.BIT2
#define IE0         TCON_bit.BIT1
#define IT0         TCON_bit.BIT0
                    
/*  P1  */
#define P17         P1_bit.BIT7
#define P16         P1_bit.BIT6
#define P15         P1_bit.BIT5
#define P14         P1_bit.BIT4
#define P13         P1_bit.BIT3
#define P12         P1_bit.BIT2
#define P11         P1_bit.BIT1
#define P10         P1_bit.BIT0

/*  SCON  */
#define SM0         SCON_bit.BIT7 
#define FE          SCON_bit.BIT7 
#define SM1         SCON_bit.BIT6 
#define SM2         SCON_bit.BIT5 
#define REN         SCON_bit.BIT4 
#define TB8         SCON_bit.BIT3 
#define RB8         SCON_bit.BIT2 
#define TI          SCON_bit.BIT1 
#define RI          SCON_bit.BIT0 

/*  P2  */ 
#define P20	    P2_bit.BIT0
#define P21	    P2_bit.BIT1
#define P22	    P2_bit.BIT2
#define P23	    P2_bit.BIT3
#define P24	    P2_bit.BIT4
#define P25	    P2_bit.BIT5
#define P26	    P2_bit.BIT6
#define P27	    P2_bit.BIT7

/*  IE  */
#define EA          IE_bit.BIT7
#define EADC        IE_bit.BIT6
#define EBOD        IE_bit.BIT5
#define ES          IE_bit.BIT4
#define ET1         IE_bit.BIT3
#define EX1         IE_bit.BIT2
#define ET0         IE_bit.BIT1
#define EX0         IE_bit.BIT0

/*  P3  */  
#define P30	    P3_bit.BIT0
#define P31	    P3_bit.BIT1
#define P32	    P3_bit.BIT2
#define P33	    P3_bit.BIT3
#define P34	    P3_bit.BIT4
#define P35	    P3_bit.BIT5
#define P36	    P3_bit.BIT6
#define P37	    P3_bit.BIT7
/*  IP  */
#define PADC        IP_bit.BIT6
#define PBOD        IP_bit.BIT5
#define PS          IP_bit.BIT4
#define PT1         IP_bit.BIT3
#define PX1         IP_bit.BIT2
#define PT0         IP_bit.BIT1
#define PX0         IP_bit.BIT0

/*  I2CON  */
#define I2CEN       I2CON_bit.BIT6
#define STA         I2CON_bit.BIT5
#define STO         I2CON_bit.BIT4
#define SI          I2CON_bit.BIT3
#define AA          I2CON_bit.BIT2
#define I2CPX	    I2CON_bit.BIT0

/*  T2CON  */
#define TF2         T2CON_bit.BIT7
#define TR2         T2CON_bit.BIT2
#define CM_RL2      T2CON_bit.BIT0

/*  PSW */
#define CY          PSW.BIT7
#define AC          PSW.BIT6
#define F0          PSW.BIT5
#define RS1         PSW.BIT4
#define RS0         PSW.BIT3
#define OV          PSW.BIT2
#define P           PSW.BIT0

/*  PWMCON0  */
#define PWMRUN      PWMCON0_bit.BIT7
#define LOAD        PWMCON0_bit.BIT6
#define PWMF        PWMCON0_bit.BIT5
#define CLRPWM      PWMCON0_bit.BIT4

/*  ADCCON0  */
#define ADCF        ADCCON0_bit.BIT7
#define ADCS        ADCCON0_bit.BIT6
#define ETGSEL1     ADCCON0_bit.BIT5
#define ETGSEL0     ADCCON0_bit.BIT4
#define ADCHS3      ADCCON0_bit.BIT3
#define ADCHS2      ADCCON0_bit.BIT2
#define ADCHS1      ADCCON0_bit.BIT1
#define ADCHS0      ADCCON0_bit.BIT0

/*  SCON_1  */
#define SM0_1       SCON_1_bit.BIT7
#define FE_1        SCON_1_bit.BIT7 
#define SM1_1       SCON_1_bit.BIT6 
#define SM2_1       SCON_1_bit.BIT5 
#define REN_1       SCON_1_bit.BIT4 
#define TB8_1       SCON_1_bit.BIT3 
#define RB8_1       SCON_1_bit.BIT2 
#define TI_1        SCON_1_bit.BIT1 
#define RI_1        SCON_1_bit.BIT0















