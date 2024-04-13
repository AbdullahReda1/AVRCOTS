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

#include "HBRIDGE_interface.h"
#include "HBRIDGE_private.h"
#include "HBRIDGE_config.h"


void HHBRIDGE_voidInit(void)
{
    MDIO_voidsetpindir(CONNECTION_A_PORT, CONNECTION_A_PIN, OUTPUT);
    MDIO_voidsetpindir(CONNECTION_B_PORT, CONNECTION_B_PIN, OUTPUT);
}

void HHBRIDGE_voidForward(void)
{
    MDIO_voidsetpinval(CONNECTION_A_PORT, CONNECTION_A_PIN, HIGH);
    MDIO_voidsetpinval(CONNECTION_B_PORT, CONNECTION_B_PIN, LOW);
}

void HHBRIDGE_voidBackward(void)
{
    MDIO_voidsetpinval(CONNECTION_A_PORT, CONNECTION_A_PIN, LOW);
    MDIO_voidsetpinval(CONNECTION_B_PORT, CONNECTION_B_PIN, HIGH);
}

void HHBRIDGE_voidStop(void)
{
    MDIO_voidsetpinval(CONNECTION_A_PORT, CONNECTION_A_PIN, LOW);
    MDIO_voidsetpinval(CONNECTION_B_PORT, CONNECTION_B_PIN, LOW);
}