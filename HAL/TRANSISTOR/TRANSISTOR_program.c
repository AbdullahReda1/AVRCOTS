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

#include "TRANSISTOR_interface.h"
#include "TRANSISTOR_private.h"
#include "TRANSISTOR_config.h"


void HTRANSISTOR_voidInit(void)
{
    MDIO_voidsetpindir(BASE_PORT_CONNECTION, BASE_PIN_CONNECTION, OUTPUT);
}

void HTRANSISTOR_voidSaturationMode(void)
{
    MDIO_voidsetpinval(BASE_PORT_CONNECTION, BASE_PIN_CONNECTION, HIGH);
}

void HTRANSISTOR_voidCutoffMode(void)
{
    MDIO_voidsetpinval(BASE_PORT_CONNECTION, BASE_PIN_CONNECTION, LOW);
}