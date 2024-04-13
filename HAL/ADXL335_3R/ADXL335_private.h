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


#ifndef HAL_ADXL335_ADXL335_private_H_
#define HAL_ADXL335_ADXL335_private_H_


#define RAWMIN_GS      0
#define RAWMAX_GS      1023
#define RAWMIN_ANG     265
#define RAWMAX_ANG     402

#define CHANNEL0       0b00000000
#define CHANNEL1       0b00000001
#define CHANNEL2       0b00000010
#define CHANNEL3       0b00000011
#define CHANNEL4       0b00000100
#define CHANNEL5       0b00000101
#define CHANNEL6       0b00000110
#define CHANNEL7       0b00000111


s32 map(s32 Reading, s32 in_min, s32 in_max, s32 out_min, s32 out_max);


#endif