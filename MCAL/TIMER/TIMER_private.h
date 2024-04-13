/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    9 APR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          9 APR, 2023       Abdullah R.Hebashi       Initial Creation 
***********************************************************/


#ifndef 	MCAL_TIMER_TIMER_private_H_
#define 	MCAL_TIMER_TIMER_private_H_


/************************* TIMER0 *****************************/

#define     TIMER0_NORMAL_MODE                           0b00000000
#define     TIMER0_PHASE_CORRECT_PWM_MODE                0b01000000
#define     TIMER0_CTC_MODE                              0b00001000
#define     TIMER0_FAST_PWM_MODE                         0b01001000
#define     TIMER0_MODE_SEL_BIT_MASK                     0b10110111

//#define     NORMAL_OC0_DISCONNECTED      0
//#define     TOG_OC0_ON_COMPARE_MATCH     1
//#define     CLR_OC0_ON_COMPARE_MATCH     2
//#define     SET_OC0_ON_COMPARE_MATCH     3

#define     NORMAL_OC0_DISCONNECTED         0b00000000
#define     TOG_OC0_ON_COMPARE_MATCH        0b00010000
#define     CLR_OC0_ON_COMPARE_MATCH        0b00100000
#define     SET_OC0_ON_COMPARE_MATCH        0b00110000
#define     TIMER0_OC0_MODE_BIT_MASK        0b11001111

#define     TIMER0_STOP                     0b00000000
#define     DIV_FACTOR_1                    0b00000001
#define     DIV_FACTOR_8                    0b00000010
#define     DIV_FACTOR_64                   0b00000011
#define     DIV_FACTOR_256                  0b00000100
#define     DIV_FACTOR_1024                 0b00000101
#define     EXT_CLK_FALLING_T0              0b00000110
#define     EXT_CLK_RISING_T0               0b00000111
#define     TIMER0_CLK_SEL_BIT_MASK         0b11111000

/************************* TIMER1 *****************************/

#define     NORMAL_OC1A_DISCONNECTED         0b00000000
#define     TOG_OC1A_ON_COMPARE_MATCH        0b01000000
#define     CLR_OC1A_ON_COMPARE_MATCH        0b10000000
#define     SET_OC1A_ON_COMPARE_MATCH        0b11000000
#define     TIMER1_OC1A_MODE_BIT_MASK        0b00111111

#define     NORMAL_OC1B_DISCONNECTED         0b00000000
#define     TOG_OC1B_ON_COMPARE_MATCH        0b00010000
#define     CLR_OC1B_ON_COMPARE_MATCH        0b00100000
#define     SET_OC1B_ON_COMPARE_MATCH        0b00110000
#define     TIMER1_OC1B_MODE_BIT_MASK        0b11001111

#define     TIMER1_STOP                     0b00000000
#define     DIV_FACTOR_1                    0b00000001
#define     DIV_FACTOR_8                    0b00000010
#define     DIV_FACTOR_64                   0b00000011
#define     DIV_FACTOR_256                  0b00000100
#define     DIV_FACTOR_1024                 0b00000101
#define     EXT_CLK_FALLING_T1              0b00000110
#define     EXT_CLK_RISING_T1               0b00000111
#define     TIMER1_CLK_SEL_BIT_MASK         0b11111000

#define     TIMER1_NORMAL_MODE                                  0b0000000000000000
#define     TIMER1_PHASE_CORRECT_PWM_8_BIT_MODE                 0b0000000000000001
#define     TIMER1_PHASE_CORRECT_PWM_9_BIT_MODE                 0b0000000000000010
#define     TIMER1_PHASE_CORRECT_PWM_10_BIT_MODE                0b0000000000000011
#define     TIMER1_CTC_OCR1A_MODE                               0b0000100000000000
#define     TIMER1_FAST_PWM_8_BIT_MODE                          0b0000100000000001
#define     TIMER1_FAST_PWM_9_BIT_MODE                          0b0000100000000010
#define     TIMER1_FAST_PWM_10_BIT_MODE                         0b0000100000000011
#define     TIMER1_PHASE_FREQ_CORRECT_PWM_ICR1_MODE             0b0001000000000000
#define     TIMER1_PHASE_FREQ_CORRECT_PWM_OCR1A_MODE            0b0001000000000001
#define     TIMER1_PHASE_CORRECT_PWM_ICR1_MODE                  0b0001000000000010
#define     TIMER1_PHASE_CORRECT_PWM_OCR1A_MODE                 0b0001000000000011
#define     TIMER1_CTC_ICR1_MODE                                0b0001100000000000
#define     TIMER1_FAST_PWM_ICR1_MODE                           0b0001100000000010
#define     TIMER1_FAST_PWM_OCR1A_MODE                          0b0001100000000011
#define     TIMER1_MODE_SEL_BIT_MASK                            0b1110011111111100

/************************* TIMER2 *****************************/

#define     TIMER2_NORMAL_MODE                           0b00000000
#define     TIMER2_PHASE_CORRECT_PWM_MODE                0b01000000
#define     TIMER2_CTC_MODE                              0b00001000
#define     TIMER2_FAST_PWM_MODE                         0b01001000
#define     TIMER2_MODE_SEL_BIT_MASK                     0b10110111

#define     NORMAL_OC2_DISCONNECTED         0b00000000
#define     TOG_OC2_ON_COMPARE_MATCH        0b00010000
#define     CLR_OC2_ON_COMPARE_MATCH        0b00100000
#define     SET_OC2_ON_COMPARE_MATCH        0b00110000
#define     TIMER2_OC2_MODE_BIT_MASK        0b11001111

#define     TIMER2_STOP                     0b00000000
#define     DIV_FACTOR_1                    0b00000001
#define     DIV_FACTOR_8                    0b00000010
#define     DIV_FACTOR_32                   0b00000011
#define     DIV_FACTOR_64                   0b00000100
#define     DIV_FACTOR_128                  0b00000101
#define     DIV_FACTOR_256                  0b00000110
#define     DIV_FACTOR_1024                 0b00000111
#define     TIMER2_CLK_SEL_BIT_MASK         0b11111000


/******************************Register Description*******************************/

#define TIFR      *((volatile u8*)0x58)
#define TIMSK     *((volatile u8*)0x59)

#define TCNT0     *((volatile u8*)0x52)
#define TCCR0     *((volatile u8*)0x53)
#define OCR0      *((volatile u8*)0x5C)

#define TCCR1A    *((volatile u8*)0x4F)
#define TCCR1B    *((volatile u8*)0x4E)
#define TCCR1     *((volatile u16*)0x4E)
#define TCNT1H    *((volatile u8*)0x4D)
#define TCNT1L    *((volatile u8*)0x4C)
#define TCNT1     *((volatile u16*)0x4C)
#define OCR1AH    *((volatile u8*)0x4B)
#define OCR1AL    *((volatile u8*)0x4A)
#define OCR1A     *((volatile u16*)0x4A)
#define OCR1BH    *((volatile u8*)0x49)
#define OCR1BL    *((volatile u8*)0x48)
#define OCR1B     *((volatile u16*)0x48)
#define ICR1H     *((volatile u8*)0x47)
#define ICR1L     *((volatile u8*)0x46)
#define ICR1      *((volatile u16*)0x46)

#define TCNT2     *((volatile u8*)0x44)
#define TCCR2     *((volatile u8*)0x45)
#define OCR2      *((volatile u8*)0x43)

#define ASSR      *((volatile u8*)0x42)

#define NULL      '\0'

#define TIFR_TOV0         0
#define TIFR_OCF0         1
#define TIFR_TOV1         2
#define TIFR_OCF1B        3
#define TIFR_OCF1A        4
#define TIFR_ICF1         5
#define TIFR_TOV2         6
#define TIFR_OCF2         7

#define TIMSK_TOIE0       0
#define TIMSK_OCIE0       1
#define TIMSK_TOIE1       2
#define TIMSK_OCIE1B      3
#define TIMSK_OCIE1A      4
#define TIMSK_TICIE1      5
#define TIMSK_TOIE2       6
#define TIMSK_OCIE2       7

#define TCCR0_CS00        0
#define TCCR0_CS01        1
#define TCCR0_CS02        2
#define TCCR0_WGM01       3
#define TCCR0_COM00       4
#define TCCR0_COM01       5
#define TCCR0_WGM00       6
#define TCCR0_FOC0        7

#define TCCR1A_WGM10      0
#define TCCR1A_WGM11      1
#define TCCR1A_FOC1B      2
#define TCCR1A_FOC1A      3
#define TCCR1A_COM1B0     4
#define TCCR1A_COM1B1     5
#define TCCR1A_COM1A0     6
#define TCCR1A_COM1A1     7

#define TCCR1B_CS10       0
#define TCCR1B_CS11       1
#define TCCR1B_CS12       2
#define TCCR1B_WGM12      3
#define TCCR1B_WGM13      4
#define TCCR1B_ICES1      6
#define TCCR1B_ICNC1      7

#define TCCR2_CS20        0
#define TCCR2_CS21        1
#define TCCR2_CS22        2
#define TCCR2_WGM21       3
#define TCCR2_COM20       4
#define TCCR2_COM21       5
#define TCCR2_WGM20       6
#define TCCR2_FOC2        7

#define ASSR_AS2          3


#endif