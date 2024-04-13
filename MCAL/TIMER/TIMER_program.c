/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    9 APR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          9 APR, 2023       Abdullah R.Hebashi       Initial Creation 
***********************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"


static void (*TIMER0_pvOVFNotificationFunction)(void) = NULL;
static void (*TIMER0_pvOCNotificationFunction)(void) = NULL;

static void (*TIMER1_pvOVFNotificationFunction)(void) = NULL;
static void (*TIMER1_pvOC1ANotificationFunction)(void) = NULL;
static void (*TIMER1_pvOC1BNotificationFunction)(void) = NULL;
static void (*TIMER1_pvICUNotificationFunction)(void) = NULL;

static void (*TIMER2_pvOVFNotificationFunction)(void) = NULL;
static void (*TIMER2_pvOCNotificationFunction)(void) = NULL;


/************************* TIMER0 *****************************/

void MTIMER0_voidInit(void)
{
	/* Set Mode for timer0 */
	TCCR0 &= TIMER0_MODE_SEL_BIT_MASK;
    TCCR0 |= TIMER0_MODE_SEL;

	/*Set compare output mode*/
	TCCR0 &= TIMER0_OC0_MODE_BIT_MASK;
    TCCR0 |= TIMER0_OUTPUT_COMPARE_SEL;

	/*#if TIMER0_MODE_SEL == TIMER0_NORMAL_MODE
		#if TIMER0_OUTPUT_COMPARE_SEL == NORMAL_OC0_DISCONNECTED
			CLR_BIT(TCCR0, TCCR0_COM00);
			CLR_BIT(TCCR0, TCCR0_COM01);
		#elif TIMER0_OUTPUT_COMPARE_SEL == TOG_OC0_ON_COMPARE_MATCH
			SET_BIT(TCCR0, TCCR0_COM00);
			CLR_BIT(TCCR0, TCCR0_COM01);
		#elif TIMER0_OUTPUT_COMPARE_SEL == CLR_OC0_ON_COMPARE_MATCH
			CLR_BIT(TCCR0, TCCR0_COM00);
			SET_BIT(TCCR0, TCCR0_COM01);
		#elif TIMER0_OUTPUT_COMPARE_SEL == SET_OC0_ON_COMPARE_MATCH
			SET_BIT(TCCR0, TCCR0_COM00);
			SET_BIT(TCCR0, TCCR0_COM01);
		#else
			#error("Error, TIMER0_OUTPUT_COMPARE_SEL Configuration error")
		#endif
	#elif TIMER0_MODE_SEL == TIMER0_CTC_MODE
		#if TIMER0_OUTPUT_COMPARE_SEL == NORMAL_OC0_DISCONNECTED
			CLR_BIT(TCCR0, TCCR0_COM00);
			CLR_BIT(TCCR0, TCCR0_COM01);
		#elif TIMER0_OUTPUT_COMPARE_SEL == TOG_OC0_ON_COMPARE_MATCH
			SET_BIT(TCCR0, TCCR0_COM00);
			CLR_BIT(TCCR0, TCCR0_COM01);
		#elif TIMER0_OUTPUT_COMPARE_SEL == CLR_OC0_ON_COMPARE_MATCH
			CLR_BIT(TCCR0, TCCR0_COM00);
			SET_BIT(TCCR0, TCCR0_COM01);
		#elif TIMER0_OUTPUT_COMPARE_SEL == SET_OC0_ON_COMPARE_MATCH
			SET_BIT(TCCR0, TCCR0_COM00);
			SET_BIT(TCCR0, TCCR0_COM01);
		#else
			#error("Error, TIMER0_OUTPUT_COMPARE_SEL Configuration error")
		#endif
	#elif TIMER0_MODE_SEL == TIMER0_FAST_PWM_MODE
		#if TIMER0_OUTPUT_COMPARE_SEL == NORMAL_OC0_DISCONNECTED
			CLR_BIT(TCCR0, TCCR0_COM00);
			CLR_BIT(TCCR0, TCCR0_COM01);
		#elif TIMER0_OUTPUT_COMPARE_SEL == CLR_OC0_ON_COMPARE_MATCH
			CLR_BIT(TCCR0, TCCR0_COM00);
			SET_BIT(TCCR0, TCCR0_COM01);
		#elif TIMER0_OUTPUT_COMPARE_SEL == SET_OC0_ON_COMPARE_MATCH
			SET_BIT(TCCR0, TCCR0_COM00);
			SET_BIT(TCCR0, TCCR0_COM01);
		#else
			#error("Error, TIMER0_OUTPUT_COMPARE_SEL Configuration error")
		#endif
	#elif TIMER0_MODE_SEL == TIMER0_PHASE_CORRECT_PWM_MODE
		#if TIMER0_OUTPUT_COMPARE_SEL == NORMAL_OC0_DISCONNECTED
			CLR_BIT(TCCR0, TCCR0_COM00);
			CLR_BIT(TCCR0, TCCR0_COM01);
		#elif TIMER0_OUTPUT_COMPARE_SEL == CLR_OC0_ON_COMPARE_MATCH
			CLR_BIT(TCCR0, TCCR0_COM00);
			SET_BIT(TCCR0, TCCR0_COM01);
		#elif TIMER0_OUTPUT_COMPARE_SEL == SET_OC0_ON_COMPARE_MATCH
			SET_BIT(TCCR0, TCCR0_COM00);
			SET_BIT(TCCR0, TCCR0_COM01);
		#else
			#error("Error, TIMER0_OUTPUT_COMPARE_SEL Configuration error")
		#endif
	#else
		#error("Error, TIMER0_MODE_SEL Configuration error")
	#endif*/

	/*Set The Prescaler*/
	TCCR0 &= TIMER0_CLK_SEL_BIT_MASK;
    TCCR0 |= TIMER0_CLK_SEL;
}

void MTIMER0_voidDisableTimer0(void)
{
	CLR_BIT(TCCR0, TCCR0_COM00);
	CLR_BIT(TCCR0, TCCR0_COM01);	
}

void MTIMER0_voidEnableTimer0(void)
{
	/* Set Mode for timer0 */
	TCCR0 &= TIMER0_MODE_SEL_BIT_MASK;
	TCCR0 |= TIMER0_MODE_SEL;
	
	/*Set compare output mode*/
	TCCR0 &= TIMER0_OC0_MODE_BIT_MASK;
	TCCR0 |= TIMER0_OUTPUT_COMPARE_SEL;
	
	/*Set The Prescaler*/
	TCCR0 &= TIMER0_CLK_SEL_BIT_MASK;
	TCCR0 |= TIMER0_CLK_SEL;
}

void MTIMER0_voidSetPreloadValue(u8 Copy_u8Value)
{
	TCNT0 = Copy_u8Value;
}

void MTIMER0_voidSetOCMatchValue(u8 Copy_u8Value)
{
	OCR0 = Copy_u8Value;
}

void MTIMER0_voidEnableInterrupt(u8 Copy_u8Mode)
{
	if(Copy_u8Mode == TIMER0_OVF)
	{
		SET_BIT(TIMSK,TIMSK_TOIE0);
	}
	else if(Copy_u8Mode == TIMER0_COMP)
	{
		SET_BIT(TIMSK,TIMSK_OCIE0);
	}
}

void MTIMER0_voidDisableInterrupt(u8 Copy_u8Mode)
{
	if(Copy_u8Mode == TIMER0_OVF)
	{
		CLR_BIT(TIMSK,TIMSK_TOIE0);
	}
	else if(Copy_u8Mode == TIMER0_COMP)
	{
		CLR_BIT(TIMSK,TIMSK_OCIE0);
	}
}

void MTIMER0_voidSetBusyWait_OVFMode(u32 Copy_u32Time)
{
	/*Set The Prescaler to be 8*/
	TCCR0 &= TIMER0_CLK_SEL_BIT_MASK;
    TCCR0 |= TIMER0_CLK_SEL;

	MTIMER0_voidSetPreloadValue(6);
	u32 Number_of_OVF = ((u32)Copy_u32Time * 1000UL) / 250UL;

	u32 Local_u32Counter = 0;

	while(Local_u32Counter < Number_of_OVF)
	{
		while(GET_BIT(TIFR , TIFR_TOV0) == 0);
		SET_BIT(TIFR , TIFR_TOV0);
		Local_u32Counter++;
		MTIMER0_voidSetPreloadValue(6);
	}
}

void MTIMER0_voidSetBusyWait_OCMode(u32 Copy_u32Time)
{
	/*Set The Prescaler to be 8*/
	TCCR0 &= TIMER0_CLK_SEL_BIT_MASK;
    TCCR0 |= TIMER0_CLK_SEL;

	MTIMER0_voidSetOCMatchValue(250);
	u32 Number_Of_OCF = ((u32)Copy_u32Time * 1000UL) / 250UL;

	u32 Local_u32Counter = 0;

	while(Local_u32Counter <= Number_Of_OCF)
	{
		while(GET_BIT(TIFR , TIFR_OCF0) == 0);
		SET_BIT(TIFR , TIFR_OCF0);
		Local_u32Counter++;
	}
}

/************************* TIMER1 *****************************/

void MTIMER1_voidInit(void)
{
	/* Set Mode for timer1 */
	TCCR1 &= TIMER1_MODE_SEL_BIT_MASK;
    TCCR1 |= TIMER1_MODE_SEL;

	/*Set compare A output mode*/
	TCCR1A &= TIMER1_OC1A_MODE_BIT_MASK;
    TCCR1A |= TIMER1_OC1A_OUTPUT_COMPARE_SEL;

	/*Set compare B output mode*/
	TCCR1A &= TIMER1_OC1B_MODE_BIT_MASK;
    TCCR1A |= TIMER1_OC1B_OUTPUT_COMPARE_SEL;

	/*Set The Prescaler*/
	TCCR1B &= TIMER1_CLK_SEL_BIT_MASK;
    TCCR1B |= TIMER1_CLK_SEL;
}

void MTIMER1_voidSetPreloadValue(u16 Copy_u16Value)
{
	TCNT1 = Copy_u16Value;
}

void MTIMER1_voidSetOC1AMatchValue(u16 Copy_u16Value)
{
	OCR1A = Copy_u16Value;
}

void MTIMER1_voidSetOC1BMatchValue(u16 Copy_u16Value)
{
	OCR1B = Copy_u16Value;
}

void MTIMER1_voidSetICR1Value(u16 Copy_u16Value)
{
	ICR1 = Copy_u16Value;
}

void MTIMER1_voidEnableInterrupt(u8 Copy_u8Mode)
{
	if(Copy_u8Mode == TIMER1_OVF)
	{
		SET_BIT(TIMSK, TIMSK_TOIE1);
	}
	else if(Copy_u8Mode == TIMER1_COMPB)
	{
		SET_BIT(TIMSK, TIMSK_OCIE1B);
	}
	else if(Copy_u8Mode == TIMER1_COMPA)
	{
		SET_BIT(TIMSK, TIMSK_OCIE1A);
	}
	else if(Copy_u8Mode == TIMER1_CAPT)
	{
		SET_BIT(TIMSK, TIMSK_TICIE1);
	}
}

void MTIMER1_voidDisableInterrupt(u8 Copy_u8Mode)
{
	if(Copy_u8Mode == TIMER1_OVF)
	{
		CLR_BIT(TIMSK, TIMSK_TOIE1);
	}
	else if(Copy_u8Mode == TIMER1_COMPB)
	{
		CLR_BIT(TIMSK, TIMSK_OCIE1B);
	}
	else if(Copy_u8Mode == TIMER1_COMPA)
	{
		CLR_BIT(TIMSK, TIMSK_OCIE1A);
	}
	else if(Copy_u8Mode == TIMER1_CAPT)
	{
		CLR_BIT(TIMSK, TIMSK_TICIE1);
	}
}

void MTIMER1_voidSetBusyWait_OVFMode(u32 Copy_u32Time)
{
	/*Set The Prescaler to be 8*/
	TCCR1B &= TIMER1_CLK_SEL_BIT_MASK;
    TCCR1B |= TIMER1_CLK_SEL;

	MTIMER1_voidSetPreloadValue(6);
	u32 Number_of_OVF = ((u32)Copy_u32Time * 1000UL) / 65530UL;

	u32 Local_u32Counter = 0;

	while(Local_u32Counter < Number_of_OVF)
	{
		while(GET_BIT(TIFR , TIFR_TOV1) == 0);
		SET_BIT(TIFR , TIFR_TOV1);
		Local_u32Counter++;
		MTIMER1_voidSetPreloadValue(6);
	}
}

void MTIMER1_voidSetBusyWait_OC1BMode(u32 Copy_u32Time)
{
	/*Set The Prescaler to be 8*/
	TCCR1B &= TIMER1_CLK_SEL_BIT_MASK;
    TCCR1B |= TIMER1_CLK_SEL;

	MTIMER1_voidSetOC1BMatchValue(65530);
	u32 Number_Of_OCF = ((u32)Copy_u32Time * 1000UL) / 65530UL;

	u32 Local_u32Counter = 0;

	while(Local_u32Counter <= Number_Of_OCF)
	{
		while(GET_BIT(TIFR , TIFR_OCF1B) == 0);
		SET_BIT(TIFR , TIFR_OCF1B);
		Local_u32Counter++;
	}
}

void MTIMER1_voidSetBusyWait_OC1AMode(u32 Copy_u32Time)
{
	/*Set The Prescaler to be 8*/
	TCCR1B &= TIMER1_CLK_SEL_BIT_MASK;
    TCCR1B |= TIMER1_CLK_SEL;

	MTIMER1_voidSetOC1AMatchValue(65530);
	u32 Number_Of_OCF = ((u32)Copy_u32Time * 1000UL) / 65530UL;

	u32 Local_u32Counter = 0;

	while(Local_u32Counter <= Number_Of_OCF)
	{
		while(GET_BIT(TIFR , TIFR_OCF1A) == 0);
		SET_BIT(TIFR , TIFR_OCF1A);
		Local_u32Counter++;
	}
}

void MICU_voidInterruptControl(u8 Copy_u8InterruptEnable)
{
    switch (Copy_u8InterruptEnable)
    {
		case ICU_ENABLE:
			SET_BIT(TIMSK, TIMSK_TICIE1);
		break;
		case ICU_DISABLE:
			CLR_BIT(TIMSK, TIMSK_TICIE1);
		break;
		default:
			/* Do Nothing */
		break;
    }
}

u16 MICU_u16GetICRRegister(void)
{
    return ICR1;
}

void MICU_voidSetTriggerSignal(u8 Copy_u8TriggerSignal)
{
    switch (Copy_u8TriggerSignal)
    {
		case ICU_RISING_EDGE:
			SET_BIT(TCCR1B, TCCR1B_ICES1);
		break;
		case ICU_FALLING_EDGE:
			CLR_BIT(TCCR1B, TCCR1B_ICES1);
		break;
		default:
				/* Do Nothing */
		break;
    }
}

/************************* TIMER2 *****************************/

void MTIMER2_voidInit(void)
{
	/* Set Mode for timer2 */
	TCCR2 &= TIMER2_MODE_SEL_BIT_MASK;
    TCCR2 |= TIMER2_MODE_SEL;

	/*Set compare output mode*/
	TCCR2 &= TIMER2_OC2_MODE_BIT_MASK;
    TCCR2 |= TIMER2_OUTPUT_COMPARE_SEL;

	/*Asynchronous Status Timer2*/
	switch (TIMER2_ASYNCHRONOUS_STATUS)
    {
		case CLK:
			CLR_BIT(ASSR, ASSR_AS2);
		break;
		case OSC:
			SET_BIT(ASSR, ASSR_AS2);
		break;
		default:
			/* Do Nothing */
		break;
    }

	/*Set The Prescaler*/
	TCCR2 &= TIMER2_CLK_SEL_BIT_MASK;
    TCCR2 |= TIMER2_CLK_SEL;
}

void MTIMER2_voidSetPreloadValue(u8 Copy_u8Value)
{
	TCNT2 = Copy_u8Value;
}

void MTIMER2_voidSetOCMatchValue(u8 Copy_u8Value)
{
	OCR2 = Copy_u8Value;
}

void MTIMER2_voidEnableInterrupt(u8 Copy_u8Mode)
{
	if(Copy_u8Mode == TIMER2_OVF)
	{
		SET_BIT(TIMSK,TIMSK_TOIE2);
	}
	else if(Copy_u8Mode == TIMER2_COMP)
	{
		SET_BIT(TIMSK,TIMSK_OCIE2);
	}
}

void MTIMER2_voidDisableInterrupt(u8 Copy_u8Mode)
{
	if(Copy_u8Mode == TIMER2_OVF)
	{
		CLR_BIT(TIMSK,TIMSK_TOIE2);
	}
	else if(Copy_u8Mode == TIMER2_COMP)
	{
		CLR_BIT(TIMSK,TIMSK_OCIE2);
	}
}

void MTIMER2_voidSetBusyWait_OVFMode(u32 Copy_u32Time)
{
	/*Set The Prescaler to be 8*/
	TCCR2 &= TIMER2_MODE_SEL_BIT_MASK;
    TCCR2 |= TIMER2_MODE_SEL;

	MTIMER2_voidSetPreloadValue(6);
	u32 Number_of_OVF = ((u32)Copy_u32Time * 1000UL) / 250UL;

	u32 Local_u32Counter = 0;

	while(Local_u32Counter < Number_of_OVF)
	{
		while(GET_BIT(TIFR , TIFR_TOV2) == 0);
		SET_BIT(TIFR , TIFR_TOV2);
		Local_u32Counter++;
		MTIMER2_voidSetPreloadValue(6);
	}
}

void MTIMER2_voidSetBusyWait_OCMode(u32 Copy_u32Time)
{
	/*Set The Prescaler to be 8*/
	TCCR2 &= TIMER2_MODE_SEL_BIT_MASK;
    TCCR2 |= TIMER2_MODE_SEL;

	MTIMER2_voidSetOCMatchValue(250);
	u32 Number_Of_OCF = ((u32)Copy_u32Time * 1000UL) / 250UL;

	u32 Local_u32Counter = 0;

	while(Local_u32Counter <= Number_Of_OCF)
	{
		while(GET_BIT(TIFR , TIFR_OCF2) == 0);
		SET_BIT(TIFR , TIFR_OCF2);
		Local_u32Counter++;
	}
}

/********************** ISR of TIMER0 *****************************/

			/******OVF T0 ISR*******/
void MTIMER0_voidSetOVFCallBack(void(*pvNotificationFunction)(void))
{
	TIMER0_pvOVFNotificationFunction = pvNotificationFunction;
}
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if ( TIMER0_pvOVFNotificationFunction != NULL )
	{
		TIMER0_pvOVFNotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}

			/******COMP T0 ISR*******/
void MTIMER0_voidSetOCCallBack(void(*pvNotificationFunction)(void))
{
	TIMER0_pvOCNotificationFunction = pvNotificationFunction;
}
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if ( TIMER0_pvOCNotificationFunction != NULL )
	{
		TIMER0_pvOCNotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}

/********************** ISR of TIMER1 *****************************/

			/******OVF T1 ISR*******/
void MTIMER1_voidSetOVFCallBack(void(*pvNotificationFunction)(void))
{
	TIMER1_pvOVFNotificationFunction = pvNotificationFunction;
}
void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	if ( TIMER1_pvOVFNotificationFunction != NULL )
	{
		TIMER1_pvOVFNotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}

			/******COMPA T1 ISR*******/
void MTIMER1_voidSetOC1ACallBack(void(*pvNotificationFunction)(void))
{
	TIMER1_pvOC1ANotificationFunction = pvNotificationFunction;
}
void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	if ( TIMER1_pvOC1ANotificationFunction != NULL )
	{
		TIMER1_pvOC1ANotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}

			/******COMPB T1 ISR*******/
void MTIMER1_voidSetOC1BCallBack(void(*pvNotificationFunction)(void))
{
	TIMER1_pvOC1BNotificationFunction = pvNotificationFunction;
}
void __vector_8 (void) __attribute__((signal));
void __vector_8 (void)
{
	if ( TIMER1_pvOC1BNotificationFunction != NULL )
	{
		TIMER1_pvOC1BNotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}

			/******CAPT T1 ISR*******/
			/********ICU ISR********/
void MTIMER1_voidSetICUCallBack(void(*pvNotificationFunction)(void))
{
	TIMER1_pvICUNotificationFunction = pvNotificationFunction;
}
void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if ( TIMER1_pvICUNotificationFunction != NULL )
	{
		TIMER1_pvICUNotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}

/********************** ISR of TIMER2 *****************************/

			/******OVF T2 ISR*******/
void MTIMER2_voidSetOVFCallBack(void(*pvNotificationFunction)(void))
{
	TIMER2_pvOVFNotificationFunction = pvNotificationFunction;
}
void __vector_5 (void) __attribute__((signal));
void __vector_5 (void)
{
	if ( TIMER2_pvOVFNotificationFunction != NULL )
	{
		TIMER2_pvOVFNotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}

			/******COMP T2 ISR*******/
void MTIMER2_voidSetOCCallBack(void(*pvNotificationFunction)(void))
{
	TIMER2_pvOCNotificationFunction = pvNotificationFunction;
}
void __vector_4 (void) __attribute__((signal));
void __vector_4 (void)
{
	if ( TIMER2_pvOCNotificationFunction != NULL )
	{
		TIMER2_pvOCNotificationFunction();
	}
	else
	{
		/* Do Nothing */
	}
}