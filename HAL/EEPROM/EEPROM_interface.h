/*********************************************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:        19 APR, 2023
 * Version:              v1.0
 * Compiler:             GNU GCC
*********************************************************************************/
/*********************************************************************************
 * Version      Date              Author                        Description
 * v1.0         19 APR, 2023      Abdullah R.Hebashi            Initial Creation 
*********************************************************************************/


#ifndef HAL_EEPROM_EEPROM_INTERFACE_H
#define HAL_EEPROM_EEPROM_INTERFACE_H


void HEEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8Data);

void HEEPROM_voidReceiveDataByte(u16 Copy_u16LocationAddress, u8 * Copy_pu8ReceivedData);


#endif