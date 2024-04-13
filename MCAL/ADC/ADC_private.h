/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    30 MAR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          30 MAR, 2023     Abdullah R.Hebashi       Initial Creation 
*	v2.0			 05 APR, 2023 	  Abdullah R.Hebashi		  Adding ADC ISR
***********************************************************/


#ifndef 	MCAL_ADC_ADC_private_H_
#define 	MCAL_ADC_ADC_private_H_

#define     RIGHT_ADJUST            0
#define     LEFT_ADJUST             1

//#define     AREF                    0
//#define     AVCC                    1
//#define     INTERNAL_2v56           2

#define     ENABLE                  1
#define     DISABLE                 0

#define     AREF                    0b00000000
#define     AVCC                    0b01000000
#define     INTERNAL_2v56           0b11000000
#define     REF_SEL_BIT_MASK        0b00111111

#define     DIV_FACTOR_2            0b00000000
#define     DIV_FACTOR_4            0b00000010
#define     DIV_FACTOR_8            0b00000011
#define     DIV_FACTOR_16           0b00000100
#define     DIV_FACTOR_32           0b00000101
#define     DIV_FACTOR_64           0b00000110
#define     DIV_FACTOR_128          0b00000111
#define     PRE_SCALER_BIT_MASK     0b11111000

#define     CHANNEL_SELECTION_MASK      0b11100000


/******************************Register Description*******************************/

#define ADMUX    *((volatile u8*)0x27)
#define ADCSRA   *((volatile u8*)0x26)
#define ADCH     *((volatile u8*)0x25)
#define ADCL     *((volatile u8*)0x24)
#define ADC     *((volatile u16*)0x24)

#define NULL     '\0'

#define ADMUX_MUX0     0
#define ADMUX_MUX1     1
#define ADMUX_MUX2     2
#define ADMUX_MUX3     3
#define ADMUX_MUX4     4
#define ADMUX_ADLAR    5
#define ADMUX_REFS0    6
#define ADMUX_REFS1    7

#define ADCSRA_ADPS0     0
#define ADCSRA_ADPS1     1
#define ADCSRA_ADPS2     2
#define ADCSRA_ADIE      3
#define ADCSRA_ADIF      4
#define ADCSRA_ADATE     5
#define ADCSRA_ADSC      6
#define ADCSRA_ADEN      7


#endif