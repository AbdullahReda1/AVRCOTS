/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    30 MAR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          30 MAR, 2023     Abdullah R.Hebashi       Initial Creation 
*	v2.0			 05 APR, 2023 	  Abdullah R.Hebashi		  Adding ADC ISR
***********************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"


volatile u16 ADC_u16DigitalResult = 0;
static void (*ADC_pvoidNotifiFunction) (void) = NULL;

void MADC_voidInit(void)
{
    /* ADC Enable */
    #if ADC_ENABLE == ENABLE
        SET_BIT(ADCSRA, ADCSRA_ADEN);
    #elif ADC_ENABLE == DISABLE
        CLR_BIT(ADCSRA, ADCSRA_ADEN);
    #else
        #error("Error, ADC_ENABLE Configuration error")
    #endif
    
    
    /* ADC Interrupt Enable */
        /* Pre Build */
    #if ADC_INTERRUPT_STATUS == ENABLE
        SET_BIT(ADCSRA, ADCSRA_ADIE);
    #elif ADC_INTERRUPT_STATUS == DISABLE
        CLR_BIT(ADCSRA, ADCSRA_ADIE);
    #else
        #error("Error, ADC_INTERRUPT_STATUS Configuration error")
    #endif

    
    /* Reference voltage choose */
    /*
    #if ADC_Reference_SECTION == AREF
        CLR_BIT(ADMUX, ADMUX_REFS0);
        CLR_BIT(ADMUX, ADMUX_REFS1);
    #elif ADC_Reference_SECTION == AVCC
        SET_BIT(ADMUX, ADMUX_REFS0);
        CLR_BIT(ADMUX, ADMUX_REFS1);
    #elif ADC_Reference_SECTION == INTERNAL_2v56
        SET_BIT(ADMUX, ADMUX_REFS0);
        SET_BIT(ADMUX, ADMUX_REFS1);    
    #else
        #error("Error, ADC_Reference_SECTION Configuration error")
    #endif
    */

    /* Reference voltage choose by bit masking */
    ADMUX &= REF_SEL_BIT_MASK;
    ADMUX |= ADC_Reference_SELCTION;

    /* Adjust Result */
    #if ADC_ADJUST_RESULT == RIGHT_ADJUST
        CLR_BIT(ADMUX, ADMUX_ADLAR);
    #elif ADC_ADJUST_RESULT == LEFT_ADJUST
        SET_BIT(ADMUX, ADMUX_ADLAR);
    #else
        #error("Error, ADC_ADJUST_RESULT Configuration error")
    #endif

    /* Pre-Scaler by bit mask */
    ADCSRA &= PRE_SCALER_BIT_MASK;
    ADCSRA |= ADC_PRESCALER;
}


void MADC_voidInterruptControl(u8 Copy_u8InterruptStatus)
{
    /*Post Build*/
    switch (Copy_u8InterruptStatus)
    {
    case ADC_INTERRUPT_DISABLE:
        CLR_BIT(ADCSRA, ADCSRA_ADIE);
        break;
    case ADC_INTERRUPT_ENABLE:
        SET_BIT(ADCSRA, ADCSRA_ADIE);
        break;
    default:
        /* Do Nothing */
        break;
    }
}

u8 MADC_u8StartConversionSynchronous(u8 Copy_u8ChannelNumber)   // polling mechanism.
{
    /* Set Channel */
    ADMUX &= CHANNEL_SELECTION_MASK;
    ADMUX |= Copy_u8ChannelNumber;

    /* ADC start convertion */
    SET_BIT(ADCSRA, ADCSRA_ADSC);

    /* Polling (Busy wait) till the flag is raised */
    while (GET_BIT(ADCSRA, ADCSRA_ADIF) == FALSE);

    /* Clear flag */
    SET_BIT(ADCSRA, ADCSRA_ADIF);

    /* Return value */
    u8 Local_u8DigitalValue;
    #if ADC_ADJUST_RESULT == LEFT_ADJUST
    Local_u8DigitalValue = ADCH;
    #elif ADC_ADJUST_RESULT == RIGHT_ADJUST
    Local_u8DigitalValue = ADCL;
    #endif

    return Local_u8DigitalValue;
}

u8 MADC_u8StartConversionAsynchronous(u8 Copy_u8ChannelNumber, void (*NotificationFunction)(void))
{
    /* Set Channel */
    ADMUX &= CHANNEL_SELECTION_MASK;
    ADMUX |= Copy_u8ChannelNumber;

    /*Set Callback Function in the global Ptr to Function*/
    MADC_voidADCSetCallback(NotificationFunction);

    /* ADC start convertion */
    SET_BIT(ADCSRA, ADCSRA_ADSC);
}


/********** ISR of ADC ************/

void MADC_voidADCSetCallback(void (*NotificationFunction)(void))
{
	ADC_pvoidNotifiFunction = NotificationFunction;
}

void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
    MADC_voidInterruptControl(DISABLE);
    ADC_u16DigitalResult = ADCH;
	if ( ADC_pvoidNotifiFunction != NULL )
	{
		ADC_pvoidNotifiFunction();
	}
	else
	{
		/* Do Nothing */
	}
    MADC_voidInterruptControl(ENABLE);
}