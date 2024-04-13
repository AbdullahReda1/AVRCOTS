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

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"


static void (*MSPI_pvSTCNotificationFunction)(void) = NULL;


void MSPI_voidMasterInit(void)
{
	SET_BIT(SPCR , SPCR_MSTR);

	CLR_BIT(SPCR , SPCR_DORD);

	CLR_BIT(SPCR , SPCR_CPOL);

	CLR_BIT(SPCR , SPCR_CPHA);

    #if (SPI_SCK_SEL == DIV_FACTOR_4 || SPI_SCK_SEL == DIV_FACTOR_16 || SPI_SCK_SEL == DIV_FACTOR_64 || SPI_SCK_SEL == DIV_FACTOR_128)
        CLR_BIT(SPSR , SPSR_SPI2X);
        SPCR &= SPI_SCK_SEL_BIT_MASK;
        SPCR |= SPI_SCK_SEL;
    #elif (SPI_SCK_SEL == DIV_FACTOR_2X_2 || SPI_SCK_SEL == DIV_FACTOR_2X_8 || SPI_SCK_SEL == DIV_FACTOR_2X_32 || SPI_SCK_SEL == DIV_FACTOR_2X_64)  
        SET_BIT(SPSR , SPSR_SPI2X);
        SPCR &= SPI_SCK_SEL_BIT_MASK;
        SPCR |= SPI_SCK_SEL;
    #else
		#error ("Error, SPI_SCK_SEL Configuration error")
	#endif

	SET_BIT(SPCR , SPCR_SPE);
}

void MSPI_voidSlaveInit(void)
{
	CLR_BIT(SPCR , SPCR_MSTR);

	CLR_BIT(SPCR , SPCR_DORD);

	CLR_BIT(SPCR , SPCR_CPOL);

	CLR_BIT(SPCR , SPCR_CPHA);

	#if (SPI_SCK_SEL == DIV_FACTOR_4 || SPI_SCK_SEL == DIV_FACTOR_16 || SPI_SCK_SEL == DIV_FACTOR_64 || SPI_SCK_SEL == DIV_FACTOR_128)
        CLR_BIT(SPSR , SPSR_SPI2X);
        SPCR &= SPI_SCK_SEL_BIT_MASK;
        SPCR |= SPI_SCK_SEL;
    #elif (SPI_SCK_SEL == DIV_FACTOR_2X_2 || SPI_SCK_SEL == DIV_FACTOR_2X_8 || SPI_SCK_SEL == DIV_FACTOR_2X_32 || SPI_SCK_SEL == DIV_FACTOR_2X_64)  
        SET_BIT(SPSR , SPSR_SPI2X);
        SPCR &= SPI_SCK_SEL_BIT_MASK;
        SPCR |= SPI_SCK_SEL;
    #else
		#error ("Error, SPI_SCK_SEL Configuration error")
	#endif

	SET_BIT(SPCR , SPCR_SPE);
}

void MSPI_voidDisableSPI(void)
{
	CLR_BIT(SPCR , SPCR_SPE);
}

u8 MSPI_u8SendReceive(u8 Copy_u8Data)
{
	SPDR = Copy_u8Data;
	while(GET_BIT(SPSR , SPSR_SPIF) == 0);
	return SPDR;
}

void MSPI_voidSendData(u8 Copy_Data)
{
	SPDR = Copy_Data;
}

void MSPI_voidReceiveData(u8 *Copy_pu8Data)
{
	if(GET_BIT(SPSR , SPSR_SPIF) == 1)
    {
		(*Copy_pu8Data) =  SPDR;
	}
}

void MSPI_voidSendString(u8 * Copy_pu8String)
{
	while((*Copy_pu8String) != 0)
	{
		MSPI_voidSendData(*Copy_pu8String);
		Copy_pu8String++;
	}
}

/********************** ISR of SPI *****************************/

void MSPI_voidSetSTCCallBack(void(*pvNotificationFunction)(void))
{
	MSPI_pvSTCNotificationFunction = pvNotificationFunction;
}
void __vector_12 (void) __attribute__((signal));
void __vector_12 (void)
{
	if ( MSPI_pvSTCNotificationFunction != NULL )
	{
		MSPI_pvSTCNotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}