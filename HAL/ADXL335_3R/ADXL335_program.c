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


#include <math.h>
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/ADC/ADC_interface.h"

#include "ADXL335_interface.h"
#include "ADXL335_private.h"
#include "ADXL335_config.h"


const float RAD_TO_DEG = 57.295779513082320876798154814105f;
const float PI = 3.1415926535897932384626433832795f;


void HADXL335_voidInit(void)
{
    MADC_voidInit();
}

s32 map(s32 Reading, s32 in_min, s32 in_max, s32 out_min, s32 out_max)
{
  return (((Reading - in_min) * (out_max - out_min)) / (in_max - in_min)) + out_min;
}

s8 HADXL335_s8GetXAcceleration(void)
{
    return ((map(MADC_u8StartConversionSynchronous(X_CHANNEL), RAWMIN_GS, RAWMAX_GS, -3000, 3000))/1000.0);
}

s8 HADXL335_s8GetYAcceleration(void)
{
    return ((map(MADC_u8StartConversionSynchronous(Y_CHANNEL), RAWMIN_GS, RAWMAX_GS, -3000, 3000))/1000.0);
}

s8 HADXL335_s8GetZAcceleration(void)
{
    return ((map(MADC_u8StartConversionSynchronous(Z_CHANNEL), RAWMIN_GS, RAWMAX_GS, -3000, 3000))/1000.0);
}

u8 HADXL335_u8GetTotalAcceleration(void)
{
    s8 Local_s8XReading, Local_s8YReading, Local_s8ZReading;
    u8 Local_u8TotalReading;
    Local_s8XReading = HADXL335_s8GetXAcceleration();
    Local_s8YReading = HADXL335_s8GetYAcceleration();
    Local_s8ZReading = HADXL335_s8GetZAcceleration();
    Local_u8TotalReading = sqrt(pow(Local_s8XReading, 2) + pow(Local_s8YReading, 2) + pow(Local_s8ZReading, 2));
    return Local_u8TotalReading;
}

f64 HADXL335_f64GetXAngle(void)
{
    u32 Local_u32YReading, Local_u32ZReading;
    f64 Local_f64XAngle;
    Local_u32YReading = map(MADC_u8StartConversionSynchronous(Y_CHANNEL), RAWMIN_ANG, RAWMAX_ANG, -90, 90);
    Local_u32ZReading = map(MADC_u8StartConversionSynchronous(Z_CHANNEL), RAWMIN_ANG, RAWMAX_ANG, -90, 90);
    Local_f64XAngle = RAD_TO_DEG * (atan2(-Local_u32YReading, -Local_u32ZReading) + PI);
    return Local_f64XAngle;
}

f64 HADXL335_f64GetYAngle(void)
{
    u32 Local_u32XReading, Local_u32ZReading;
    f64 Local_f64YAngle;
    Local_u32XReading = map(MADC_u8StartConversionSynchronous(X_CHANNEL), RAWMIN_ANG, RAWMAX_ANG, -90, 90);
    Local_u32ZReading = map(MADC_u8StartConversionSynchronous(Z_CHANNEL), RAWMIN_ANG, RAWMAX_ANG, -90, 90);
    Local_f64YAngle = RAD_TO_DEG * (atan2(-Local_u32XReading, -Local_u32ZReading) + PI);
    return Local_f64YAngle;
}

f64 HADXL335_f64GetZAngle(void)
{
    u32 Local_u32XReading, Local_u32YReading;
    f64 Local_f64ZAngle;
    Local_u32XReading = map(MADC_u8StartConversionSynchronous(X_CHANNEL), RAWMIN_ANG, RAWMAX_ANG, -90, 90);
    Local_u32YReading = map(MADC_u8StartConversionSynchronous(Y_CHANNEL), RAWMIN_ANG, RAWMAX_ANG, -90, 90);
    Local_f64ZAngle = RAD_TO_DEG * (atan2(-Local_u32YReading, -Local_u32XReading) + PI);
    return Local_f64ZAngle;
}