/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    25 MAR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          25 MAR, 2023     Abdullah R.Hebashi       Initial Creation    
***********************************************************/

#ifndef 	MCAL_DIO_DIO_private_H_
#define 	MCAL_DIO_DIO_private_H_


#define 	PORTA         *((volatile u8*)0x3B)
#define 	DDRA          *((volatile u8*)0x3A)
#define 	PINA          *((volatile u8*)0x39)

#define 	PORTB         *((volatile u8*)0x38)
#define 	DDRB          *((volatile u8*)0x37)
#define 	PINB          *((volatile u8*)0x36)

#define 	PORTC         *((volatile u8*)0x35)
#define 	DDRC          *((volatile u8*)0x34)
#define 	PINC          *((volatile u8*)0x33)

#define 	PORTD         *((volatile u8*)0x32)
#define 	DDRD          *((volatile u8*)0x31)
#define 	PIND          *((volatile u8*)0x30)


#endif