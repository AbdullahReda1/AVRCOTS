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

#ifndef HAL_TFT_TFT_PRIVATE_H_
#define HAL_TFT_TFT_PRIVATE_H_


#define DELAY                 0x80    // Used to introduce a delay in the program execution.
#define NOP                   0x00    // No operation command.
#define SWRESET               0x01    // Software reset command.
#define RDDID                 0x04    // Read display ID command.
#define RDDST                 0x09    // Read display status command.
#define SLPIN                 0x10    // Enter sleep mode command.
#define SLPOUT                0x11    // Exit sleep mode command.
#define PTLON                 0x12    // Partial mode on command.
#define NORON                 0x13    // Normal mode on command.
#define INVOFF                0x20    // Display inversion off command.
#define INVON                 0x21    // Display inversion on command.
#define DISPOFF               0x28    // Display off command.
#define DISPON                0x29    // Display on command.
#define RAMRD                 0x2E    // Memory read command.
#define CASET                 0x2A    // Column address set command.
#define RASET                 0x2B    // Row address set command.
#define RAMWR                 0x2C    // Memory write command.
#define PTLAR                 0x30    // Partial area set command.
#define MADCTL                0x36    // Memory data access control command.
#define COLMOD                0x3A    // Interface pixel format command.
#define FRMCTR1               0xB1    // Frame rate control (normal mode/full colors) command.
#define FRMCTR2               0xB2    // Frame rate control (idle mode/8-colors) command.
#define FRMCTR3               0xB3    // Frame rate control (partial mode/full colors) command.
#define INVCTR                0xB4    // Display inversion control command.
#define DISSET5               0xB6    // Display function setting command.
#define PWCTR1                0xC0    // Power control setting command 1.
#define PWCTR2                0xC1    // Power control setting command 2.
#define PWCTR3                0xC2    // Power control setting command 3.
#define PWCTR4                0xC3    // Power control setting command 4.
#define PWCTR5                0xC4    // Power control setting command 5.
#define VMCTR1                0xC5    // VCOM control 1 command.
#define RDID1                 0xDA    // Read ID1 command.
#define RDID2                 0xDB    // Read ID2 command.
#define RDID3                 0xDC    // Read ID3 command.
#define RDID4                 0xDD    // Read ID4 command.
#define GMCTRP1               0xE0    // Positive gamma correction setting command.
#define GMCTRN1               0xE1    // Negative gamma correction setting command.
#define PWCTR6                0xFC    // Power control setting command 6.

/* Constants */
#define HTFT_X0     0
#define HTFT_X1     127
#define HTFT_Y0     0
#define HTFT_Y1     159

#define ZERO_DATA   0


static void HTFT_voidSendData(u8 Copy_u8Data);
static void HTFT_voidSendCommand(u8 Copy_u8Commend);


#endif