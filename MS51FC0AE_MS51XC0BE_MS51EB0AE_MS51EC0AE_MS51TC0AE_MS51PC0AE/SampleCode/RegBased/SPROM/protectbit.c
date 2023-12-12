/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "numicro_8051.h"

#if defined __C51__
uint8_t code lockdata [] = { 
    0xFF                        /* This byte as 0xFF means unlock SPROM. Any other value is lock*/
//    0X00                      /* Define this value is lock*/
};

#elif defined __ICC8051__
__code const char lockdata@0xFFFF = 0xFF;    /* This byte as 0xFF means unlock SPROM. Any other value is lock*/
// __code const char lockdata@0xFFFF = 0x00; /* Define this value is lock*/

#elif defined __SDCC__
uint8_t __code lockdata [] = {
    0xFF                        /* This byte as 0xFF means unlock SPROM. Any other value is lock*/
//    0X00                      /* Define this value is lock*/
};

#endif
 




