/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    17 APR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          17 APR, 2023     Abdullah R.Hebashi       Initial Creation
***********************************************************/


#ifndef 	MCAL_UART_UART_private_H_
#define 	MCAL_UART_UART_private_H_


#define NULL     '\0'

// Needed Baud Rates While F_CPU = 8MHz.
#define     BR_2400_BPS     207
#define     BR_4800_BPS     103
#define     BR_9600_BPS     51

#define     FREE_REG        0


/******************************Register Description*******************************/

#define UDR       *((volatile u8*)0x2C)
#define UCSRA     *((volatile u8*)0x2B)
#define UCSRB     *((volatile u8*)0x2A)
#define UBRRL     *((volatile u8*)0x29)
#define UCSRC     *((volatile u8*)0x40)
#define UBRRH     *((volatile u8*)0x40)

#define UCSRA_MPCM        0
#define UCSRA_U2X         1
#define UCSRA_PE          2
#define UCSRA_DOR         3
#define UCSRA_FE          4
#define UCSRA_UDRE        5
#define UCSRA_TXC         6
#define UCSRA_RXC         7

#define UCSRB_TXB8        0
#define UCSRB_RXB8        1
#define UCSRB_UCSZ2       2
#define UCSRB_TXEN        3
#define UCSRB_RXEN        4
#define UCSRB_UDRIE       5
#define UCSRB_TXCIE       6
#define UCSRB_RXCIE       7

#define UCSRC_UCPOL       0
#define UCSRC_UCSZ0       1
#define UCSRC_UCSZ1       2
#define UCSRC_USBS        3
#define UCSRC_UPM0        4
#define UCSRC_UPM1        5
#define UCSRC_UMSEL       6
#define UCSRC_URSEL       7

#define UBRRH_URSEL       7


#endif