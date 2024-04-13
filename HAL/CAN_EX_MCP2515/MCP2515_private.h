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


#ifndef HAL_CAN_EX_MCP2515_MCP2515_private_H_
#define HAL_CAN_EX_MCP2515_MCP2515_private_H_


static const u8 CANCTRL_REQOP = 0xE0;
static const u8 CANCTRL_ABAT = 0x10;
static const u8 CANCTRL_OSM = 0x08;
static const u8 CANCTRL_CLKEN = 0x04;
static const u8 CANCTRL_CLKPRE = 0x03;

typedef enum
{
    CANCTRL_REQOP_NORMAL     = (u8) 0x00,
    CANCTRL_REQOP_SLEEP      = (u8) 0x20,
    CANCTRL_REQOP_LOOPBACK   = (u8) 0x40,
    CANCTRL_REQOP_LISTENONLY = (u8) 0x60,
    CANCTRL_REQOP_CONFIG     = (u8) 0x80,
    CANCTRL_REQOP_POWERUP    = (u8) 0xE0
}CANCTRL_REQOP_MODE;

static const u8 CANSTAT_OPMOD = 0xE0;
static const u8 CANSTAT_ICOD = 0x0E;

static const u8 CNF3_SOF = 0x80;

static const u8 TXB_EXIDE_MASK = 0x08;
static const u8 DLC_MASK       = 0x0F;
static const u8 RTR_MASK       = 0x40;

static const u8 RXBnCTRL_RXM_STD    = 0x20;
static const u8 RXBnCTRL_RXM_EXT    = 0x40;
static const u8 RXBnCTRL_RXM_STDEXT = 0x00;
static const u8 RXBnCTRL_RXM_MASK   = 0x60;
static const u8 RXBnCTRL_RTR        = 0x08;
static const u8 RXB0CTRL_BUKT       = 0x04;
static const u8 RXB0CTRL_FILHIT_MASK = 0x03;
static const u8 RXB1CTRL_FILHIT_MASK = 0x07;
static const u8 RXB0CTRL_FILHIT = 0x00;
static const u8 RXB1CTRL_FILHIT = 0x01;

static const u8 MCP_SIDH = 0;
static const u8 MCP_SIDL = 1;
static const u8 MCP_EID8 = 2;
static const u8 MCP_EID0 = 3;
static const u8 MCP_DLC  = 4;
static const u8 MCP_DATA = 5;

enum STAT
{
    STAT_RX0IF = (u8) (1<<0),
    STAT_RX1IF = (u8) (1<<1)
};

static const u8 STAT_RXIF_MASK = STAT_RX0IF | STAT_RX1IF;

enum TXBnCTRL
{
    TXB_ABTF   = (u8) 0x40,
    TXB_MLOA   = (u8) 0x20,
    TXB_TXERR  = (u8) 0x10,
    TXB_TXREQ  = (u8) 0x08,
    TXB_TXIE   = (u8) 0x04,
    TXB_TXP    = (u8) 0x03
};

static const u8 EFLG_ERRORMASK = EFLG_RX1OVR
                                | EFLG_RX0OVR
                                | EFLG_TXBO
                                | EFLG_TXEP
                                | EFLG_RXEP;

enum INSTRUCTION
{
    INSTRUCTION_WRITE       = (u8) 0x02,
    INSTRUCTION_READ        = (u8) 0x03,
    INSTRUCTION_BITMOD      = (u8) 0x05,
    INSTRUCTION_LOAD_TX0    = (u8) 0x40,
    INSTRUCTION_LOAD_TX1    = (u8) 0x42,
    INSTRUCTION_LOAD_TX2    = (u8) 0x44,
    INSTRUCTION_RTS_TX0     = (u8) 0x81,
    INSTRUCTION_RTS_TX1     = (u8) 0x82,
    INSTRUCTION_RTS_TX2     = (u8) 0x84,
    INSTRUCTION_RTS_ALL     = (u8) 0x87,
    INSTRUCTION_READ_RX0    = (u8) 0x90,
    INSTRUCTION_READ_RX1    = (u8) 0x94,
    INSTRUCTION_READ_STATUS = (u8) 0xA0,
    INSTRUCTION_RX_STATUS   = (u8) 0xB0,
    INSTRUCTION_RESET       = (u8) 0xC0
};

typedef enum
{
    MCP_RXF0SIDH = (u8) 0x00,
    MCP_RXF0SIDL = (u8) 0x01,
    MCP_RXF0EID8 = (u8) 0x02,
    MCP_RXF0EID0 = (u8) 0x03,
    MCP_RXF1SIDH = (u8) 0x04,
    MCP_RXF1SIDL = (u8) 0x05,
    MCP_RXF1EID8 = (u8) 0x06,
    MCP_RXF1EID0 = (u8) 0x07,
    MCP_RXF2SIDH = (u8) 0x08,
    MCP_RXF2SIDL = (u8) 0x09,
    MCP_RXF2EID8 = (u8) 0x0A,
    MCP_RXF2EID0 = (u8) 0x0B,
    MCP_CANSTAT  = (u8) 0x0E,
    MCP_CANCTRL  = (u8) 0x0F,
    MCP_RXF3SIDH = (u8) 0x10,
    MCP_RXF3SIDL = (u8) 0x11,
    MCP_RXF3EID8 = (u8) 0x12,
    MCP_RXF3EID0 = (u8) 0x13,
    MCP_RXF4SIDH = (u8) 0x14,
    MCP_RXF4SIDL = (u8) 0x15,
    MCP_RXF4EID8 = (u8) 0x16,
    MCP_RXF4EID0 = (u8) 0x17,
    MCP_RXF5SIDH = (u8) 0x18,
    MCP_RXF5SIDL = (u8) 0x19,
    MCP_RXF5EID8 = (u8) 0x1A,
    MCP_RXF5EID0 = (u8) 0x1B,
    MCP_TEC      = (u8) 0x1C,
    MCP_REC      = (u8) 0x1D,
    MCP_RXM0SIDH = (u8) 0x20,
    MCP_RXM0SIDL = (u8) 0x21,
    MCP_RXM0EID8 = (u8) 0x22,
    MCP_RXM0EID0 = (u8) 0x23,
    MCP_RXM1SIDH = (u8) 0x24,
    MCP_RXM1SIDL = (u8) 0x25,
    MCP_RXM1EID8 = (u8) 0x26,
    MCP_RXM1EID0 = (u8) 0x27,
    MCP_CNF3     = (u8) 0x28,
    MCP_CNF2     = (u8) 0x29,
    MCP_CNF1     = (u8) 0x2A,
    MCP_CANINTE  = (u8) 0x2B,
    MCP_CANINTF  = (u8) 0x2C,
    MCP_EFLG     = (u8) 0x2D,
    MCP_TXB0CTRL = (u8) 0x30,
    MCP_TXB0SIDH = (u8) 0x31,
    MCP_TXB0SIDL = (u8) 0x32,
    MCP_TXB0EID8 = (u8) 0x33,
    MCP_TXB0EID0 = (u8) 0x34,
    MCP_TXB0DLC  = (u8) 0x35,
    MCP_TXB0DATA = (u8) 0x36,
    MCP_TXB1CTRL = (u8) 0x40,
    MCP_TXB1SIDH = (u8) 0x41,
    MCP_TXB1SIDL = (u8) 0x42,
    MCP_TXB1EID8 = (u8) 0x43,
    MCP_TXB1EID0 = (u8) 0x44,
    MCP_TXB1DLC  = (u8) 0x45,
    MCP_TXB1DATA = (u8) 0x46,
    MCP_TXB2CTRL = (u8) 0x50,
    MCP_TXB2SIDH = (u8) 0x51,
    MCP_TXB2SIDL = (u8) 0x52,
    MCP_TXB2EID8 = (u8) 0x53,
    MCP_TXB2EID0 = (u8) 0x54,
    MCP_TXB2DLC  = (u8) 0x55,
    MCP_TXB2DATA = (u8) 0x56,
    MCP_RXB0CTRL = (u8) 0x60,
    MCP_RXB0SIDH = (u8) 0x61,
    MCP_RXB0SIDL = (u8) 0x62,
    MCP_RXB0EID8 = (u8) 0x63,
    MCP_RXB0EID0 = (u8) 0x64,
    MCP_RXB0DLC  = (u8) 0x65,
    MCP_RXB0DATA = (u8) 0x66,
    MCP_RXB1CTRL = (u8) 0x70,
    MCP_RXB1SIDH = (u8) 0x71,
    MCP_RXB1SIDL = (u8) 0x72,
    MCP_RXB1EID8 = (u8) 0x73,
    MCP_RXB1EID0 = (u8) 0x74,
    MCP_RXB1DLC  = (u8) 0x75,
    MCP_RXB1DATA = (u8) 0x76
}REGISTER;


#define N_TXBUFFERS     3
#define N_RXBUFFERS     2

static const struct TXBn_REGS 
{
    REGISTER CTRL;
    REGISTER SIDH;
    REGISTER DATA;
} TXB[N_TXBUFFERS];

static const struct RXBn_REGS 
{
    REGISTER CTRL;
    REGISTER SIDH;
    REGISTER DATA;
    CANINTF  CANINTF_RXnIF;
} RXB[N_RXBUFFERS];


void HMCP_voidStartSPI(void);
void HMCP_voidEndSPI(void);
void HMCP_voidSPITransfer(u8 Copy_u8Data);
u8 HMCP_voidSPIReceive(void);

void voidMillisCounterUbdate(void);
u32 u32Millis(void);

void *pvoidmemset(void *Copy_pvoidVariable, u32 Copy_u32value, u32 Copy_u32NumberofData);
void *pvoidmemcpy(void *Copy_pvoidDestination, void *Copy_pvoidSource, u8 Copy_u8NumberofData);

ERROR HMCP_ERRORSetMode(const CANCTRL_REQOP_MODE Copy_CANCTRL_REQOP_MODEMode);

u8 HMCP_u8ReadRegister(const REGISTER Copy_REGISTERRegisterAddress);
void HMCP_voidReadRegisters(const REGISTER Copy_REGISTERRegisterAddress, u8 Copy_u8Arrayofvalues[], const u8 Copy_u8NumberofValues);
void HMCP_voidSetRegister(const REGISTER Copy_REGISTERRegisterAddress, const u8 Copy_u8RegisterValue);
void HMCP_voidSetRegisters(const REGISTER Copy_REGISTERRegisterAddress, const u8 Copy_u8Arrayofvalues[], const u8 Copy_u8NumberofValues);

/* // Allow "individual" bit modification */
void HMCP_voidModifyRegister(const REGISTER Copy_REGISTERRegisterAddress, const u8 Copy_u8Mask, const u8 Copy_u8Data);

void HMCP_voidPrepareID(u8 *Copy_pu8Buffer, const u8 Copy_u8Extended, const u32 Copy_u32ID);

/************************** EMULATION FUNCTIONS ***************************/
void HMCP_voidEMULATEStartSPI(void);
void HMCP_voidEMULATEEndSPI(void);
void HMCP_voidEMULATESPITransfer(u8 Copy_u8Data);
u8 HMCP_voidEMULATESPIReceive(void);


#endif