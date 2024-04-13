/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    29 MAR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0         29 MAR, 2023     Abdullah R.Hebashi        Initial Creation    
 * v2.0         30 MAR, 2023     Abdullah R.Hebashi        Adding ISR function    
***********************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../DIO/DIO_interface.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"


static void (*EXTI_pvoidINT0NotifiFunction) (void) = NULL;
static void (*EXTI_pvoidINT1NotifiFunction) (void) = NULL;
static void (*EXTI_pvoidINT2NotifiFunction) (void) = NULL;


void MEXTI_voidInit(u8 Copy_u8IntNum)
{
	switch (Copy_u8IntNum)
	{
	case EXTI_INT0:
		#if 	INT0_PIN_CONNECTION == INT0_INPUT_PULLUP
				MDIO_voidsetpindir(EXTI0_PORT, EXTI0_PIN, INPUT);
				MDIO_voidsetpinval(EXTI0_PORT, EXTI0_PIN, HIGH);
		#elif 	INT0_PIN_CONNECTION == INT0_INPUT_EXTERNAL_PULLUP
				MDIO_voidsetpindir(EXTI0_PORT, EXTI0_PIN, INPUT);
		#elif 	INT0_PIN_CONNECTION == INT0_INPUT_EXTERNAL_PULLDOWN
				MDIO_voidsetpindir(EXTI0_PORT, EXTI0_PIN, INPUT);
		#else
				#error ("Error INT0_PIN_CONNECTION, Configuration error")
		#endif
		break;
	case EXTI_INT1:
		#if 	INT1_PIN_CONNECTION == INT1_INPUT_PULLUP
				MDIO_voidsetpindir(EXTI1_PORT, EXTI1_PIN, INPUT);
				MDIO_voidsetpinval(EXTI1_PORT, EXTI1_PIN, HIGH);
		#elif 	INT1_PIN_CONNECTION == INT1_INPUT_EXTERNAL_PULLUP
				MDIO_voidsetpindir(EXTI1_PORT, EXTI1_PIN, INPUT);
		#elif 	INT1_PIN_CONNECTION == INT1_INPUT_EXTERNAL_PULLDOWN
				MDIO_voidsetpindir(EXTI1_PORT, EXTI1_PIN, INPUT);
		#else
				#error ("Error INT1_PIN_CONNECTION, Configuration error")
		#endif
		break;
	case EXTI_INT2:
		#if 	INT2_PIN_CONNECTION == INT2_INPUT_PULLUP
				MDIO_voidsetpindir(EXTI2_PORT, EXTI2_PIN, INPUT);
				MDIO_voidsetpinval(EXTI2_PORT, EXTI2_PIN, HIGH);
		#elif 	INT2_PIN_CONNECTION == INT2_INPUT_EXTERNAL_PULLUP
				MDIO_voidsetpindir(EXTI2_PORT, EXTI2_PIN, INPUT);
		#elif 	INT2_PIN_CONNECTION == INT2_INPUT_EXTERNAL_PULLDOWN
				MDIO_voidsetpindir(EXTI2_PORT, EXTI2_PIN, INPUT);
		#else
				#error ("Error INT2_PIN_CONNECTION, Configuration error")
		#endif
		break;
	default:
		/* Do Nothing */
		break;
	}
}

void MEXTI_voidEnable(u8 Copy_u8IntNum)
{
	switch (Copy_u8IntNum)
	{
	case EXTI_INT0:
		SET_BIT(GICR, GICR_INT0);
		break;
	case EXTI_INT1:
		SET_BIT(GICR, GICR_INT1);
		break;
	case EXTI_INT2:
		SET_BIT(GICR, GICR_INT2);
		break;
	default:
		/* Do Nothing */
		break;
	}
}

void MEXTI_voidDisable(u8 Copy_u8IntNum)
{
	switch (Copy_u8IntNum)
	{
	case EXTI_INT0:
		CLR_BIT(GICR, GICR_INT0);
		break;
	case EXTI_INT1:
		CLR_BIT(GICR, GICR_INT1);
		break;
	case EXTI_INT2:
		CLR_BIT(GICR, GICR_INT2);
		break;
	default:
		/* Do Nothing */
		break;
	}
}

void MEXTI_voidTriggerEdge(u8 Copy_u8IntNum, u8 Copy_u8Edge)
{
	switch (Copy_u8IntNum)
	{
	case EXTI_INT0:
		switch (Copy_u8Edge)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR, MCUCR_ISC00);
			CLR_BIT(MCUCR, MCUCR_ISC01);
			break;
		case ANY_LOGICAL_CHANGE:
			SET_BIT(MCUCR, MCUCR_ISC00);
			CLR_BIT(MCUCR, MCUCR_ISC01);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR, MCUCR_ISC00);
			SET_BIT(MCUCR, MCUCR_ISC01);
			break;
		case RISINGING_EDGE:
			SET_BIT(MCUCR, MCUCR_ISC00);
			SET_BIT(MCUCR, MCUCR_ISC01);
			break;		
		default:
			/* Do Nothing */
			break;
		}
		break;
	case EXTI_INT1:
		switch (Copy_u8Edge)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR, MCUCR_ISC10);
			CLR_BIT(MCUCR, MCUCR_ISC11);
			break;
		case ANY_LOGICAL_CHANGE:
			SET_BIT(MCUCR, MCUCR_ISC10);
			CLR_BIT(MCUCR, MCUCR_ISC11);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR, MCUCR_ISC10);
			SET_BIT(MCUCR, MCUCR_ISC11);
			break;
		case RISINGING_EDGE:
			SET_BIT(MCUCR, MCUCR_ISC10);
			SET_BIT(MCUCR, MCUCR_ISC11);
			break;		
		default:
			/* Do Nothing */
			break;
		}
		break;
	case EXTI_INT2:
		switch (Copy_u8Edge)
		{
		case FALLING_EDGE:
			CLR_BIT(MCUCSR, MCUCSR_ISC2);
			break;
		case RISINGING_EDGE:
			SET_BIT(MCUCSR, MCUCSR_ISC2);
			break;		
		default:
			/* Do Nothing */
			break;
		}
		break;
	default:
		/* Do Nothing */
		break;
	}
}


/************** ISR for INT0 *****************/

void MEXTI_voidINT0SetCallback(void (*NotificationFunction)(void))
{
	EXTI_pvoidINT0NotifiFunction = NotificationFunction;
}

void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if ( EXTI_pvoidINT0NotifiFunction != NULL )
	{
		EXTI_pvoidINT0NotifiFunction();
	}
	else
	{
		/* Do Nothing */
	}
}

/************** ISR for INT1 *****************/

void MEXTI_voidINT1SetCallback(void (*NotificationFunction)(void))
{
	EXTI_pvoidINT1NotifiFunction = NotificationFunction;
}

void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	if ( EXTI_pvoidINT1NotifiFunction != NULL )
	{
		EXTI_pvoidINT1NotifiFunction();
	}
	else
	{
		/* Do Nothing */
	}
}

/************** ISR for INT2 *****************/

void MEXTI_voidINT2SetCallback(void (*NotificationFunction)(void))
{
	EXTI_pvoidINT2NotifiFunction = NotificationFunction;
}

void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	if ( EXTI_pvoidINT2NotifiFunction != NULL )
	{
		EXTI_pvoidINT2NotifiFunction();
	}
	else
	{
		/* Do Nothing */
	}
}