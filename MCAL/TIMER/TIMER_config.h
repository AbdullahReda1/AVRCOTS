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

#ifndef 	MCAL_TIMER_TIMER_config_H_
#define 	MCAL_TIMER_TIMER_config_H_


/************************* TIMER0 *****************************/

/*
    ORTIONS:
    TIMER0_NORMAL_MODE                    
    TIMER0_PHASE_CORRECT_PWM_MODE                       
    TIMER0_CTC_MODE                       
    TIMER0_FAST_PWM_MODE
*/
#define     TIMER0_MODE_SEL       TIMER0_FAST_PWM_MODE

/*
    ORTIONS:
    NORMAL_OC0_DISCONNECTED
    TOG_OC0_ON_COMPARE_MATCH    ->  Only for Non PWM mode (NORMAL, CTC).
    CLR_OC0_ON_COMPARE_MATCH
    SET_OC0_ON_COMPARE_MATCH
*/
#define     TIMER0_OUTPUT_COMPARE_SEL       CLR_OC0_ON_COMPARE_MATCH

/*
    ORTIONS:
    TIMER0_STOP             
    DIV_FACTOR_1            
    DIV_FACTOR_8            
    DIV_FACTOR_64           
    DIV_FACTOR_256          
    DIV_FACTOR_1024         
    EXT_CLK_FALLING_T0         
    EXT_CLK_RISING_T0        
*/
#define     TIMER0_CLK_SEL       DIV_FACTOR_8

/************************* TIMER1 *****************************/

/*
    ORTIONS:
    NORMAL_OC1A_DISCONNECTED
    TOG_OC1A_ON_COMPARE_MATCH    ->  Only for Non PWM mode (NORMAL, CTC).
    CLR_OC1A_ON_COMPARE_MATCH
    SET_OC1A_ON_COMPARE_MATCH
*/
#define     TIMER1_OC1A_OUTPUT_COMPARE_SEL       CLR_OC1A_ON_COMPARE_MATCH

/*
    ORTIONS:
    NORMAL_OC1B_DISCONNECTED
    TOG_OC1B_ON_COMPARE_MATCH    ->  Only for Non PWM mode (NORMAL, CTC).
    CLR_OC1B_ON_COMPARE_MATCH
    SET_OC1B_ON_COMPARE_MATCH
*/
#define     TIMER1_OC1B_OUTPUT_COMPARE_SEL       NORMAL_OC1B_DISCONNECTED

/*
    ORTIONS:
    TIMER1_STOP             
    DIV_FACTOR_1            
    DIV_FACTOR_8            
    DIV_FACTOR_64           
    DIV_FACTOR_256          
    DIV_FACTOR_1024         
    EXT_CLK_FALLING_T1         
    EXT_CLK_RISING_T1        
*/
#define     TIMER1_CLK_SEL       DIV_FACTOR_64

/*
    ORTIONS:
    TIMER1_NORMAL_MODE      
    TIMER1_PHASE_CORRECT_PWM_8_BIT_MODE
    TIMER1_PHASE_CORRECT_PWM_9_BIT_MODE
    TIMER1_PHASE_CORRECT_PWM_10_BIT_MODE
    TIMER1_CTC_OCR1A_MODE
    TIMER1_FAST_PWM_8_BIT_MODE
    TIMER1_FAST_PWM_9_BIT_MODE
    TIMER1_FAST_PWM_10_BIT_MODE
    TIMER1_PHASE_FREQ_CORRECT_PWM_ICR1_MODE
    TIMER1_PHASE_FREQ_CORRECT_PWM_OCR1A_MODE
    TIMER1_PHASE_CORRECT_PWM_ICR1_MODE
    TIMER1_PHASE_CORRECT_PWM_OCR1A_MODE
    TIMER1_CTC_ICR1_MODE
    TIMER1_FAST_PWM_ICR1_MODE
    TIMER1_FAST_PWM_OCR1A_MODE
*/
#define     TIMER1_MODE_SEL       TIMER1_CTC_OCR1A_MODE

/************************* TIMER2 *****************************/

/*
    ORTIONS:
    TIMER2_NORMAL_MODE                    
    TIMER2_PHASE_CORRECT_PWM_MODE                       
    TIMER2_CTC_MODE                       
    TIMER2_FAST_PWM_MODE
*/
#define     TIMER2_MODE_SEL       TIMER2_FAST_PWM_MODE

/*
    ORTIONS:
    NORMAL_OC2_DISCONNECTED
    TOG_OC2_ON_COMPARE_MATCH    ->  Only for Non PWM mode (NORMAL, CTC).
    CLR_OC2_ON_COMPARE_MATCH
    SET_OC2_ON_COMPARE_MATCH
*/
#define     TIMER2_OUTPUT_COMPARE_SEL       CLR_OC2_ON_COMPARE_MATCH

/*
    ORTIONS:
    TIMER2_STOP             
    DIV_FACTOR_1            
    DIV_FACTOR_8            
    DIV_FACTOR_32         
    DIV_FACTOR_64         
    DIV_FACTOR_128    ->  Must used for "OSC" selection in "TIMER2_ASYNCHRONOUS_STATUS".  
    DIV_FACTOR_256          
    DIV_FACTOR_1024       
*/
#define     TIMER2_CLK_SEL       DIV_FACTOR_128

/*
    ORTIONS:
    CLK     ->  For all prescaler sellections(0/1/8/32/64/128/256/1024), To enable internal MC clk.
    OSC     ->  For ONLY (128) prescaler sellection, To enable external crystal oscillator clock.
*/
#define     TIMER2_ASYNCHRONOUS_STATUS       OSC


#endif