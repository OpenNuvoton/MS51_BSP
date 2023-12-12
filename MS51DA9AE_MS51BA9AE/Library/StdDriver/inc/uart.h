#define UART0_Timer1  0
#define UART0_Timer3  1
#define UART1_Timer3  2
#define UART0 0
#define UART1 1

void UART_Open(uint32_t u32SysClock, uint8_t u8UARTPort,uint32_t u32Baudrate);
void UART_Send_Data(uint8_t UARTPort, uint8_t c);
extern uint8_t Receive_Data(uint8_t UARTPort);
void Enable_UART0_VCOM_printf_24M_115200(void);

extern   BIT PRINTFG,uart0_receive_flag,uart1_receive_flag;
extern   uint8_t uart0_receive_data,uart1_receive_data;

