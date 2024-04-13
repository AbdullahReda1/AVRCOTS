/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    17 APR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          17 APR, 2023     Abdullah R.Hebashi       Initial Creation
***********************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"


static void (*MUART_pvTXCNotificationFunction)(void) = NULL;
static void (*MUART_pvUDRENotificationFunction)(void) = NULL;
static void (*MUART_pvRXCNotificationFunction)(void) = NULL;


void MUART_voidInit(void)
{
    u8 Local_u8UCSRCTemp = FREE_REG;

    CLR_BIT(Local_u8UCSRCTemp, UCSRC_UMSEL);

    SET_BIT(UCSRB, UCSRB_TXEN);
    SET_BIT(UCSRB, UCSRB_RXEN);

    SET_BIT(Local_u8UCSRCTemp, UCSRC_UCSZ0);
    SET_BIT(Local_u8UCSRCTemp, UCSRC_UCSZ1);
    CLR_BIT(UCSRB, UCSRB_UCSZ2);

    CLR_BIT(Local_u8UCSRCTemp, UCSRC_UPM0);
    CLR_BIT(Local_u8UCSRCTemp, UCSRC_UPM1);
    
    CLR_BIT(Local_u8UCSRCTemp, UCSRC_USBS);

    SET_BIT(Local_u8UCSRCTemp, UCSRC_URSEL);

    UCSRC = Local_u8UCSRCTemp;

    CLR_BIT(UCSRA, UCSRA_U2X);
    UBRRL = VALUE_GET_BAUDRATE;

    CLR_BIT(UBRRH, UBRRH_URSEL);
    UBRRH = FREE_REG;
}

void MUART_voidTransmitDataAsynchronous(u8 Copy_u8Data)
{
    while(GET_BIT(UCSRA, UCSRA_UDRE) == 0);
    UDR = Copy_u8Data;
    while(GET_BIT(UCSRA, UCSRA_TXC) == 0);
    SET_BIT(UCSRA, UCSRA_TXC);
}

void MUART_voidReceiveDataAsynchronous(u8 * Copy_pu8ReceivedData)
{
    while(GET_BIT(UCSRA, UCSRA_RXC) == 0);
    (*Copy_pu8ReceivedData) = UDR;
}

void MUART_voidSendString(u8 * Copy_pu8String)
{
	while((*Copy_pu8String) != 0)
	{
		MUART_voidTransmitDataAsynchronous(*Copy_pu8String);
		Copy_pu8String++;
	}
}

/********************** ISR of USART *****************************/

			/******TXC ISR*******/
void MUART_voidSetTXCCallBack(void(*pvNotificationFunction)(void))
{
	MUART_pvTXCNotificationFunction = pvNotificationFunction;
}
void __vector_15 (void) __attribute__((signal));
void __vector_15 (void)
{
	if ( MUART_pvTXCNotificationFunction != NULL )
	{
		MUART_pvTXCNotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}

			/******UDRE ISR*******/
void MUART_voidSetUDRECallBack(void(*pvNotificationFunction)(void))
{
	MUART_pvUDRENotificationFunction = pvNotificationFunction;
}
void __vector_14 (void) __attribute__((signal));
void __vector_14 (void)
{
	if ( MUART_pvUDRENotificationFunction != NULL )
	{
		MUART_pvUDRENotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}

			/******RXC ISR*******/
void MUART_voidSetRXCCallBack(void(*pvNotificationFunction)(void))
{
	MUART_pvRXCNotificationFunction = pvNotificationFunction;
}
void __vector_13 (void) __attribute__((signal));
void __vector_13 (void)
{
	if ( MUART_pvRXCNotificationFunction != NULL )
	{
		MUART_pvRXCNotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}