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


#ifndef 	MCAL_DIO_DIO_interface_H_
#define 	MCAL_DIO_DIO_interface_H_

#define 	PIN0        0
#define 	PIN1        1
#define 	PIN2        2
#define 	PIN3        3
#define 	PIN4        4
#define 	PIN5        5
#define 	PIN6        6
#define 	PIN7        7

#define 	DIO_PORTA   0
#define 	DIO_PORTB   1
#define 	DIO_PORTC   2
#define 	DIO_PORTD   3

#define 	OUTPUT      	1
#define 	INPUT       	0

#define 	ALL_OUTPUT      0xFF
#define 	ALL_INPUT       0x00

#define 	LOW         	0
#define 	HIGH        	1

#define 	PULLUP      	1
#define 	NO_PULLUP       0


void MDIO_voidsetpindir(u8 Copy_u8portName, u8 Copy_u8pinNumber, u8 Copy_u8dirStatus);

void MDIO_voidsetpinval(u8 Copy_u8portName, u8 Copy_u8pinNumber, u8 Copy_u8inputVal);

u8 MDIO_u8GetVal(u8 Copy_u8portName, u8 Copy_u8pinNumber);

void MDIO_voidTogPin(u8 Copy_u8portName, u8 Copy_u8pinNumber);

void MDIO_voidSetportdir(u8 Copy_u8portName, u8 Copy_u8dirStatus);

void MDIO_voidSetportval(u8 Copy_u8portName, u8 Copy_u8portval);

u8 MDIO_u8GetportVal(u8 Copy_u8portName);

void MDIO_voidTogPort(unsigned char port);

void MDIO_voidpullup(u8 Copy_u8portName, u8 Copy_u8pinNumber, u8 Copy_u8EnableVal);

void MDIO_voidSetLowNippledir(u8 Copy_u8portName, u8 Copy_u8dirStatus);

void MDIO_voidSetHighNippledir(u8 Copy_u8portName, u8 Copy_u8dirStatus);

void MDIO_voidSetLowNippleVal(u8 Copy_u8portName, u8 Copy_u8NippleVal);

void MDIO_voidSetHighNippleVal(u8 Copy_u8portName, u8 Copy_u8NippleVal);

void MDIO_voidSPIMasterConfig(void);
void MDIO_voidSPISlaveConfig(void);


#endif