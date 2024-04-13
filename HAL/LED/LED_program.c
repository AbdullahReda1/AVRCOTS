/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    28 MAR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          28 MAR, 2023     Abdullah R.Hebashi       Initial Creation    
***********************************************************/


#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"


void HLED_voidInit(LED_t* Ledobj)
{
	MDIO_voidsetpindir(Ledobj->LED_PORT , Ledobj->LED_PIN , OUTPUT);
}

void HLED_voidTurnOn(LED_t* Ledobj)
{
	MDIO_voidsetpinval(Ledobj->LED_PORT , Ledobj->LED_PIN , HIGH);
}

void HLED_voidTurnOff(LED_t* Ledobj)
{
	MDIO_voidsetpinval(Ledobj->LED_PORT , Ledobj->LED_PIN , LOW);
}

void HLED_voidToggle(LED_t* Ledobj)
{
	MDIO_voidTogPin(Ledobj->LED_PORT , Ledobj->LED_PIN);
}
