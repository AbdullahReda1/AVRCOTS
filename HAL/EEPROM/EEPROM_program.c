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


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/TWI/TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_config.h"
#include "EEPROM_private.h"

void HEEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8Data)
{
    u8 Local_u8SlaveAddress = ((u8)(Copy_u16LocationAddress >> 8)) | (A2_CONNECTION << 2) | CONTROL_CHIP_SELECT_CODE;
    MTWI_ERRSendStartCondition();
    MTWI_ERRSendSlaveAddressWithWrite(Local_u8SlaveAddress);
    MTWI_ERRSendDataPacket((u8)Copy_u16LocationAddress);
    MTWI_ERRSendDataPacket(Copy_u8Data);
    MTWI_voidSendStopCondition();
    _delay_ms(5);
}

void HEEPROM_voidReceiveDataByte(u16 Copy_u16LocationAddress, u8 * Copy_pu8ReceivedData)
{
    u8 Local_u8SlaveAddress = CONTROL_CHIP_SELECT_CODE | (A2_CONNECTION << 2) | (u8)(Copy_u16LocationAddress >> 8);
    MTWI_ERRSendStartCondition();
    MTWI_ERRSendSlaveAddressWithWrite(Local_u8SlaveAddress);
    MTWI_ERRSendDataPacket((u8)Copy_u16LocationAddress);
    MTWI_ERRSendRepeatedStartCondition();
    MTWI_voidSendSlaveAddressWithRead(Local_u8SlaveAddress);
    MTWI_ERRReceiveDataPacket(Copy_pu8ReceivedData);
    MTWI_voidSendStopCondition();
}