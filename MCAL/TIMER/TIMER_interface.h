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


#ifndef 	MCAL_TIMER_TIMER_interface_H_
#define 	MCAL_TIMER_TIMER_interface_H_


/************************* TIMER0 *****************************/

#define TIMER0_OVF      0
#define TIMER0_COMP     1


void MTIMER0_voidInit(void);

void MTIMER0_voidDisableTimer0(void);
void MTIMER0_voidEnableTimer0(void);

void MTIMER0_voidSetPreloadValue(u8 Copy_u8Value);
void MTIMER0_voidSetOCMatchValue(u8 Copy_u8Value);

void MTIMER0_voidSetOVFCallBack(void(*pvNotificationFunction)(void));
void MTIMER0_voidSetOCCallBack(void(*pvNotificationFunction)(void));

void MTIMER0_voidEnableInterrupt(u8 Copy_u8Mode);
void MTIMER0_voidDisableInterrupt(u8 Copy_u8Mode);

void MTIMER0_voidSetBusyWait_OVFMode(u32 Copy_u32Time);
void MTIMER0_voidSetBusyWait_OCMode(u32 Copy_u32Time);

/************************* TIMER1 *****************************/

#define     TIMER1_OVF            0
#define     TIMER1_COMPB          1
#define     TIMER1_COMPA          2
#define     TIMER1_CAPT           3

#define     ICU_ENABLE            1
#define     ICU_DISABLE           0

#define     ICU_RISING_EDGE       1
#define     ICU_FALLING_EDGE      0


void MTIMER1_voidInit(void);

void MTIMER1_voidSetPreloadValue(u16 Copy_u16Value);
void MTIMER1_voidSetOC1AMatchValue(u16 Copy_u16Value);
void MTIMER1_voidSetOC1BMatchValue(u16 Copy_u16Value);
void MTIMER1_voidSetICR1Value(u16 Copy_u16Value);

void MTIMER1_voidEnableInterrupt(u8 Copy_u8Mode);
void MTIMER1_voidDisableInterrupt(u8 Copy_u8Mode);

void MTIMER1_voidSetBusyWait_OVFMode(u32 Copy_u32Time);
void MTIMER1_voidSetBusyWait_OC1BMode(u32 Copy_u32Time);
void MTIMER1_voidSetBusyWait_OC1AMode(u32 Copy_u32Time);

void MICU_voidInterruptControl(u8 Copy_u8InterruptEnable);
u16 MICU_u16GetICRRegister(void);
void MICU_voidSetTriggerSignal(u8 Copy_u8TriggerSignal);

void MTIMER1_voidSetOVFCallBack(void(*pvNotificationFunction)(void));
void MTIMER1_voidSetOC1ACallBack(void(*pvNotificationFunction)(void));
void MTIMER1_voidSetOC1BCallBack(void(*pvNotificationFunction)(void));
void MTIMER1_voidSetICUCallBack(void(*pvNotificationFunction)(void));

/************************* TIMER2 *****************************/

#define TIMER2_OVF      0
#define TIMER2_COMP     1

#define CLK      1
#define OSC      0


void MTIMER2_voidInit(void);

void MTIMER2_voidSetPreloadValue(u8 Copy_u8Value);
void MTIMER2_voidSetOCMatchValue(u8 Copy_u8Value);

void MTIMER2_voidSetOVFCallBack(void(*pvNotificationFunction)(void));
void MTIMER2_voidSetOCCallBack(void(*pvNotificationFunction)(void));

void MTIMER2_voidEnableInterrupt(u8 Copy_u8Mode);
void MTIMER2_voidDisableInterrupt(u8 Copy_u8Mode);

void MTIMER2_voidSetBusyWait_OVFMode(u32 Copy_u32Time);
void MTIMER2_voidSetBusyWait_OCMode(u32 Copy_u32Time);


#endif