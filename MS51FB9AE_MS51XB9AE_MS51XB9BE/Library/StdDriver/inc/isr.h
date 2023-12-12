#define  INT_INT0         1
#define  INT_BOD          2
#define  INT_WDT          3
#define  INT_Timer0       4
#define  INT_I2C0         5
#define  INT_ADC          6
#define  INT_INT1         7
#define  INT_PIT          8
#define  INT_Timer1       9
#define  INT_UART0        11
#define  INT_PWM0_Brake   12
#define  INT_SPI0         13
#define  INT_Timer2       14
#define  INT_Capture      15
#define  INT_PWM0         16
#define  INT_UART1        17
#define  INT_Timer3       18
#define  INT_WKT          19
#define  INT_SMC0         21
#define  INT_PDMA0        22
#define  INT_PDMA1        23
#define  INT_SPI1         24
#define  INT_ACMP         25
#define  INT_I2C1         26
#define  INT_PWM123       27
#define  INT_SMC1         28
#define  INT_PDMA2        29
#define  INT_PDMA3        30
#define  INT_RTC          31

void Set_Interrupt_Priority_Level( uint8_t u8InterruptSource, uint8_t u8u8InterruptPriorityLevel);