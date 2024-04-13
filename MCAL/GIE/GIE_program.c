/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    29 MAR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                      
 * v1.0          29 MAR, 2023     Abdullah R.Hebashi           
***********************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "GIE_interface.h"
#include "GIE_config.h"
#include "GIE_private.h"


void MGIE_voidEnableGlobalInterrupt(void)
{
	SET_BIT(SREG, I_BIT);
}

void MGIE_voidDisableGlobalInterrupt(void)
{
	CLR_BIT(SREG, I_BIT);
}