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


#ifndef MCAL_TWI_TWI_INTERFACE_H
#define MCAL_TWI_TWI_INTERFACE_H


typedef enum
{
	NoError,
	StartConditionError,
	RepeatedStartConditionError,
	SlaveAddressWithWriteRequestError,
	SlaveAddressWithReadRequestError,
	SendDataPacketError,
	MasterReadDataPacketError,
}ERR_t;


void MTWI_voidMasterInit(u8 Copy_u8SlaveAddress);
void MTWI_voidSlaveInit(u8 Copy_u8SlaveAddress);

ERR_t MTWI_ERRSendStartCondition(void);
ERR_t MTWI_ERRSendRepeatedStartCondition(void);
ERR_t MTWI_ERRSendDataPacket(u8 Copy_u8DataPacket);
ERR_t MTWI_ERRReceiveDataPacket(u8 *Copy_pu8DataPacket);
ERR_t MTWI_ERRSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);

void MTWI_voidSendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);
void MTWI_voidSendStopCondition(void);


#endif