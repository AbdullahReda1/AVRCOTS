/********************************************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:        29 APR, 2023
 * Version:              v1.0
 * Compiler:             GNU GCC
********************************************************************************/
/********************************************************************************
 * Version      Date                  Author                   Description
 * v1.0         29 APR, 2023          Abdullah R.Hebashi       Initial Creation    
********************************************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "RELAY_interface.h"
#include "RELAY_private.h"
#include "RELAY_config.h"


void HRELAY_voidInit(void)
{
    MDIO_voidsetpindir(Relay_PORT_CONNECTION, RELAY_PIN_CONNECTION, OUTPUT);
}

void HRELAY_voidOpen(void)
{
    MDIO_voidsetpinval(Relay_PORT_CONNECTION, RELAY_PIN_CONNECTION, HIGH);
}

void HRELAY_voidClose(void)
{
    MDIO_voidsetpinval(Relay_PORT_CONNECTION, RELAY_PIN_CONNECTION, LOW);
}