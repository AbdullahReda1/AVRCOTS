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


#ifndef 	MCAL_ADC_ADC_interface_H_
#define 	MCAL_ADC_ADC_interface_H_


#define     ADC_INTERRUPT_ENABLE                  1
#define     ADC_INTERRUPT_DISABLE                 0

#define     CHANNEL0                    0b00000000
#define     CHANNEL1                    0b00000001
#define     CHANNEL2                    0b00000010
#define     CHANNEL3                    0b00000011
#define     CHANNEL4                    0b00000100
#define     CHANNEL5                    0b00000101
#define     CHANNEL6                    0b00000110
#define     CHANNEL7                    0b00000111

void MADC_voidInit(void);
void MADC_voidInterruptControl(u8 Copy_u8InterruptStatus);
u8 MADC_u8StartConversionSynchronous(u8 Copy_u8ChannelNumber);
void MADC_voidADCSetCallback(void (*NotificationFunction)(void));
u8 MADC_u8StartConversionAsynchronous(u8 Copy_u8ChannelNumber, void (*NotificationFunction)(void));


#endif