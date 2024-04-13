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

#ifndef 	MCAL_ADC_ADC_config_H_
#define 	MCAL_ADC_ADC_config_H_


/*
    ORTIONS:
    RIGHT_ADJUST
    LEFT_ADJUST
*/
#define     ADC_ADJUST_RESULT       LEFT_ADJUST

/*
    ORTIONS:
    AREF
    AVCC
    INTERNAL_2v56
*/
#define     ADC_Reference_SELCTION       AVCC

/*
    ORTIONS:
    DIV_FACTOR_2
    DIV_FACTOR_4
    DIV_FACTOR_8
    DIV_FACTOR_16
    DIV_FACTOR_32
    DIV_FACTOR_64
    DIV_FACTOR_128
*/
#define     ADC_PRESCALER       DIV_FACTOR_64

/*
    ORTIONS:
    ENABLE
    DISABLE
*/
#define     ADC_INTERRUPT_STATUS      ENABLE

/*
    ORTIONS:
    ENABLE
    DISABLE
*/
#define         ADC_ENABLE              ENABLE


#endif