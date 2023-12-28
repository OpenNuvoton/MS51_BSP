#define PWM_FSYS         0
#define PWM_TIMER1       1

#define Independent      0
#define Complementary    1
#define Synchronous      2

#define EdgeAligned      0
#define CenterAligned    1

#define PWM0_CH01        0
#define PWM0_CH23        1
#define PWM0_CH45        2
#define PWM0_ALL         3

#define PWM1_CH01        0
#define PWM1_CH23        1
#define PWM1_CH45        2
#define PWM1_ALL         3

void PWM0_ClockSource(uint8_t u8PWMCLKSource, uint8_t u8PWM0CLKDIV);
void PWM0_ConfigOutputChannel(uint8_t u8PWM0ChannelNum,
                              uint8_t u8PWM0OPMode,
                              uint8_t u8PWM0PwmType,
                              uint16_t u16PWM0Frequency,
                              uint16_t u16PWM0DutyCycle);
void PWM0_ChannelDuty(uint8_t u8PWM0ChannelNum,
                      uint16_t u16PWM0DutyCycle);
void PWM0_DeadZoneEnable(uint8_t u8PWM0Pair, uint16_t u16PWM0DZValue);
void PWM0_DeadZone_ALL_Disable(void);
void PWM0_RUN(void);
void PWM0_STOP(void);

void PWM1_ClockSource(uint8_t u8PWMCLKSource, uint8_t u8PWM0CLKDIV);
void PWM1_ConfigOutputChannel(uint8_t u8PWM1ChannelNum,
                              uint8_t u8PWM1OPMode,
                              uint8_t u8PWM1PwmType,
                              uint32_t u32PWM1Frequency,
                              uint16_t u16PWM1DutyCycle);
void PWM1_DeadZoneEnable(uint8_t u8PWM0Pair, uint16_t u16PWM0DZValue);
void PWM1_DeadZone_ALL_Disable(void);
void PWM1_RUN(void);
void PWM1_STOP(void);
void PWM0_Reload(void);