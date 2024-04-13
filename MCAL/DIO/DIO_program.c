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


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "DIO_interface.h"
#include "DIO_config.h"
#include "DIO_private.h"

// Set pin direction...

void MDIO_voidsetpindir(u8 Copy_u8portName, u8 Copy_u8pinNumber, u8 Copy_u8dirStatus)
{
	switch(Copy_u8portName)
	{
		case DIO_PORTA:
		if ( OUTPUT==Copy_u8dirStatus )
		{
			SET_BIT(DDRA,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(DDRA,Copy_u8pinNumber);
		}
		break;
		case DIO_PORTB:
		if ( OUTPUT==Copy_u8dirStatus )
		{
			SET_BIT(DDRB,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(DDRB,Copy_u8pinNumber);
		}
		break;
		case DIO_PORTC:
		if ( OUTPUT==Copy_u8dirStatus )
		{
			SET_BIT(DDRC,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(DDRC,Copy_u8pinNumber);
		}
		break;
		case DIO_PORTD:
		if ( OUTPUT==Copy_u8dirStatus )
		{
			SET_BIT(DDRD,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(DDRD,Copy_u8pinNumber);
		}
		break;
		default:
			/* Do Nothing */
		break;
	}
}

// Write pin...

void MDIO_voidsetpinval(u8 Copy_u8portName, u8 Copy_u8pinNumber, u8 Copy_u8inputVal)
{
	switch(Copy_u8portName)
	{
		case DIO_PORTA:
		if ( HIGH==Copy_u8inputVal )
		{
			SET_BIT(PORTA,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(PORTA,Copy_u8pinNumber);
		}
		break;
		case DIO_PORTB:
		if ( HIGH==Copy_u8inputVal )
		{
			SET_BIT(PORTB,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(PORTB,Copy_u8pinNumber);
		}
		break;
		case DIO_PORTC:
		if ( HIGH==Copy_u8inputVal )
		{
			SET_BIT(PORTC,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(PORTC,Copy_u8pinNumber);
		}
		break;
		case DIO_PORTD:
		if ( HIGH==Copy_u8inputVal )
		{
			SET_BIT(PORTD,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(PORTD,Copy_u8pinNumber);
		}
		break;
		default:
			/* Do Nothing */
		break;
	}
}

// Read pin...

u8 MDIO_u8GetVal(u8 Copy_u8portName, u8 Copy_u8pinNumber)
{
	u8 Local_u8returnval = 0;
	switch(Copy_u8portName)
	{
		case DIO_PORTA:
		Local_u8returnval = GET_BIT(PINA,Copy_u8pinNumber);
		break;
		case DIO_PORTB:
		Local_u8returnval = GET_BIT(PINB,Copy_u8pinNumber);
		break;
		case DIO_PORTC:
		Local_u8returnval = GET_BIT(PINC,Copy_u8pinNumber);
		break;
		case DIO_PORTD:
		Local_u8returnval = GET_BIT(PIND,Copy_u8pinNumber);
		break;
		default:
			/* Do Nothing */
		break;
	}
	return Local_u8returnval;
}

// Toggle pin...

void MDIO_voidTogPin(u8 Copy_u8portName, u8 Copy_u8pinNumber)
{
	switch(Copy_u8portName)
	{
		case DIO_PORTA:
		TOG_BIT(PORTA,Copy_u8pinNumber);
		break;
		case DIO_PORTB:
		TOG_BIT(PORTB,Copy_u8pinNumber);
		break;
		case DIO_PORTC:
		TOG_BIT(PORTC,Copy_u8pinNumber);
		break;
		case DIO_PORTD:
		TOG_BIT(PORTD,Copy_u8pinNumber);
		break;
		default:
			/* Do Nothing */
		break;
	}
}

// Set port direction...

void MDIO_voidSetportdir(u8 Copy_u8portName, u8 Copy_u8dirStatus)
{
	/*(NOTICE)
    Status ORTIONS:
		ALL_OUTPUT
		ALL_INPUT
*/
	switch(Copy_u8portName)
	{
		case DIO_PORTA:
		SET_REG(DDRA, Copy_u8dirStatus);
		break;
		case DIO_PORTB:
		SET_REG(DDRB, Copy_u8dirStatus);
		break;
		case DIO_PORTC:
		SET_REG(DDRC, Copy_u8dirStatus);
		break;
		case DIO_PORTD:
		SET_REG(DDRD, Copy_u8dirStatus);
		break;
		default:
			/* Do Nothing */
		break;
	}
}

// Write port...

void MDIO_voidSetportval(u8 Copy_u8portName, u8 Copy_u8portval)
{
	switch(Copy_u8portName)
	{
		case DIO_PORTA:
		SET_REG(PORTA, Copy_u8portval);
		break;
		case DIO_PORTB:
		SET_REG(PORTB, Copy_u8portval);
		break;
		case DIO_PORTC:
		SET_REG(PORTC, Copy_u8portval);
		break;
		case DIO_PORTD:
		SET_REG(PORTD, Copy_u8portval);
		break;
		default:
			/* Do Nothing */
		break;
	}
}

// Read port...

u8 MDIO_u8GetportVal(u8 Copy_u8portName)
{
	u8 Local_u8returnval =0;
	switch(Copy_u8portName)
	{
		case DIO_PORTA:
		Local_u8returnval = PINA;
		break;
		case DIO_PORTB:
		Local_u8returnval = PINB;
		break;
		case DIO_PORTC:
		Local_u8returnval = PINC;
		break;
		case DIO_PORTD:
		Local_u8returnval = PIND;
		break;
		default:
			/* Do Nothing */
		break;
	}
	return Local_u8returnval;
}

// Toggle port...

void MDIO_voidTogPort(u8 Copy_u8portName)
{
	switch(Copy_u8portName)
	{
		case DIO_PORTA:
		PORTA = (~ PORTA);
		break;
		case DIO_PORTB:
		PORTB = (~ PORTB);
		break;
		case DIO_PORTC:
		PORTC = (~ PORTC);
		break;
		case DIO_PORTD:
		PORTD = (~ PORTD);
		break;
		default:
			/* Do Nothing */
		break;
	}
}

// Internal pull up enable...

void MDIO_voidpullup(u8 Copy_u8portName, u8 Copy_u8pinNumber, u8 Copy_u8EnableVal)
{
	switch(Copy_u8portName)
	{
		case DIO_PORTA:
		if ( 1==Copy_u8EnableVal )
		{
			SET_BIT(PORTA,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(PORTA,Copy_u8pinNumber);
		}
		break;
		case DIO_PORTB:
		if ( 1==Copy_u8EnableVal )
		{
			SET_BIT(PORTB,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(PORTB,Copy_u8pinNumber);
		}
		break;
		case DIO_PORTC:
		if ( 1==Copy_u8EnableVal )
		{
			SET_BIT(PORTC,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(PORTC,Copy_u8pinNumber);
		}
		break;
		case DIO_PORTD:
		if ( 1==Copy_u8EnableVal )
		{
			SET_BIT(PORTD,Copy_u8pinNumber);
		}
		else
		{
			CLR_BIT(PORTD,Copy_u8pinNumber);
		}
		break;
		default:
			/* Do Nothing */
		break;
	}
}

// Set low nibble direction...

void MDIO_voidSetLowNippledir(u8 Copy_u8portName, u8 Copy_u8dirStatus)
{
	u8 Local_u8loopCounter;
	for ( Local_u8loopCounter=0 ; Local_u8loopCounter<=3 ; Local_u8loopCounter++ )
	{
		MDIO_voidsetpindir(Copy_u8portName, Local_u8loopCounter, Copy_u8dirStatus);
	}
}

// Set high nibble direction...

void MDIO_voidSetHighNippledir(u8 Copy_u8portName, u8 Copy_u8dirStatus)
{
	u8 Local_u8loopCounter;
	for ( Local_u8loopCounter=4 ; Local_u8loopCounter<=7 ; Local_u8loopCounter++ )
	{
		MDIO_voidsetpindir(Copy_u8portName, Local_u8loopCounter, Copy_u8dirStatus);
	}
}

// Write low nibble...

void MDIO_voidSetLowNippleVal(u8 Copy_u8portName, u8 Copy_u8NippleVal)
{
	u8 Local_u8loopCounter;
	for ( Local_u8loopCounter=0 ; Local_u8loopCounter<=3 ; Local_u8loopCounter++ )
	{
		MDIO_voidsetpinval(Copy_u8portName, Local_u8loopCounter, GET_BIT(Copy_u8NippleVal, Local_u8loopCounter));
	}
}

// Write high nibble...

void MDIO_voidSetHighNippleVal(u8 Copy_u8portName, u8 Copy_u8NippleVal)
{
	u8 Local_u8loopCounter;
	for ( Local_u8loopCounter=4 ; Local_u8loopCounter<=7 ; Local_u8loopCounter++ )
	{
		MDIO_voidsetpinval(Copy_u8portName, Local_u8loopCounter, GET_BIT(Copy_u8NippleVal, (Local_u8loopCounter-4)));
	}
}


void MDIO_voidSPIMasterConfig(void)
{
	//MOSI
	MDIO_voidsetpindir(DIO_PORTB, PIN5, OUTPUT);
	//SCK
	MDIO_voidsetpindir(DIO_PORTB, PIN7, OUTPUT);
	//SS
	MDIO_voidsetpindir(DIO_PORTB, PIN4, OUTPUT);
	MDIO_voidsetpinval(DIO_PORTB, PIN4, HIGH);
}

void MDIO_voidSPISlaveConfig(void)
{
	//MISO
	MDIO_voidsetpindir(DIO_PORTB, PIN6, OUTPUT);
}