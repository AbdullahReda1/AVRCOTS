/********************************************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:        27 APR, 2023
 * Version:              v1.0
 * Compiler:             GNU GCC
*********************************************************************************/
/********************************************************************************
 * Version      Date                  Author                    Description
 * v1.0         27 APR, 2023          Abdullah R.Hebashi        Initial Creation    
*********************************************************************************/

#ifndef HAL_TFT_TFT_CONFIG_H_
#define HAL_TFT_TFT_CONFIG_H_

/*
    OPTIONS:
    DIO_PORTA
    DIO_PORTB
    DIO_PORTC
    DIO_PORTD
*/
#define HTFT_RESET_PORT      DIO_PORTA

/*
    OPTIONS:
    PIN0
    PIN1
    PIN2
    PIN3
    PIN4
    PIN5
    PIN6
    PIN7
*/
#define HTFT_RESET_PIN       PIN0


/*
    OPTIONS:
    DIO_PORTA
    DIO_PORTB
    DIO_PORTC
    DIO_PORTD
*/
#define HTFT_A0_PORT         DIO_PORTA

/*
    OPTIONS:
    PIN0
    PIN1
    PIN2
    PIN3
    PIN4
    PIN5
    PIN6
    PIN7
*/
#define HTFT_A0_PIN          PIN1


#endif