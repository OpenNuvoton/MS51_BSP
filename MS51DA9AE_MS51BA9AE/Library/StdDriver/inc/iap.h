#if defined __C51__
extern uint8_t xdata DIDBuffer[2];
extern uint8_t xdata PIDBuffer[2];
extern uint8_t xdata UIDBuffer[12];
extern uint8_t xdata UCIDBuffer[12];
extern uint8_t xdata IAPDataBuf[128];
extern uint8_t xdata IAPCFBuf[5];

#elif defined __ICC8051__
extern uint8_t __xdata DIDBuffer[2];
extern uint8_t __xdata PIDBuffer[2];
extern uint8_t __xdata UIDBuffer[12];
extern uint8_t __xdata UCIDBuffer[12];
extern uint8_t __xdata IAPDataBuf[128];
extern uint8_t __xdata IAPCFBuf[5];

#elif defined __SDCC__
extern __xdata volatile uint8_t DIDBuffer[2];
extern __xdata volatile uint8_t PIDBuffer[2];
extern __xdata volatile uint8_t UIDBuffer[12];
extern __xdata volatile uint8_t UCIDBuffer[12];
extern __xdata volatile uint8_t IAPDataBuf[128];
extern __xdata volatile uint8_t IAPCFBuf[5];
#endif

extern BIT  ConfigModifyFlag;

void Trigger_IAP(void);
void Erase_LDROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize);
void Erase_Verify_LDROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize);
void Program_LDROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize);
void Program_Verify_LDROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize);
void Erase_APROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize);
void Erase_Verify_APROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize);
void Program_APROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize);
void Program_Verify_APROM(uint16_t u16IAPStartAddress, uint16_t u16IAPDataSize);
void Modify_CONFIG(uint8_t u8CF0,uint8_t u8CF1,uint8_t u8CF2,uint8_t u8CF3,uint8_t u8CF4);
void Read_CONFIG(void);
void Read_UID(void);
void Read_UCID(void);
void Read_DID(void);
void Read_PID(void);

