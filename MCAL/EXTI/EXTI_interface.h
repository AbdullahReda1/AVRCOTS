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


#ifndef 	MCAL_EXTI_EXTI_interface_H_
#define 	MCAL_EXTI_EXTI_interface_H_


#define		LOW_LEVEL			        		0
#define		ANY_LOGICAL_CHANGE			        1
#define		FALLING_EDGE			    		2
#define		RISINGING_EDGE			    		3

#define     EXTI_INT0         0
#define     EXTI_INT1         1
#define     EXTI_INT2         2

void MEXTI_voidInit(u8 Copy_u8IntNum);
void MEXTI_voidEnable(u8 Copy_u8IntNum);
void MEXTI_voidDisable(u8 Copy_u8IntNum);
void MEXTI_voidTriggerEdge(u8 Copy_u8IntNum, u8 Copy_u8Edge);
void MEXTI_voidINT0SetCallback(void(*Notificationfunction)(void));
void MEXTI_voidINT1SetCallback(void (*NotificationFunction)(void));
void MEXTI_voidINT2SetCallback(void (*NotificationFunction)(void));


#endif