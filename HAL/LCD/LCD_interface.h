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


#ifndef 		HAL_LCD_LCD_interface_H_
#define 		HAL_LCD_LCD_interface_H_


void HLCD_voidInit(void);
void HLCD_voidSendData(u8 Copy_u8Data);
void HLCD_voidClearDisplay(void);
void HLCD_voidGoToXY(u8 Copy_u8XPos, u8 Copy_u8YPos);
void HLCD_voidSendNumber(u32 Copy_u32Number);
void HLCD_voidSendString(u8 * Copy_pu8StringArray);
void HLCD_voidSendCustomCharacter(u8 * Copy_pu8CharacterArray, u8 Copy_u8PatternNumber, u8 Copy_u8XPosition, u8 Copy_u8YPosition);
void HCD_voidSendCommand(u8 Copy_u8Command);


#endif