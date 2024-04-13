/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    28 MAR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          28 MAR, 2023     Abdullah R.Hebashi       Initial Creation    
***********************************************************/


#ifndef 		HAL_LED_LED_interface_H_
#define 		HAL_LED_LED_interface_H_


typedef struct {
	u8 LED_PORT;
	u8 LED_PIN;
}LED_t;

void HLED_voidInit(LED_t* Ledobj);
void HLED_voidTurnOn(LED_t* Ledobj);
void HLED_voidTurnOff(LED_t* Ledobj);
void HLED_voidToggle(LED_t* Ledobj);


#endif
