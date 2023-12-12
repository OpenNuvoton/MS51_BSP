#if defined __C51__
extern uint8_t  SPTEMP;
extern uint8_t code lockdata;

#elif defined __ICC8051__
extern uint8_t  SPTEMP;
extern __code const char lockdata@0xFFFF = 0xFF;

#elif defined __SDCC__
extern uint8_t  SPTEMP;
extern __code uint8_t  lockdata;
#endif

void SPROM_CODE (void);
