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


#ifndef 	MCAL_UART_UART_interface_H_
#define 	MCAL_UART_UART_interface_H_


void MUART_voidInit(void);


void MUART_voidTransmitDataAsynchronous(u8 Copy_u8Data);

void MUART_voidReceiveDataAsynchronous(u8 * Copy_pu8ReceivedData);

void MUART_voidSendString(u8 * Copy_pu8String);


void MUART_voidSetTXCCallBack(void(*pvNotificationFunction)(void));

void MUART_voidSetUDRECallBack(void(*pvNotificationFunction)(void));

void MUART_voidSetRXCCallBack(void(*pvNotificationFunction)(void));


#endif