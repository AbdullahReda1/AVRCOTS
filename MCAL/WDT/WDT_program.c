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


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "WDT_interface.h"
#include "WDT_private.h"
#include "WDT_config.h"

void MWDT_voidEnable(void)
{
    SET_BIT(WDTCR, WDTCR_WDE);
}

void MWDT_voidSleep(u8 Copy_u8TimeOut)
{
    WDTCR &= WDT_SLEEP_BIT_MSK;
    WDTCR |= Copy_u8TimeOut;
}

void MWDT_voidDisable(void)
{
   WDTCR = ((1 << WDTCR_WDTOE) | (1 << WDTCR_WDE));
   WDTCR = 0;
}