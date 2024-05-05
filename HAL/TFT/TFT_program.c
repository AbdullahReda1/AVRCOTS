/********************************************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:        27 APR, 2023
 * Version:              v1.0
 * Compiler:             GNU GCC
*********************************************************************************/
/********************************************************************************
 * Version      Date                  Author                    Description
 * v1.0         27 APR, 2023          Abdullah R.Hebashi        Initial Creation
 * v2.0         5  MAY, 2024          Abdullah R.Hebashi        Adding functions started by ellipse
*********************************************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/SPI/SPI_interface.h"

#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"

#include "../../Services/ImageArray.h"


void HTFT_voidInit(void)
{
	/* Reset pin, A0 (D/!C) */
	MDIO_voidsetpindir(HTFT_A0_PORT, HTFT_A0_PIN, OUTPUT);
	MDIO_voidsetpindir(HTFT_RESET_PORT, HTFT_RESET_PIN, OUTPUT);

	/* MOSI, SCK, SS */
	MDIO_voidSPIMasterConfig();

	MSPI_voidMasterInit();

	/* Reset Puls To Initializing All registers */
	MDIO_voidsetpinval(HTFT_RESET_PORT, HTFT_RESET_PIN, HIGH);
    _delay_us(100);
    MDIO_voidsetpinval(HTFT_RESET_PORT, HTFT_RESET_PIN, LOW);
    _delay_us(1);
    MDIO_voidsetpinval(HTFT_RESET_PORT, HTFT_RESET_PIN, HIGH);
    _delay_us(100);
    MDIO_voidsetpinval(HTFT_RESET_PORT, HTFT_RESET_PIN, LOW);
    _delay_us(100);
    MDIO_voidsetpinval(HTFT_RESET_PORT, HTFT_RESET_PIN, HIGH);
    _delay_us(120000);

	/* Sleep it out and Active 4-Line MCU serial interface mode then display on */
	HTFT_voidSendCommand(SLPOUT);
	_delay_us(150000);
	HTFT_voidSendCommand(COLMOD);
	HTFT_voidSendData(COLMOD_RGB565_16BIT);
	HTFT_voidSendCommand(DISPON);
	_delay_us(1000);
	HTFT_voidSendCommand(MADCTL);
	HTFT_voidSendData(PWCTR1);
}

static void HTFT_voidSendData(u8 Copy_u8Data) 
{
	u8 Local_u8DummyData;
	MDIO_voidsetpinval(HTFT_A0_PORT, HTFT_A0_PIN, HIGH);
	MDIO_voidsetpinval(DIO_PORTB, PIN4, LOW);
	Local_u8DummyData = MSPI_u8SendReceive(Copy_u8Data);
	MDIO_voidsetpinval(DIO_PORTB, PIN4, HIGH);
}

static void HTFT_voidSendCommand(u8 Copy_u8Command) 
{
	u8 Local_u8DummyData;
	MDIO_voidsetpinval(HTFT_A0_PORT, HTFT_A0_PIN, LOW);
	MDIO_voidsetpinval(DIO_PORTB, PIN4, LOW);
	Local_u8DummyData = MSPI_u8SendReceive(Copy_u8Command);
	MDIO_voidsetpinval(DIO_PORTB, PIN4, HIGH);
}

void HTFT_voidFillColor(u16 Copy_u16Color)
{
	u8 Local_u8XCounter;
	u8 Local_u8YCounter;

	for (Local_u8YCounter = 0 ; Local_u8YCounter < 160; Local_u8YCounter++)
	{
		HTFT_voidSendCommand(CASET);
		HTFT_voidSendData(ZERO_DATA);
		HTFT_voidSendData(ZERO_DATA);
		HTFT_voidSendCommand(RASET);
		HTFT_voidSendData(ZERO_DATA);
		HTFT_voidSendData(Local_u8YCounter);
		HTFT_voidSendCommand(RAMWR);
		for (Local_u8XCounter = 0; Local_u8XCounter < 128; Local_u8XCounter++)
		{
			HTFT_voidSendData(Copy_u16Color >> 8);
			HTFT_voidSendData(Copy_u16Color & 0xFF);
		}
	}
}

void HTFT_voidSetWindow(u8 Copy_u8X0, u8 Copy_u8X1, u8 Copy_u8Y0, u8 Copy_u8Y1)
{
    HTFT_voidSendCommand(CASET);
    HTFT_voidSendData(ZERO_DATA);
    HTFT_voidSendData(Copy_u8X0);
    HTFT_voidSendData(ZERO_DATA);
    HTFT_voidSendData(Copy_u8X1);
	
    HTFT_voidSendCommand(RASET);
    HTFT_voidSendData(ZERO_DATA);
    HTFT_voidSendData(Copy_u8Y0);
    HTFT_voidSendData(ZERO_DATA);
    HTFT_voidSendData(Copy_u8Y1);
}

void HTFT_voidDrawPixel(u8 Copy_u8XCoordinate, u8 Copy_u8YCoordinate, u16 Copy_u16Color)
{
	HTFT_voidSetWindow(Copy_u8XCoordinate, Copy_u8XCoordinate, Copy_u8YCoordinate, Copy_u8YCoordinate);
	HTFT_voidSendCommand(RAMWR);
	HTFT_voidSendData(Copy_u16Color>>8);
	HTFT_voidSendData((u8)Copy_u16Color);
}

void HTFT_voidFillRect(u8 Copy_u8X0, u8 Copy_u8X1, u8 Copy_u8Y0, u8 Copy_u8Y1, u16 Copy_u16Color)
{
	u32 Local_u32LoopCounter = 0;
	u8 Local_u8Width  = Copy_u8X1 - Copy_u8X0;
	u8 Local_u8Height = Copy_u8Y1 - Copy_u8Y0;
	u16 Local_u16Area = Local_u8Width * Local_u8Height;
	HTFT_voidSetWindow(Copy_u8X0, Copy_u8X1, Copy_u8Y0, Copy_u8Y1);
    HTFT_voidSendCommand(RAMWR);
    for (Local_u32LoopCounter = 0; Local_u32LoopCounter < (Local_u16Area + 8); Local_u32LoopCounter++)
    {
    	HTFT_voidSendData(Copy_u16Color >> 8);
    	HTFT_voidSendData((u8)Copy_u16Color);
    }
}

void HTFT_voidDrawHorizontalLine(u8 Copy_u8X0, u8 Copy_u8X1, u8 Copy_u8Y, u16 Copy_u16Color)
{
	u8 Local_u8LoopCounter = 0;
	u8 Local_u8Length  = Copy_u8X1 - Copy_u8X0 + 1;
	HTFT_voidSetWindow(Copy_u8X0, Copy_u8X1, Copy_u8Y, Copy_u8Y);
    HTFT_voidSendCommand(RAMWR);
    for(Local_u8LoopCounter = 0; Local_u8LoopCounter < Local_u8Length; Local_u8LoopCounter++)
    {
    	HTFT_voidSendData(Copy_u16Color >> 8);
    	HTFT_voidSendData((u8)Copy_u16Color);
    }
}

void HTFT_voidDrawVerticalLine(u8 Copy_u8X, u8 Copy_u8Y0, u8 Copy_u8Y1, u16 Copy_u16Color)
{
	u32 Local_u32LoopCounter = 0;
	u8 Local_u8Length  = Copy_u8Y1 - Copy_u8Y0 + 1;
	HTFT_voidSetWindow(Copy_u8X, Copy_u8X, Copy_u8Y0, Copy_u8Y1);
    HTFT_voidSendCommand(RAMWR);
    for(Local_u32LoopCounter = 0; Local_u32LoopCounter < Local_u8Length; Local_u32LoopCounter++)
    {
    	HTFT_voidSendData(Copy_u16Color >> 8);
    	HTFT_voidSendData((u8)Copy_u16Color);
    }
}

void HTFT_voidDisplayImage(void)
{
	HTFT_voidSetWindow(HTFT_X0, HTFT_X1, HTFT_Y0, HTFT_Y1);
    HTFT_voidSendCommand(RAMWR);
    u16 Local_u16LoopCounter;
    u8 Local_u8Data = 0;
    for (Local_u16LoopCounter=0; Local_u16LoopCounter <= IMAGE_SIZE; Local_u16LoopCounter++)
    {
    	Local_u8Data = Image_Array[Local_u16LoopCounter] >> 8;
    	HTFT_voidSendData(Local_u8Data);
    	Local_u8Data = (u8) Image_Array[Local_u16LoopCounter];
    	HTFT_voidSendData(Local_u8Data);
    }
}

void HTFT_voidWriteChar(u8 *Copy_pu8Char, u8 Copy_u8Xaxis, u8 Copy_u8Yaxis, u16 Copy_u16Color)
{
	u8 Local_u8Mask = DELAY;
	u8 Local_u8Iterator1;
	u8 Local_u8Iterator2;
	u8 Local_u8DataMasked;
	u16 Local_u16Pixel;

	for (Local_u8Iterator1 = 0; Local_u8Iterator1 < 5; Local_u8Iterator1++)
	{
		for (Local_u8Iterator2 = 0; Local_u8Iterator2 < 7; Local_u8Iterator2++)
		{
			HTFT_voidSendCommand(CASET);
			HTFT_voidSendData(Copy_u8Xaxis + Local_u8Iterator1);
			HTFT_voidSendData(Copy_u8Xaxis + Local_u8Iterator1);
			HTFT_voidSendCommand(RASET);
			HTFT_voidSendData(Copy_u8Yaxis + Local_u8Iterator2);
			HTFT_voidSendData(Copy_u8Yaxis + Local_u8Iterator2);
			HTFT_voidSendCommand(RAMWR);
			Local_u8DataMasked = Copy_pu8Char[Local_u8Iterator1] & Local_u8Mask;
			if(Local_u8DataMasked == 0)
			{
				Local_u16Pixel = 0x0000; 
			}
			else
			{
				Local_u16Pixel = Copy_u16Color; 
			}
			HTFT_voidSendData(Local_u16Pixel >> 8);
			HTFT_voidSendData(Local_u16Pixel & 0xFF);
			Local_u8Mask >>= 1;
		}
		Local_u8Mask = 0x80;
	}
}

void HTFT_voidSetColorMode(u8 Copy_u8Mode)
{
	HTFT_voidSendCommand(COLMOD);
	HTFT_voidSendData(Copy_u8Mode);
}

void HTFT_voidSetFeature(u8 Copy_u8Feature)
{
	HTFT_voidSendCommand(MADCTL);
	HTFT_voidSendData(Copy_u8Feature);
}

void HTFT_voidContentHide(void)
{
	HTFT_voidSendCommand(DISPOFF);
}

void HTFT_voidDrawEllipse(u8 Copy_u8X0, u8 Copy_u8Y0, u8 Copy_u8RadiusX, u8 Copy_u8RadiusY, u16 Copy_u16Color)
{
	s32 Local_s32XPos, Local_s32YPos;
	f32 Local_f32Theta;
	f32 Local_f32DeltaTheta = 0.01;

	for (Local_f32Theta = 0; Local_f32Theta < (2 * M_PI); Local_f32Theta += Local_f32DeltaTheta)
	{
		Local_s32XPos = Copy_u8X0 + Copy_u8RadiusX * cos(Local_f32Theta);
		Local_s32YPos = Copy_u8Y0 + Copy_u8RadiusY * sin(Local_f32Theta);

		HTFT_voidDrawPixel(Local_s32XPos, Local_s32YPos, Copy_u16Color);
	}
}

static void vSwap(s32* Copy_ps32Variable1, s32* Copy_ps32Variable2)
{
	s32 Local_s32TempVar = *Copy_ps32Variable1;
	*Copy_ps32Variable1  = *Copy_ps32Variable2;
	*Copy_ps32Variable2  =  Local_s32TempVar;
}

void HTFT_voidFillTriangle(u8 Copy_u8X0, u8 Copy_u8Y0, u8 Copy_u8X1, u8 Copy_u8Y1, u8 Copy_u8X2, u8 Copy_u8Y2, u16 Copy_u16Color)
{
	if (Copy_u8Y0 > Copy_u8Y1)
	{
		vSwap(&Copy_u8Y0, &Copy_u8Y1);
		vSwap(&Copy_u8X0, &Copy_u8X1);
	}
	if (Copy_u8Y0 > Copy_u8Y2)
	{
		vSwap(&Copy_u8Y0, &Copy_u8Y2);
		vSwap(&Copy_u8X0, &Copy_u8X2);
	}
	if (Copy_u8Y1 > Copy_u8Y2)
	{
		vSwap(&Copy_u8Y1, &Copy_u8Y2);
		vSwap(&Copy_u8X1, &Copy_u8X2);
	}

	s32 Local_s32TotalHeight = Copy_u8Y2 - Copy_u8Y0;

	for (s32 Local_s32OuterIterator = 0; Local_s32OuterIterator < Local_s32TotalHeight; Local_s32OuterIterator++)
	{
		u8 Local_u8LowerHalf = Local_s32OuterIterator > Copy_u8Y1 - Copy_u8Y0 || Copy_u8Y1 == Copy_u8Y0;
		s32 Local_s32SegmentHeight = Local_u8LowerHalf ? (Copy_u8Y2 - Copy_u8Y1) : (Copy_u8Y1 - Copy_u8Y0);

		f32 Local_f32Alpha = (f32)Local_s32OuterIterator / Local_s32TotalHeight;
		f32 Local_f32Beta  = (f32)(Local_s32OuterIterator - (Local_u8LowerHalf ? Copy_u8Y1 - Copy_u8Y0 : 0)) / Local_s32SegmentHeight;

		s32 Local_s32StartXPos = Copy_u8X0 + (Copy_u8X2 - Copy_u8X0) * Local_f32Alpha;
		s32 Local_s32EndXPos   = Local_u8LowerHalf ? Copy_u8X1 + (Copy_u8X2 - Copy_u8X1) * Local_f32Beta : Copy_u8X0 + (Copy_u8X1 - Copy_u8X0) * Local_f32Beta;

		if (Local_s32StartXPos > Local_s32EndXPos)
		{
			vSwap(&Local_s32StartXPos, &Local_s32EndXPos);
		}

		for (s32 Local_s32InnerIterator = Local_s32StartXPos; Local_s32InnerIterator < Local_s32EndXPos; Local_s32InnerIterator++)
		{
			HTFT_voidDrawPixel(Local_s32InnerIterator, Copy_u8Y0 + Local_s32OuterIterator, Copy_u16Color);
		}
	}
}

void HTFT_voidDrawLine(u8 Copy_u8X0, u8 Copy_u8Y0, u8 Copy_u8X1, u8 Copy_u8Y1, u16 Copy_u16Color)
{
	/* Bresenham's line algorithm */
	s32 Local_s32DeltaX = abs(Copy_u8X1 - Copy_u8X0), Local_s32Sx = Copy_u8X0 < Copy_u8X1 ? 1 : -1;
	s32 Local_s32DeltaY = abs(Copy_u8Y1 - Copy_u8Y0), Local_s32Sy = Copy_u8Y0 < Copy_u8Y1 ? 1 : -1;
	s32 Local_s32Error = (Local_s32DeltaX > Local_s32DeltaY ? Local_s32DeltaX : -Local_s32DeltaY) / 2, Local_s32Error2;

	while (1)
	{
		HTFT_voidDrawPixel(Copy_u8X0, Copy_u8Y0, Copy_u16Color);
		if (Copy_u8X0 == Copy_u8X1 && Copy_u8Y0 == Copy_u8Y1) break;
		Local_s32Error2 = Local_s32Error;
		if (Local_s32Error2 > -Local_s32DeltaX) { Local_s32Error -= Local_s32DeltaY; Copy_u8X0 += Local_s32Sx; }
		if (Local_s32Error2 <  Local_s32DeltaY) { Local_s32Error += Local_s32DeltaX; Copy_u8Y0 += Local_s32Sy; }
    }
}

void HTFT_voidDrawTriangle(u8 Copy_u8X0, u8 Copy_u8Y0, u8 Copy_u8X1, u8 Copy_u8Y1, u8 Copy_u8X2, u8 Copy_u8Y2, u16 Copy_u16Color)
{
	HTFT_voidDrawLine(Copy_u8X0, Copy_u8Y0, Copy_u8X1, Copy_u8Y1, Copy_u16Color);
	HTFT_voidDrawLine(Copy_u8X1, Copy_u8Y1, Copy_u8X2, Copy_u8Y2, Copy_u16Color);
	HTFT_voidDrawLine(Copy_u8X2, Copy_u8Y2, Copy_u8X0, Copy_u8Y0, Copy_u16Color);
}

void HTFT_voidFillCircle(u8 Copy_u8X0, u8 Copy_u8Y0, u8 Copy_u8Radius, u16 Copy_u16Color)
{
	s32 Local_s32XPos = Copy_u8Radius - 1;
	s32 Local_s32YPos = 0;
	s32 Local_s32DeltaX = 1;
	s32 Local_s32DeltaY = 1;
	s32 Local_s32Error = Local_s32DeltaX - (Copy_u8Radius << 1);

	while (Local_s32XPos >= Local_s32YPos)
	{
		HTFT_voidDrawHorizontalLine(Copy_u8X0 - Local_s32XPos, Copy_u8X0 + Local_s32XPos, Copy_u8Y0 + Local_s32YPos, Copy_u16Color);
		HTFT_voidDrawHorizontalLine(Copy_u8X0 - Local_s32XPos, Copy_u8X0 + Local_s32XPos, Copy_u8Y0 - Local_s32YPos, Copy_u16Color);
		HTFT_voidDrawHorizontalLine(Copy_u8X0 - Local_s32YPos, Copy_u8X0 + Local_s32YPos, Copy_u8Y0 + Local_s32XPos, Copy_u16Color);
		HTFT_voidDrawHorizontalLine(Copy_u8X0 - Local_s32YPos, Copy_u8X0 + Local_s32YPos, Copy_u8Y0 - Local_s32XPos, Copy_u16Color);

		HTFT_voidDrawVerticalLine(Copy_u8X0 - Local_s32YPos, Copy_u8Y0 + Local_s32XPos, Copy_u8Y0 - Local_s32XPos, Copy_u16Color);
		HTFT_voidDrawVerticalLine(Copy_u8X0 + Local_s32YPos, Copy_u8Y0 + Local_s32XPos, Copy_u8Y0 - Local_s32XPos, Copy_u16Color);
		HTFT_voidDrawVerticalLine(Copy_u8X0 - Local_s32XPos, Copy_u8Y0 + Local_s32YPos, Copy_u8Y0 - Local_s32YPos, Copy_u16Color);
		HTFT_voidDrawVerticalLine(Copy_u8X0 + Local_s32XPos, Copy_u8Y0 + Local_s32YPos, Copy_u8Y0 - Local_s32YPos, Copy_u16Color);

		if (Local_s32Error <= 0)
		{
			Local_s32YPos++;
			Local_s32Error += Local_s32DeltaY;
			Local_s32DeltaY += 2;
		}

		if (Local_s32Error > 0)
		{
			Local_s32XPos--;
			Local_s32DeltaX += 2;
			Local_s32Error += Local_s32DeltaX - (Copy_u8Radius << 1);
		}
	}
}

void HTFT_voidDrawCircle(u8 Copy_u8X0, u8 Copy_u8Y0, u8 Copy_u8Radius, u16 Copy_u16Color)
{
	s32 Local_s32XPos = Copy_u8Radius - 1;
	s32 Local_s32YPos = 0;
	s32 Local_s32DeltaX = 1;
	s32 Local_s32DeltaY = 1;
	s32 Local_s32Error = Local_s32DeltaX - (Copy_u8Radius << 1);

	while (Local_s32XPos >= Local_s32YPos)
	{
		HTFT_voidDrawPixel(Copy_u8X0 + Local_s32XPos, Copy_u8Y0 + Local_s32YPos, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u8X0 + Local_s32YPos, Copy_u8Y0 + Local_s32XPos, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u8X0 - Local_s32YPos, Copy_u8Y0 + Local_s32XPos, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u8X0 - Local_s32XPos, Copy_u8Y0 + Local_s32YPos, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u8X0 - Local_s32XPos, Copy_u8Y0 - Local_s32YPos, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u8X0 - Local_s32YPos, Copy_u8Y0 - Local_s32XPos, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u8X0 + Local_s32YPos, Copy_u8Y0 - Local_s32XPos, Copy_u16Color);
		HTFT_voidDrawPixel(Copy_u8X0 + Local_s32XPos, Copy_u8Y0 - Local_s32YPos, Copy_u16Color);

		if (Local_s32Error <= 0)
		{
			Local_s32YPos++;
			Local_s32Error += Local_s32DeltaY;
			Local_s32DeltaY += 2;
		}

		if (Local_s32Error > 0)
		{
			Local_s32XPos--;
			Local_s32DeltaX += 2;
			Local_s32Error += Local_s32DeltaX - (Copy_u8Radius << 1);
		}
	}
}

void HTFT_voidFillCrescentMoon(u8 Copy_u8X0, u8 Copy_u8Y0, u8 Copy_u8Radius, u16 Copy_u16Color)
{
	s32 Local_s32XPos = Copy_u8Radius - 1;
	s32 Local_s32YPos = 0;
	s32 Local_s32DeltaX = 1;
	s32 Local_s32DeltaY = 1;
	s32 Local_s32Error = Local_s32DeltaX - (Copy_u8Radius << 1);

	while (Local_s32XPos >= Local_s32YPos)
	{
		HTFT_voidFillRect(Copy_u8X0 - Local_s32XPos, Copy_u8X0 + Local_s32XPos, Copy_u8Y0 + Local_s32YPos, Copy_u8Y0 + Local_s32YPos, Copy_u16Color);
		HTFT_voidFillRect(Copy_u8X0 - Local_s32XPos, Copy_u8X0 + Local_s32XPos, Copy_u8Y0 - Local_s32YPos, Copy_u8Y0 - Local_s32YPos, Copy_u16Color);
		HTFT_voidFillRect(Copy_u8X0 - Local_s32YPos, Copy_u8X0 + Local_s32YPos, Copy_u8Y0 + Local_s32XPos, Copy_u8Y0 + Local_s32XPos, Copy_u16Color);
		HTFT_voidFillRect(Copy_u8X0 - Local_s32YPos, Copy_u8X0 + Local_s32YPos, Copy_u8Y0 - Local_s32XPos, Copy_u8Y0 - Local_s32XPos, Copy_u16Color);

		if (Local_s32Error <= 0)
		{
			Local_s32YPos++;
			Local_s32Error += Local_s32DeltaY;
			Local_s32DeltaY += 2;
		}

		if (Local_s32Error > 0)
		{
			Local_s32XPos--;
			Local_s32DeltaX += 2;
			Local_s32Error += Local_s32DeltaX - (Copy_u8Radius << 1);
		}
	}
}