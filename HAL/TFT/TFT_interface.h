/********************************************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:        27 APR, 2023
 * Version:              v1.0
 * Compiler:             GNU GCC
*********************************************************************************/
/********************************************************************************
 * Version      Date                  Author                    Description
 * v1.0         27 APR, 2023          Abdullah R.Hebashi        Initial Creation    
*********************************************************************************/

#ifndef HAL_TFT_TFT_INTERFACE_H_
#define HAL_TFT_TFT_INTERFACE_H_


/* Colors to fill */
#define BLACK                 0x0000
#define WHITE                 0xFFFF
#define RED                   0xF000
#define GREEN                 0x07E0
#define BLUE                  0x001F
#define CYAN                  0x07FF
#define MAGENTA               0xF81F
#define YELLOW                0xFFE0
#define ORANGE                0xFD20
#define PURPLE                0xF10F
#define PINK                  0xFE19

/* Features */
#define MADCTL_MY             0x80    // Mirror Y.
#define MADCTL_MX             0x40    // Mirror X.
#define MADCTL_MV             0x20    // Swap XY.
#define MADCTL_ML             0x10    // Scan bottom-top.
#define MADCTL_RGB            0x00    // RGB color format.
#define MADCTL_BGR            0x08    // BGR color format.
#define MADCTL_MH             0x04    // Mirror display horizontally.
#define MADCTL_VERT           0xC0    // Vertical rotation (Portrait mode)

/* Color mode */
#define COLMOD_RGB444_12BIT   0x03    // 12-bit (RGB 4-4-4)
#define COLMOD_RGB565_16BIT   0x05    // 16-bit (RGB 5-6-5)
#define COLMOD_RGB666_18BIT   0x06    // 18-bit (RGB 6-6-6)


void HTFT_voidInit(void);

void HTFT_voidFillColor(u16 Copy_u16Color);

void HTFT_voidSetWindow(u8 Copy_u8X0, u8 Copy_u8X1, u8 Copy_u8Y0, u8 Copy_u8Y1);

void HTFT_voidDrawPixel(u8 Copy_u8XCoordinate, u8 Copy_u8YCoordinate, u16 Copy_u16Color);

void HTFT_voidFillRect(u8 Copy_u8X0, u8 Copy_u8X1, u8 Copy_u8Y0, u8 Copy_u8Y1, u16 Copy_u16Color);

void HTFT_voidDrawHorizontalLine(u8 Copy_u8X0, u8 Copy_u8X1, u8 Copy_u8Y, u16 Copy_u16Color);

void HTFT_voidDrawVerticalLine(u8 Copy_u8X, u8 Copy_u8Y0, u8 Copy_u8Y1, u16 Copy_u16Color);

void HTFT_voidDisplayImage(void);

void HTFT_voidWriteChar(u8 *Copy_pu8Char, u8 Copy_u8Xaxis, u8 Copy_u8Yaxis, u16 Copy_u16Color);

void HTFT_voidSetColorMode(u8 Copy_u8Mode);

void HTFT_voidSetFeature(u8 Copy_u8Feature);

void HTFT_voidContentHide(void);


#endif