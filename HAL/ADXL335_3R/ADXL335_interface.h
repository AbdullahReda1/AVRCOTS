/**************************************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:        28 MAR, 2023
 * Version:              v1.0
 * Compiler:             GNU GCC
 **************************************************************************/
/**************************************************************************
 * Version      Date             Author                   Description
 * v1.0         28 MAR, 2023     Abdullah R.Hebashi       Initial Creation    
***************************************************************************/


#ifndef HAL_ADXL335_ADXL335_interface_H_
#define HAL_ADXL335_ADXL335_interface_H_


void HADXL335_voidInit(void);

s8 HADXL335_s8GetXAcceleration(void);
s8 HADXL335_s8GetYAcceleration(void);
s8 HADXL335_s8GetZAcceleration(void);

u8 HADXL335_u8GetTotalAcceleration(void);

f64 HADXL335_f64GetXAngle(void);
f64 HADXL335_f64GetYAngle(void);
f64 HADXL335_f64GetZAngle(void);


#endif