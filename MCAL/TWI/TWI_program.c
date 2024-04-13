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


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_config.h"


void MTWI_voidMasterInit(u8 Copy_u8SlaveAddress)
{
	SET_BIT(TWCR, TWCR_TWEA);
	if (Copy_u8SlaveAddress != 0x00)
	{
		TWAR = Copy_u8SlaveAddress << 1;
	}
	else
	{
		TWAR = 0x00 << 1;
	}
	CLR_BIT(TWSR, TWSR_TWPS0);
	CLR_BIT(TWSR, TWSR_TWPS1);
	TWBR = 2;
	SET_BIT(TWCR, TWCR_TWEN);
}

void MTWI_voidSlaveInit(u8 Copy_u8SlaveAddress)
{
	SET_BIT(TWCR, TWCR_TWEA);
	TWAR = Copy_u8SlaveAddress << 1;
	SET_BIT(TWCR, TWCR_TWEN);
}

ERR_t MTWI_ERRSendStartCondition(void)
{
	ERR_t Error_Status = NoError;
	SET_BIT(TWCR, TWCR_TWSTA);
	SET_BIT(TWCR, TWCR_TWINT);
	while (GET_BIT(TWCR, TWCR_TWINT) == 0);
	if ((TWSR & STATUS_BIT_MASK) != START_ACK)
	{
		Error_Status = StartConditionError;
	}
	return Error_Status;
}

ERR_t MTWI_ERRSendRepeatedStartCondition(void)
{
	ERR_t Error_Status = NoError;
	SET_BIT(TWCR, TWCR_TWSTA);
	SET_BIT(TWCR, TWCR_TWINT);
	while (GET_BIT(TWCR, TWCR_TWINT) == 0);
	if ((TWSR & STATUS_BIT_MASK) != REP_START_ACK)
	{
		Error_Status = RepeatedStartConditionError;
	}
	return Error_Status;
}

ERR_t MTWI_ERRSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	ERR_t Error_Status = NoError;
	TWDR = Copy_u8SlaveAddress << 1;
	CLR_BIT(TWDR, TWDR_TWD0);
	CLR_BIT(TWCR, TWCR_TWSTA);
	SET_BIT(TWCR, TWCR_TWINT);
	while (GET_BIT(TWCR, TWCR_TWINT) == 0);
	if ((TWSR & STATUS_BIT_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Error_Status = SlaveAddressWithWriteRequestError;
	}
	return Error_Status;
}

void MTWI_voidSendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	ERR_t Error_Status = NoError;
	TWDR = Copy_u8SlaveAddress << 1;
	SET_BIT(TWDR, TWDR_TWD0);
	CLR_BIT(TWCR, TWCR_TWSTA);
	SET_BIT(TWCR, TWCR_TWINT);
	while (GET_BIT(TWCR, TWCR_TWINT) == 0);
	if ((TWSR & STATUS_BIT_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Error_Status = SlaveAddressWithReadRequestError;
	}
	return Error_Status;
}

ERR_t MTWI_ERRSendDataPacket(u8 Copy_u8DataPacket)
{
	ERR_t Error_Status = NoError;
	TWDR = Copy_u8DataPacket;
	SET_BIT(TWCR, TWCR_TWINT);
	while (GET_BIT(TWCR, TWCR_TWINT) == 0);
	if ((TWSR & STATUS_BIT_MASK) != MSTR_WR_BYTE_ACK)
	{
		Error_Status = SendDataPacketError;
	}
	return Error_Status;
}

ERR_t MTWI_ERRReceiveDataPacket(u8 *Copy_pu8DataPacket)
{
	ERR_t Error_Status = NoError;
	SET_BIT(TWCR, TWCR_TWINT);
	while (GET_BIT(TWCR, TWCR_TWINT) == 0);
	if ((TWSR & STATUS_BIT_MASK) != MSTR_RD_BYTE_WITH_ACK)
	{
		Error_Status = MasterReadDataPacketError;
	}
	else
	{
		*Copy_pu8DataPacket = TWDR;
	}
	return Error_Status;
}

void MTWI_voidSendStopCondition(void)
{
	SET_BIT(TWCR, TWCR_TWSTO);
	SET_BIT(TWCR, TWCR_TWINT);
}