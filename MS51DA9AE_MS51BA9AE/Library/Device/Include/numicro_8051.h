
/* for Keil */
#if defined __C51__
#include "ms51_8k_keil.h"

/* for IAR */
#elif defined __ICC8051__
#include "ms51_8k_iar.h"

/* for SDCC */
#elif defined __SDCC__
#include "ms51_8k_sdcc.h"

#endif
