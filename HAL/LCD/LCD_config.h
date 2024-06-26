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


#ifndef 		HAL_LCD_LCD_config_H_
#define 		HAL_LCD_LCD_config_H_


/*Options:
    DIO_PORTA
    DIO_PORTB
    DIO_PORTC
    DIO_PORTD
*/
#define     LCD_DATA_PORT       DIO_PORTA

/*Options:
    DIO_PORTA
    DIO_PORTB
    DIO_PORTC
    DIO_PORTD
*/
#define     LCD_CTRL_PORT       DIO_PORTB

#define     LCD_RW_PIN          PIN0
#define     LCD_RS_PIN          PIN1
#define     LCD_EN_PIN          PIN2

/*Options:
    EIGHT_BIT_MODE
    FOUR_BIT_MODE
*/
#define LCD_INIT_MODE       EIGHT_BIT_MODE


#endif