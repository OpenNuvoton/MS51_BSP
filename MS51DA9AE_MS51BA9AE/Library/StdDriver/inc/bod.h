
#define   VBOD_1_8           0x70
#define   VBOD_2_0           0x50
#define   VBOD_2_4           0x40
#define   VBOD_2_7           0x30
#define   VBOD_3_0           0x20
#define   VBOD_3_7           0x10
#define   VBOD_4_4           0x00

#define   BOD_Reset_Enable   0x04
#define   BOD_Reset_Disable  0

#define   LPBOD_Mode_Normal  0
#define   LPBOD_Mode_1       0x02
#define   LPBOD_Mode_2       0x04
#define   LPBOD_Mode_3       0x06


void BOD_Open(uint8_t u8bodstatus, uint8_t u8bodlevel, uint8_t u8bodresetstatus);
void BOD_LowPower(uint8_t u8LPBDD);
void BOD_Interrupt_Enable (uint8_t u8bodINTstatus);

