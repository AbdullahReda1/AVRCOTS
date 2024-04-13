#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../HAL/LCD/LCD_interface.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/Timer/Timer_interface.h"

void ICU_HW(void);

volatile u16 App_u16Reading1;
volatile u16 App_u16Reading2;
volatile u16 App_u16Reading3;
volatile u16 App_u16OnTicks = 0;
volatile u16 App_u16PeriodTicks = 0;

void main(void)
{
	MDIO_voidsetpindir(DIO_PORTB, PIN3, OUTPUT);
	MDIO_voidsetpindir(DIO_PORTD, PIN6, INPUT);
	HLCD_voidInit();
	MTIMER0_voidSetOCMatchValue(50);
	MTIMER0_voidInit();
	MICU_voidSetTriggerSignal(ICU_RISING_EDGE);
	MTIMER1_voidSetICUCallBack(&ICU_HW);
	MICU_voidInterruptControl(ICU_ENABLE);
	MGIE_voidEnableGlobalInterrupt();
	MTIMER1_voidInit();

	while (1)
	{
		while(App_u16OnTicks == 0 || App_u16PeriodTicks == 0);
		HLCD_voidGoToXY(1, 1);
		HLCD_voidSendString("P.T = ");
		HLCD_voidSendNumber(App_u16PeriodTicks);
		HLCD_voidGoToXY(2, 1);
		HLCD_voidSendString("O.T = ");
		HLCD_voidSendNumber(App_u16OnTicks);
	}
}

void ICU_HW(void)
{
	static u8 Local_u8Counter = 0;
	Local_u8Counter++;
	if(Local_u8Counter == 1)
	{
		App_u16Reading1 = MICU_u16GetICRRegister();
		MICU_voidSetTriggerSignal(ICU_FALLING_EDGE);
	}
	else if(Local_u8Counter == 2)
	{
		App_u16Reading2 = MICU_u16GetICRRegister();
		App_u16OnTicks = App_u16Reading2 - App_u16Reading1 - 1;
	}
	else if(Local_u8Counter == 3)
	{
		App_u16Reading3 = MICU_u16GetICRRegister();
		App_u16PeriodTicks = App_u16Reading3 - App_u16Reading2 - 1;
		MICU_voidInterruptControl(ICU_DISABLE);
		Local_u8Counter = 0;
	}
}