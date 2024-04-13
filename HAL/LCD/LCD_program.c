/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    26 MAR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          26 MAR, 2023     Abdullah R.Hebashi       Initial Creation    
***********************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include <util/delay.h>
#include "../../MCAL/DIO/DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"


void HLCD_voidInit(void)
{
    #if LCD_INIT_MODE == EIGHT_BIT_MODE
		MDIO_voidSetportdir(LCD_DATA_PORT, LCD_ALL_OUTPUT);
		MDIO_voidsetpindir(LCD_CTRL_PORT, LCD_RW_PIN, OUTPUT);
		MDIO_voidsetpindir(LCD_CTRL_PORT, LCD_RS_PIN, OUTPUT);
		MDIO_voidsetpindir(LCD_CTRL_PORT, LCD_EN_PIN, OUTPUT);
		_delay_ms(40);
		HLCD_voidSendCommand(FUNCTION_SET_CMD);
		HLCD_voidSendCommand(DISPLAY_ON_OFF_CMD);
		HLCD_voidSendCommand(DISPLAY_CLEAR_CMD);
    #elif LCD_INIT_MODE == FOUR_BIT_MODE
		MDIO_voidSetHighNippledir(LCD_DATA_PORT, LCD_ALL_OUTPUT);
		MDIO_voidsetpindir(LCD_CTRL_PORT, LCD_RW_PIN, OUTPUT);
		MDIO_voidsetpindir(LCD_CTRL_PORT, LCD_RS_PIN, OUTPUT);
		MDIO_voidsetpindir(LCD_CTRL_PORT, LCD_EN_PIN, OUTPUT);
		_delay_ms(40);
		HLCD_voidSendCommand(FUNCTION_SET_4BITM_CMD);
		HLCD_voidSendCommand(DISPLAY_ON_OFF_CMD);
		HLCD_voidSendCommand(DISPLAY_CLEAR_CMD);
    #else
        #error ("LCD_INIT_MODE Configuration Error")
    #endif
}

void HLCD_voidSendData(u8 Copy_u8Data)
{
	#if LCD_INIT_MODE == EIGHT_BIT_MODE
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RS_PIN, HIGH);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RW_PIN, LOW);
		MDIO_voidSetportval(LCD_DATA_PORT, Copy_u8Data);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, HIGH);
		_delay_ms(2);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
	#elif LCD_INIT_MODE == FOUR_BIT_MODE
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RS_PIN, HIGH);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RW_PIN, LOW);
		MDIO_voidSetportval(LCD_DATA_PORT, (Copy_u8Data>>4));
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, HIGH);
		_delay_ms(2);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RS_PIN, HIGH);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RW_PIN, LOW);
		MDIO_voidSetportval(LCD_DATA_PORT, (Copy_u8Data));
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, HIGH);
		_delay_ms(2);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
    #else
        #error ("LCD_INIT_MODE Configuration Error")
    #endif
}

void HLCD_voidSendCommand(u8 Copy_u8Command)
{
	#if LCD_INIT_MODE == EIGHT_BIT_MODE
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RS_PIN, LOW);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RW_PIN, LOW);
		MDIO_voidSetportval(LCD_DATA_PORT, Copy_u8Command);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, HIGH);
		_delay_ms(2);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
	#elif LCD_INIT_MODE == FOUR_BIT_MODE
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RS_PIN, LOW);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RW_PIN, LOW);
		MDIO_voidSetportval(LCD_DATA_PORT, (Copy_u8Command>>4));
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, HIGH);
		_delay_ms(2);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RS_PIN, LOW);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_RW_PIN, LOW);
		MDIO_voidSetportval(LCD_DATA_PORT, (Copy_u8Command));
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, HIGH);
		_delay_ms(2);
		MDIO_voidsetpinval(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
    #else
        #error ("LCD_INIT_MODE Configuration Error")
    #endif

}

void HLCD_voidClearDisplay(void)
{
    HLCD_voidSendCommand(DISPLAY_CLEAR_CMD);
}

void HLCD_voidGoToXY(u8 Copy_u8XPos, u8 Copy_u8YPos)
{
    u8 Local_u8CharacterAddress = 0;
    if(Copy_u8XPos == 1)
    {
        Local_u8CharacterAddress = (Copy_u8YPos - 1) + 0x80;
    }
    else if (Copy_u8XPos == 2)
    {
        Local_u8CharacterAddress = (Copy_u8YPos - 1) + 0xC0;
    }
    else
    {
        // Raise an error 
    }
    HLCD_voidSendCommand(Local_u8CharacterAddress);
}

void HLCD_voidSendString(u8 * Copy_pu8StringArray)
{
    u8 Local_u8LoopCounter = 0 ;
    while(Copy_pu8StringArray[Local_u8LoopCounter] != '\0')
    {
        HLCD_voidSendData(Copy_pu8StringArray[Local_u8LoopCounter]);
        Local_u8LoopCounter++;
    }
}

void HLCD_voidSendNumber(u32 Copy_u32Number)
{
    u8 Local_u8ArrayNumber[10];
    s8 Local_s8LoopCounter = 0;
    while(Copy_u32Number != 0)
    {
        Local_u8ArrayNumber[Local_s8LoopCounter] = Copy_u32Number % 10;
        Copy_u32Number /= 10;
        Local_s8LoopCounter++;
    }
    Local_s8LoopCounter--;
    while(Local_s8LoopCounter >= 0)
    {
        HLCD_voidSendData(Local_u8ArrayNumber[Local_s8LoopCounter] + '0');
        Local_s8LoopCounter--;
    }
}


void HLCD_voidSendCustomCharacter(u8 * Copy_pu8CharacterArray, u8 Copy_u8PatternNumber, u8 Copy_u8XPosition, u8 Copy_u8YPosition)
{
    u8 Local_u8LoopCounter;
    u8 Local_u8CGRAMAddress = 0;
    Local_u8CGRAMAddress = Copy_u8PatternNumber * 8;
    SET_BIT(Local_u8CGRAMAddress, 6);
    HLCD_voidSendCommand(Local_u8CGRAMAddress);
    for(Local_u8LoopCounter = 0; Local_u8LoopCounter < 8; Local_u8LoopCounter++)
    {
        HLCD_voidSendData(Copy_pu8CharacterArray[Local_u8LoopCounter]);
    }
    HLCD_voidGoToXY(Copy_u8XPosition, Copy_u8YPosition);
    HLCD_voidSendData(Copy_u8PatternNumber);
}

