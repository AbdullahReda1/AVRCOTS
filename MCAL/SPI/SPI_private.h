/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    17 APR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          17 APR, 2023     Abdullah R.Hebashi       Initial Creation
***********************************************************/


#ifndef 	MCAL_SPI_SPI_private_H_
#define 	MCAL_SPI_SPI_private_H_


#define     NULL       '\0'

#define    DIV_FACTOR_4                0b00000000
#define    DIV_FACTOR_16               0b00000001
#define    DIV_FACTOR_64               0b00000010
#define    DIV_FACTOR_128              0b00000011
#define    DIV_FACTOR_2X_2             0b00000000
#define    DIV_FACTOR_2X_8             0b00000001
#define    DIV_FACTOR_2X_32            0b00000010
#define    DIV_FACTOR_2X_64            0b00000011
#define    SPI_SCK_SEL_BIT_MASK        0b11111100


/******************************Register Description*******************************/

#define		SPDR			*((volatile u8 *)(0x2F))
#define		SPCR			*((volatile u8 *)(0x2D))
#define		SPSR			*((volatile u8 *)(0x2E))


#define     SPCR_SPR0		0
#define     SPCR_SPR1		1
#define     SPCR_CPHA		2
#define     SPCR_CPOL		3
#define     SPCR_MSTR		4
#define     SPCR_DORD		5
#define     SPCR_SPE		6
#define     SPCR_SPIE		7

#define		SPSR_SPI2X		0
#define		SPSR_WCOL		6
#define		SPSR_SPIF		7


#endif