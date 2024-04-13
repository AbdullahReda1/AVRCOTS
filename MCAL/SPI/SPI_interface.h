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


#ifndef 	MCAL_SPI_SPI_interface_H_
#define 	MCAL_SPI_SPI_interface_H_


void MSPI_voidMasterInit(void);
void MSPI_voidSlaveInit(void);

void MSPI_voidDisableSPI(void);

u8 MSPI_u8SendReceive(u8 Copy_u8Data);

void MSPI_voidSendData(u8 Copy_Data);
void MSPI_voidReceiveData(u8 *pdata);
void MSPI_voidSendString(u8 * Copy_pu8String);

void MSPI_voidSetSTCCallBack(void(*pvNotificationFunction)(void));


#endif