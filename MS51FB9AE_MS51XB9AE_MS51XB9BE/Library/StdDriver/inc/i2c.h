#define I2C0    0
#define I2C1    1

#define      I2C_R    1
#define      I2C_W    0

void I2C_Master_Open( uint32_t u32SYSCLK, uint32_t u32I2CCLK);
void I2C_Slave_Open( uint8_t u8SlaveAddress0);
void I2C_Close(void);
void I2C_Interrupt(uint8_t u8I2CStatus);
uint8_t I2C_GetStatus(void);
void I2C_SetSlaveAddrMask( uint8_t u8SlaveNo, uint8_t u8SlaveAddrMask);
void I2C_Timeout( uint8_t u8I2CTRStatus );
void I2C_ClearTimeoutFlag(void);
void I2C_Slave_Address_Mask( uint8_t u8I2CAddMaskStatus, uint8_t u8I2CAddMaskBit);
void I2C0_SI_Check(void);