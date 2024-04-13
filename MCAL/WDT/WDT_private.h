/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    15 APR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          15 APR, 2023       Abdullah R.Hebashi       Initial Creation 
***********************************************************/


#ifndef MCAL_WDT_WDT_PRIVATE_H
#define MCAL_WDT_WDT_PRIVATE_H


#define WDT_SLEEP_BIT_MSK       0b11111000

/*********************Register Description************************/

#define     WDTCR           *((volatile u8 *)0x41)

#define     WDTCR_WDP0      0
#define     WDTCR_WDP1      1
#define     WDTCR_WDP2      2
#define     WDTCR_WDE       3
#define     WDTCR_WDTOE     4


#endif