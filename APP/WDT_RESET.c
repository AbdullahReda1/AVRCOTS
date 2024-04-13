#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "util/delay.h"

#include "../HAL/LED/LED_interface.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/WDT/WDT_interface.h"

LED_t LED1 ={DIO_PORT_D, PIN0};

void main(void)
{
    HLED_voidInit(&LED1);
	
    HLED_voidTurnOn(&LED1);
    _delay_ms(100);
    HLED_voidTurnOff(&LED1);
	
    MWDT_voidSleep(WDT_SLEEP_01_00_S);
    MWDT_voidEnable();
    while(1)
	{
		
	}
}