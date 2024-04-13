/**************************************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:        29 FEB, 2024
 * Version:              v1.0
 * Compiler:             GNU GCC
 **************************************************************************/
/**************************************************************************
 * Version      Date             Author                   Description
 * v1.0         29 FEB, 2024     Abdullah R.Hebashi       Initial Creation    
***************************************************************************/


#ifndef HAL_CAN_EX_MCP2515_MCP2515_interface_H_
#define HAL_CAN_EX_MCP2515_MCP2515_interface_H_


/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000UL       /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000UL       /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000UL       /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFUL       /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFUL       /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFUL       /* omit EFF, RTR, ERR flags */

/*
 * Controller Area Network Identifier structure
 *
 * bit 0-28 : CAN identifier (11/29 bit)
 * bit 29   : error message frame flag (0 = data frame, 1 = error message)
 * bit 30   : remote transmission request flag (1 = rtr frame)
 * bit 31   : frame format flag (0 = standard 11 bit, 1 = extended 29 bit)
 */
typedef u32 canid_t;

#define CAN_SFF_ID_BITS     11
#define CAN_EFF_ID_BITS     29

/* CAN payload length and DLC definitions according to ISO 11898-1 */
#define CAN_MAX_DLC         8
#define CAN_MAX_DLEN        8


struct CAN_FRAME 
{
    canid_t CAN_ID;                                             /* 32 bit (CAN_ID (11-29)) + EFF(32)/RTR(31)/ERR(30) flags */
    u8      CAN_DLC;                                            /* Frame payload length in byte (0 .. CAN_MAX_DLEN) */
    u8      DATA[CAN_MAX_DLEN] __attribute__((aligned(8)));     /* Each element (byte) of the data array is aligned on an 8-bit boundary */
};


/* Speed 8M */
#define MCP_8MHz_1000kBPS_CFG1  (0x00)
#define MCP_8MHz_1000kBPS_CFG2  (0x80)
#define MCP_8MHz_1000kBPS_CFG3  (0x80)

#define MCP_8MHz_500kBPS_CFG1   (0x00)
#define MCP_8MHz_500kBPS_CFG3   (0x82)
#define MCP_8MHz_500kBPS_CFG2   (0x90)

#define MCP_8MHz_250kBPS_CFG1   (0x00)
#define MCP_8MHz_250kBPS_CFG2   (0xB1)
#define MCP_8MHz_250kBPS_CFG3   (0x85)

#define MCP_8MHz_200kBPS_CFG1   (0x00)
#define MCP_8MHz_200kBPS_CFG2   (0xB4)
#define MCP_8MHz_200kBPS_CFG3   (0x86)

#define MCP_8MHz_125kBPS_CFG1   (0x01)
#define MCP_8MHz_125kBPS_CFG2   (0xB1)
#define MCP_8MHz_125kBPS_CFG3   (0x85)

#define MCP_8MHz_100kBPS_CFG1   (0x01)
#define MCP_8MHz_100kBPS_CFG2   (0xB4)
#define MCP_8MHz_100kBPS_CFG3   (0x86)

#define MCP_8MHz_80kBPS_CFG1    (0x01)
#define MCP_8MHz_80kBPS_CFG2    (0xBF)
#define MCP_8MHz_80kBPS_CFG3    (0x87)

#define MCP_8MHz_50kBPS_CFG1    (0x03)
#define MCP_8MHz_50kBPS_CFG2    (0xB4)
#define MCP_8MHz_50kBPS_CFG3    (0x86)

#define MCP_8MHz_40kBPS_CFG1    (0x03)
#define MCP_8MHz_40kBPS_CFG2    (0xBF)
#define MCP_8MHz_40kBPS_CFG3    (0x87)

#define MCP_8MHz_33k3BPS_CFG1   (0x47)
#define MCP_8MHz_33k3BPS_CFG2   (0xE2)
#define MCP_8MHz_33k3BPS_CFG3   (0x85)

#define MCP_8MHz_31k25BPS_CFG1  (0x07)
#define MCP_8MHz_31k25BPS_CFG2  (0xA4)
#define MCP_8MHz_31k25BPS_CFG3  (0x84)

#define MCP_8MHz_20kBPS_CFG1    (0x07)
#define MCP_8MHz_20kBPS_CFG2    (0xBF)
#define MCP_8MHz_20kBPS_CFG3    (0x87)

#define MCP_8MHz_10kBPS_CFG1    (0x0F)
#define MCP_8MHz_10kBPS_CFG2    (0xBF)
#define MCP_8MHz_10kBPS_CFG3    (0x87)

#define MCP_8MHz_5kBPS_CFG1     (0x1F)
#define MCP_8MHz_5kBPS_CFG2     (0xBF)
#define MCP_8MHz_5kBPS_CFG3     (0x87)

/* Speed 16M */
#define MCP_16MHz_1000kBPS_CFG1 (0x00)
#define MCP_16MHz_1000kBPS_CFG2 (0xD0)
#define MCP_16MHz_1000kBPS_CFG3 (0x82)

#define MCP_16MHz_500kBPS_CFG1  (0x00)
#define MCP_16MHz_500kBPS_CFG2  (0xF0)
#define MCP_16MHz_500kBPS_CFG3  (0x86)

#define MCP_16MHz_250kBPS_CFG1  (0x41)
#define MCP_16MHz_250kBPS_CFG2  (0xF1)
#define MCP_16MHz_250kBPS_CFG3  (0x85)

#define MCP_16MHz_200kBPS_CFG1  (0x01)
#define MCP_16MHz_200kBPS_CFG2  (0xFA)
#define MCP_16MHz_200kBPS_CFG3  (0x87)

#define MCP_16MHz_125kBPS_CFG1  (0x03)
#define MCP_16MHz_125kBPS_CFG2  (0xF0)
#define MCP_16MHz_125kBPS_CFG3  (0x86)

#define MCP_16MHz_100kBPS_CFG1  (0x03)
#define MCP_16MHz_100kBPS_CFG2  (0xFA)
#define MCP_16MHz_100kBPS_CFG3  (0x87)

#define MCP_16MHz_95kBPS_CFG1   (0x03)
#define MCP_16MHz_95kBPS_CFG2   (0xAD)
#define MCP_16MHz_95kBPS_CFG3   (0x07)

#define MCP_16MHz_83k3BPS_CFG1  (0x03)
#define MCP_16MHz_83k3BPS_CFG2  (0xBE)
#define MCP_16MHz_83k3BPS_CFG3  (0x07)

#define MCP_16MHz_80kBPS_CFG1   (0x03)
#define MCP_16MHz_80kBPS_CFG2   (0xFF)
#define MCP_16MHz_80kBPS_CFG3   (0x87)

#define MCP_16MHz_50kBPS_CFG1   (0x07)
#define MCP_16MHz_50kBPS_CFG2   (0xFA)
#define MCP_16MHz_50kBPS_CFG3   (0x87)

#define MCP_16MHz_40kBPS_CFG1   (0x07)
#define MCP_16MHz_40kBPS_CFG2   (0xFF)
#define MCP_16MHz_40kBPS_CFG3   (0x87)

#define MCP_16MHz_33k3BPS_CFG1  (0x4E)
#define MCP_16MHz_33k3BPS_CFG2  (0xF1)
#define MCP_16MHz_33k3BPS_CFG3  (0x85)

#define MCP_16MHz_20kBPS_CFG1   (0x0F)
#define MCP_16MHz_20kBPS_CFG2   (0xFF)
#define MCP_16MHz_20kBPS_CFG3   (0x87)

#define MCP_16MHz_10kBPS_CFG1   (0x1F)
#define MCP_16MHz_10kBPS_CFG2   (0xFF)
#define MCP_16MHz_10kBPS_CFG3   (0x87)

#define MCP_16MHz_5kBPS_CFG1    (0x3F)
#define MCP_16MHz_5kBPS_CFG2    (0xFF)
#define MCP_16MHz_5kBPS_CFG3    (0x87)

/* Speed 20M */
#define MCP_20MHz_1000kBPS_CFG1 (0x00)
#define MCP_20MHz_1000kBPS_CFG2 (0xD9)
#define MCP_20MHz_1000kBPS_CFG3 (0x82)

#define MCP_20MHz_500kBPS_CFG1  (0x00)
#define MCP_20MHz_500kBPS_CFG2  (0xFA)
#define MCP_20MHz_500kBPS_CFG3  (0x87)

#define MCP_20MHz_250kBPS_CFG1  (0x41)
#define MCP_20MHz_250kBPS_CFG2  (0xFB)
#define MCP_20MHz_250kBPS_CFG3  (0x86)

#define MCP_20MHz_200kBPS_CFG1  (0x01)
#define MCP_20MHz_200kBPS_CFG2  (0xFF)
#define MCP_20MHz_200kBPS_CFG3  (0x87)

#define MCP_20MHz_125kBPS_CFG1  (0x03)
#define MCP_20MHz_125kBPS_CFG2  (0xFA)
#define MCP_20MHz_125kBPS_CFG3  (0x87)

#define MCP_20MHz_100kBPS_CFG1  (0x04)
#define MCP_20MHz_100kBPS_CFG2  (0xFA)
#define MCP_20MHz_100kBPS_CFG3  (0x87)

#define MCP_20MHz_83k3BPS_CFG1  (0x04)
#define MCP_20MHz_83k3BPS_CFG2  (0xFE)
#define MCP_20MHz_83k3BPS_CFG3  (0x87)

#define MCP_20MHz_80kBPS_CFG1   (0x04)
#define MCP_20MHz_80kBPS_CFG2   (0xFF)
#define MCP_20MHz_80kBPS_CFG3   (0x87)

#define MCP_20MHz_50kBPS_CFG1   (0x09)
#define MCP_20MHz_50kBPS_CFG2   (0xFA)
#define MCP_20MHz_50kBPS_CFG3   (0x87)

#define MCP_20MHz_40kBPS_CFG1   (0x09)
#define MCP_20MHz_40kBPS_CFG2   (0xFF)
#define MCP_20MHz_40kBPS_CFG3   (0x87)

#define MCP_20MHz_33k3BPS_CFG1  (0x0B)
#define MCP_20MHz_33k3BPS_CFG2  (0xFF)
#define MCP_20MHz_33k3BPS_CFG3  (0x87)

typedef enum
{
    MCP_20MHZ,
    MCP_16MHZ,
    MCP_8MHZ
}CAN_CLOCK;

typedef enum
{
    CAN_5KBPS,
    CAN_10KBPS,
    CAN_20KBPS,
    CAN_31K25BPS,
    CAN_33KBPS,
    CAN_40KBPS,
    CAN_50KBPS,
    CAN_80KBPS,
    CAN_83K3BPS,
    CAN_95KBPS,
    CAN_100KBPS,
    CAN_125KBPS,
    CAN_200KBPS,
    CAN_250KBPS,
    CAN_500KBPS,
    CAN_1000KBPS
}CAN_SPEED;

typedef enum
{
    CLKOUT_DISABLE = -1,
    CLKOUT_DIV1 = 0x0,
    CLKOUT_DIV2 = 0x1,
    CLKOUT_DIV4 = 0x2,
    CLKOUT_DIV8 = 0x3,
}CAN_CLKOUT;

typedef enum
{
    ERROR_OK        = 0,
    ERROR_FAIL      = 1,
    ERROR_ALLTXBUSY = 2,
    ERROR_FAILINIT  = 3,
    ERROR_FAILTX    = 4,
    ERROR_NOMSG     = 5
}ERROR;

typedef enum
{
    MASK0,
    MASK1
}MASK;

typedef enum
{
    RXF0 = 0,
    RXF1 = 1,
    RXF2 = 2,
    RXF3 = 3,
    RXF4 = 4,
    RXF5 = 5
}RXF;

typedef enum
{
    RXB0 = 0,
    RXB1 = 1
}RXBn;

typedef enum
{
    TXB0 = 0,
    TXB1 = 1,
    TXB2 = 2
}TXBn;

typedef enum
{
    CANINTF_RX0IF = (u8) 0x01,
    CANINTF_RX1IF = (u8) 0x02,
    CANINTF_TX0IF = (u8) 0x04,
    CANINTF_TX1IF = (u8) 0x08,
    CANINTF_TX2IF = (u8) 0x10,
    CANINTF_ERRIF = (u8) 0x20,
    CANINTF_WAKIF = (u8) 0x40,
    CANINTF_MERRF = (u8) 0x80
}CANINTF;

typedef enum
{
    EFLG_RX1OVR = (u8) (1<<7),
    EFLG_RX0OVR = (u8) (1<<6),
    EFLG_TXBO   = (u8) (1<<5),
    EFLG_TXEP   = (u8) (1<<4),
    EFLG_RXEP   = (u8) (1<<3),
    EFLG_TXWAR  = (u8) (1<<2),
    EFLG_RXWAR  = (u8) (1<<1),
    EFLG_EWARN  = (u8) (1<<0)
}EFLG;


void HMCP_voidInit(void);
ERROR HMCP_ERRORReset(void);
ERROR HMCP_ERRORSetConfigMode(void);
ERROR HMCP_ERRORSetListenOnlyMode(void);
ERROR HMCP_ERRORSetSleepMode(void);
ERROR HMCP_ERRORSetLoopbackMode(void);
ERROR HMCP_ERRORSetNormalMode(void);
ERROR HMCP_ERRORSetClkOut(const CAN_CLKOUT Copy_CAN_CLKOUTDivisor);
ERROR HMCP_ERRORSetBitRate16MHZ(const CAN_SPEED Copy_CAN_SPEEDCANSpeed);
ERROR HMCP_ERRORSetBitRate(const CAN_SPEED Copy_CAN_SPEEDCANSpeed, CAN_CLOCK Copy_CAN_CLOCKCANClock);
ERROR HMCP_ERRORSetFilterMask(const MASK Copy_MASKMask, const u8 Copy_u8Extended, const u32 Copy_u32Data);
ERROR HMCP_ERRORSetFilter(const RXF Copy_RXFNumber, const u8 Copy_u8Extended, const u32 Copy_u32Data);
ERROR HMCP_ERRORSendMessage(const TXBn Copy_TXBntxbn, const struct CAN_FRAME *CANFrameobj);
ERROR HMCP_ERRORSendAllMessages(const struct CAN_FRAME *CANFrameobj);
ERROR HMCP_ERRORReadMessage(const RXBn Copy_RXBnrxbn, struct CAN_FRAME *CANFrameobj);
ERROR HMCP_ERRORReadAllMessages(struct CAN_FRAME *CANFrameobj);
u8 HMCP_u8CheckReceive(void);
u8 HMCP_u8CheckError(void);
u8 HMCP_u8GetErrorFlags(void);
void HMCP_voidClearRXnOVRFlags(void);
u8 HMCP_u8GetInterrupts(void);
u8 HMCP_u8GetINTPinValue(void);
u8 HMCP_u8GetInterruptMask(void);
void HMCP_voidClearInterrupts(void);
void HMCP_voidClearTXInterrupts(void);
u8 HMCP_u8GetStatus(void);
void HMCP_voidClearRXnOVR(void);
void HMCP_voidClearMERR(void);
void HMCP_voidClearERRIF(void);
u8 HMCP_u8ErrorCountRX(void);
u8 HMCP_u8ErrorCountTX(void);

/************************** EMULATION FUNCTIONS ***************************/
void HMCP_voidEMULATEInit(void);
ERROR HMCP_ERROREMULATEReadMessage(u8 u8CAN_ARRAY[13],  struct CAN_FRAME *CANFrameobj);
ERROR HMCP_ERROREMULATESendMessage(struct CAN_FRAME *CANFrameobj);


#endif