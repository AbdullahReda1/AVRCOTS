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


#ifndef MCAL_WDT_WDT_INTERFACE_H
#define MCAL_WDT_WDT_INTERFACE_H


/* Typical Time-out at VCC = 5.0V */
#define WDT_SLEEP_16_3_MS       0b000
#define WDT_SLEEP_32_5_MS       0b001
#define WDT_SLEEP_65_0_MS       0b010
#define WDT_SLEEP_00_13_S       0b011
#define WDT_SLEEP_00_26_S       0b100
#define WDT_SLEEP_00_52_S       0b101
#define WDT_SLEEP_01_00_S       0b110
#define WDT_SLEEP_02_10_S       0b111

/* Typical Time-out at VCC = 3.0V */
#define WDT_SLEEP_17_1_MS       0b000
#define WDT_SLEEP_34_3_MS       0b001
#define WDT_SLEEP_68_5_MS       0b010
#define WDT_SLEEP_00_14_S       0b011
#define WDT_SLEEP_00_27_S       0b100
#define WDT_SLEEP_00_55_S       0b101
#define WDT_SLEEP_01_10_S       0b110
#define WDT_SLEEP_02_20_S       0b111


void MWDT_voidEnable(void);
void MWDT_voidSleep(u8 Copy_u8TimeOut);
void MWDT_voidDisable(void);


#endif