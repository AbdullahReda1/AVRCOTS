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

#ifndef 	MCAL_EXTI_EXTI_private_H_
#define 	MCAL_EXTI_EXTI_private_H_


#define		MCUCR				*((volatile u8*)0x55)
#define		MCUCSR			    *((volatile u8*)0x54)
#define		GICR				*((volatile u8*)0x5B)
#define		GIFR				*((volatile u8*)0x5A)

#define NULL     '\0'

#define     EXTI0_PORT      DIO_PORTD
#define     EXTI0_PIN       PIN2

#define     EXTI1_PORT      DIO_PORTD
#define     EXTI1_PIN       PIN3

#define     EXTI2_PORT      DIO_PORTB
#define     EXTI2_PIN       PIN2

#define		MCUCR_ISC00			0
#define		MCUCR_ISC01			1
#define		MCUCR_ISC10			2
#define		MCUCR_ISC11			3

#define		MCUCSR_ISC2			6

#define		GICR_INT0			6
#define		GICR_INT1			7
#define		GICR_INT2			5

#define		INT0_INPUT_PULLUP			            0
#define		INT0_INPUT_EXTERNAL_PULLUP			    1
#define		INT0_INPUT_EXTERNAL_PULLDOWN			2

#define		INT1_INPUT_PULLUP			            0
#define		INT1_INPUT_EXTERNAL_PULLUP			    1
#define		INT1_INPUT_EXTERNAL_PULLDOWN			2

#define		INT2_INPUT_PULLUP			           	0
#define		INT2_INPUT_EXTERNAL_PULLUP			    1
#define		INT2_INPUT_EXTERNAL_PULLDOWN			2


#endif