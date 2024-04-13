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


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/SPI/SPI_interface.h"
#include "../../MCAL/GIE/GIE_interface.h"
#include "../../MCAL/TIMER/TIMER_interface.h"

#include "MCP2515_interface.h"
#include "MCP2515_private.h"
#include "MCP2515_config.h"


volatile u32 u32Millis_Counter = 0;


static const struct TXBn_REGS TXB[N_TXBUFFERS] =
{
    {MCP_TXB0CTRL, MCP_TXB0SIDH, MCP_TXB0DATA},
    {MCP_TXB1CTRL, MCP_TXB1SIDH, MCP_TXB1DATA},
    {MCP_TXB2CTRL, MCP_TXB2SIDH, MCP_TXB2DATA}
};

static const struct RXBn_REGS RXB[N_RXBUFFERS] =
{
    {MCP_RXB0CTRL, MCP_RXB0SIDH, MCP_RXB0DATA, CANINTF_RX0IF},
    {MCP_RXB1CTRL, MCP_RXB1SIDH, MCP_RXB1DATA, CANINTF_RX1IF}
};


void HMCP_voidInit(void)
{
    MDIO_voidSPIMasterConfig();
    MDIO_voidsetpindir(INT_PORT, INT_PIN, INPUT);
    MTIMER1_voidInit();
    MTIMER1_voidSetOC1ACallBack(& voidMillisCounterUbdate);
    MTIMER1_voidEnableInterrupt(TIMER1_COMPA);
    MTIMER1_voidSetOC1AMatchValue(124);
    MGIE_voidEnableGlobalInterrupt();
    MTIMER1_voidSetPreloadValue(0);
    MSPI_voidMasterInit();
}

void voidMillisCounterUbdate(void)
{
    u32Millis_Counter++;
}

u32 u32Millis(void)
{
    return u32Millis_Counter;
}

void HMCP_voidStartSPI(void) 
{
    MSPI_voidMasterInit();
    MDIO_voidsetpinval(DIO_PORTB, PIN4, LOW);
}

void HMCP_voidEndSPI(void)
{
    MDIO_voidsetpinval(DIO_PORTB, PIN4, HIGH);
    MSPI_voidDisableSPI();
}

void HMCP_voidSPITransfer(u8 Copy_u8Data)
{
    u8 Local_u8DummyData = MSPI_u8SendReceive(Copy_u8Data);
}

u8 HMCP_voidSPIReceive(void)
{
    u8 Local_u8Data = MSPI_u8SendReceive(0x00);
    return(Local_u8Data);
}

void *pvoidmemset(void *Copy_pvoidVariable, u32 Copy_u32value, u32 Copy_u32NumberofData)
{
    u8 *Local_pu8TemporaryPointer = (u8 *)Copy_pvoidVariable;
    u32 Local_u32Itirator;
    for (Local_u32Itirator = 0; Local_u32Itirator < Copy_u32NumberofData; Local_u32Itirator++)
    {
        Local_pu8TemporaryPointer[Local_u32Itirator] = (u8) Copy_u32value;
    }
    return Copy_pvoidVariable;
}

ERROR HMCP_ERRORReset(void)
{
    HMCP_voidStartSPI();
    HMCP_voidSPITransfer(INSTRUCTION_RESET);
    HMCP_voidEndSPI();

    _delay_ms(10);

    u8 Local_u8Zeros[14];
    pvoidmemset(Local_u8Zeros, 0, 14);
    HMCP_voidSetRegisters(MCP_TXB0CTRL, Local_u8Zeros, 14);
    HMCP_voidSetRegisters(MCP_TXB1CTRL, Local_u8Zeros, 14);
    HMCP_voidSetRegisters(MCP_TXB2CTRL, Local_u8Zeros, 14);

    HMCP_voidSetRegister(MCP_RXB0CTRL, 0);
    HMCP_voidSetRegister(MCP_RXB1CTRL, 0);

    HMCP_voidSetRegister(MCP_CANINTE, CANINTF_RX0IF | CANINTF_RX1IF | CANINTF_ERRIF | CANINTF_MERRF);

    // receives all valid messages using either Standard or Extended Identifiers that
    // meet filter criteria. RXF0 is applied for RXB0, RXF1 is applied for RXB1
    HMCP_voidModifyRegister(MCP_RXB0CTRL,
                            RXBnCTRL_RXM_MASK | RXB0CTRL_BUKT | RXB0CTRL_FILHIT_MASK,
                            RXBnCTRL_RXM_STDEXT | RXB0CTRL_BUKT | RXB0CTRL_FILHIT);
    HMCP_voidModifyRegister(MCP_RXB1CTRL,
                            RXBnCTRL_RXM_MASK | RXB1CTRL_FILHIT_MASK,
                            RXBnCTRL_RXM_STDEXT | RXB1CTRL_FILHIT);

    // clear filters and masks
    // do not filter any standard frames for RXF0 used by RXB0
    // do not filter any extended frames for RXF1 used by RXB1
    RXF Local_RXFFilters[] = {RXF0, RXF1, RXF2, RXF3, RXF4, RXF5};
    for (u32 Local_u32Itirator = 0; Local_u32Itirator < 6; Local_u32Itirator++)
    {
        u8 Local_u8Extended = (Local_u32Itirator == 1);
        ERROR Local_ERRORResult = HMCP_ERRORSetFilter(Local_RXFFilters[Local_u32Itirator], Local_u8Extended, 0);
        if (Local_ERRORResult != ERROR_OK)
        {
            return Local_ERRORResult;
        }
    }

    MASK Local_MASKMasks[] = {MASK0, MASK1};
    for (u32 Local_u32Itirator = 0; Local_u32Itirator < 2; Local_u32Itirator++)
    {
        ERROR Local_ERRORResult = HMCP_ERRORSetFilterMask(Local_MASKMasks[Local_u32Itirator], TRUE, 0);
        if (Local_ERRORResult != ERROR_OK)
        {
            return Local_ERRORResult;
        }
    }

    return ERROR_OK;
}

u8 HMCP_u8ReadRegister(const REGISTER Copy_REGISTERRegisterAddress)
{
    HMCP_voidStartSPI();
    HMCP_voidSPITransfer(INSTRUCTION_READ);
    HMCP_voidSPITransfer(Copy_REGISTERRegisterAddress);
    u8 Local_u8Return = HMCP_voidSPIReceive();
    HMCP_voidEndSPI();

    return Local_u8Return;
}

void HMCP_voidReadRegisters(const REGISTER Copy_REGISTERRegisterAddress, u8 Copy_u8Arrayofvalues[], const u8 Copy_u8NumberofValues)
{
    HMCP_voidStartSPI();
    HMCP_voidSPITransfer(INSTRUCTION_READ);
    HMCP_voidSPITransfer(Copy_REGISTERRegisterAddress);
    // mcp2515 has auto-increment of address-pointer
    for (u8 Local_u8Itirator = 0; Local_u8Itirator < Copy_u8NumberofValues; Local_u8Itirator++)
    {
        Copy_u8Arrayofvalues[Local_u8Itirator] = HMCP_voidSPIReceive();
    }
    HMCP_voidEndSPI();
}

void HMCP_voidSetRegister(const REGISTER Copy_REGISTERRegisterAddress, const u8 Copy_u8RegisterValue)
{
    HMCP_voidStartSPI();
    HMCP_voidSPITransfer(INSTRUCTION_WRITE);
    HMCP_voidSPITransfer(Copy_REGISTERRegisterAddress);
    HMCP_voidSPITransfer(Copy_u8RegisterValue);
    HMCP_voidEndSPI();
}

void HMCP_voidSetRegisters(const REGISTER Copy_REGISTERRegisterAddress, const u8 Copy_u8Arrayofvalues[], const u8 Copy_u8NumberofValues)
{
    HMCP_voidStartSPI();
    HMCP_voidSPITransfer(INSTRUCTION_WRITE);
    HMCP_voidSPITransfer(Copy_REGISTERRegisterAddress);
    for (u8 Local_u8Itirator = 0; Local_u8Itirator < Copy_u8NumberofValues; Local_u8Itirator++)
    {
        HMCP_voidSPITransfer(Copy_u8Arrayofvalues[Local_u8Itirator]);
    }
    HMCP_voidEndSPI();
}

void HMCP_voidModifyRegister(const REGISTER Copy_REGISTERRegisterAddress, const u8 Copy_u8Mask, const u8 Copy_u8Data)
{
    HMCP_voidStartSPI();
    HMCP_voidSPITransfer(INSTRUCTION_BITMOD);
    HMCP_voidSPITransfer(Copy_REGISTERRegisterAddress);
    HMCP_voidSPITransfer(Copy_u8Mask);
    HMCP_voidSPITransfer(Copy_u8Data);
    HMCP_voidEndSPI();
}

u8 HMCP_u8GetStatus(void)
{
    HMCP_voidStartSPI();
    HMCP_voidSPITransfer(INSTRUCTION_READ_STATUS);
    u8 Local_u8ReceivedData = HMCP_voidSPIReceive();
    HMCP_voidEndSPI();

    return Local_u8ReceivedData;
}

ERROR HMCP_ERRORSetConfigMode(void)
{
    return HMCP_ERRORSetMode(CANCTRL_REQOP_CONFIG);
}

ERROR HMCP_ERRORSetListenOnlyMode(void)
{
    return HMCP_ERRORSetMode(CANCTRL_REQOP_LISTENONLY);
}

ERROR HMCP_ERRORSetSleepMode(void)
{
    return HMCP_ERRORSetMode(CANCTRL_REQOP_SLEEP);
}

ERROR HMCP_ERRORSetLoopbackMode(void)
{
    return HMCP_ERRORSetMode(CANCTRL_REQOP_LOOPBACK);
}

ERROR HMCP_ERRORSetNormalMode(void)
{
    return HMCP_ERRORSetMode(CANCTRL_REQOP_NORMAL);
}

ERROR HMCP_ERRORSetMode(const CANCTRL_REQOP_MODE Copy_CANCTRL_REQOP_MODEMode)
{
    HMCP_voidModifyRegister(MCP_CANCTRL, CANCTRL_REQOP, Copy_CANCTRL_REQOP_MODEMode);

    u32 Local_u32EndTime = (u32Millis()) + 10;
    u8 Local_u8ModeMatch = FALSE;
    while ((u32Millis()) < Local_u32EndTime)
    {
        u8 Local_u8NewMode = HMCP_u8ReadRegister(MCP_CANSTAT);
        Local_u8NewMode &= CANSTAT_OPMOD;

        Local_u8ModeMatch = (Local_u8NewMode == Copy_CANCTRL_REQOP_MODEMode);

        if (Local_u8ModeMatch)
        {
            break;
        }
    }

    return Local_u8ModeMatch ? ERROR_OK : ERROR_FAIL;
}

ERROR HMCP_ERRORSetBitRate16MHZ(const CAN_SPEED Copy_CAN_SPEEDCANSpeed)
{
    return HMCP_ERRORSetBitRate(Copy_CAN_SPEEDCANSpeed, MCP_16MHZ);
}

ERROR HMCP_ERRORSetBitRate(const CAN_SPEED Copy_CAN_SPEEDCANSpeed, CAN_CLOCK Copy_CAN_CLOCKCANClock)
{
    ERROR Local_ERRORErrorValue = HMCP_ERRORSetConfigMode();
    if (Local_ERRORErrorValue != ERROR_OK)
    {
        return Local_ERRORErrorValue;
    }

    u8 Local_u8SetValue, Local_u8CFG1, Local_u8CFG2, Local_u8CFG3;
    Local_u8SetValue = 1;
    switch (Copy_CAN_CLOCKCANClock)
    {
        case (MCP_8MHZ):
            switch (Copy_CAN_SPEEDCANSpeed)
            {
                case (CAN_5KBPS):                                               //   5KBPS
                    Local_u8CFG1 = MCP_8MHz_5kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_5kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_5kBPS_CFG3;
                break;

                case (CAN_10KBPS):                                              //  10KBPS
                    Local_u8CFG1 = MCP_8MHz_10kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_10kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_10kBPS_CFG3;
                break;

                case (CAN_20KBPS):                                              //  20KBPS
                    Local_u8CFG1 = MCP_8MHz_20kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_20kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_20kBPS_CFG3;
                break;

                case (CAN_31K25BPS):                                            //  31.25KBPS
                    Local_u8CFG1 = MCP_8MHz_31k25BPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_31k25BPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_31k25BPS_CFG3;
                break;

                case (CAN_33KBPS):                                              //  33.333KBPS
                    Local_u8CFG1 = MCP_8MHz_33k3BPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_33k3BPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_33k3BPS_CFG3;
                break;

                case (CAN_40KBPS):                                              //  40Kbps
                    Local_u8CFG1 = MCP_8MHz_40kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_40kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_40kBPS_CFG3;
                break;

                case (CAN_50KBPS):                                              //  50Kbps
                    Local_u8CFG1 = MCP_8MHz_50kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_50kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_50kBPS_CFG3;
                break;

                case (CAN_80KBPS):                                              //  80Kbps
                    Local_u8CFG1 = MCP_8MHz_80kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_80kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_80kBPS_CFG3;
                break;

                case (CAN_100KBPS):                                             // 100Kbps
                    Local_u8CFG1 = MCP_8MHz_100kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_100kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_100kBPS_CFG3;
                break;

                case (CAN_125KBPS):                                             // 125Kbps
                    Local_u8CFG1 = MCP_8MHz_125kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_125kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_125kBPS_CFG3;
                break;

                case (CAN_200KBPS):                                             // 200Kbps
                    Local_u8CFG1 = MCP_8MHz_200kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_200kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_200kBPS_CFG3;
                break;

                case (CAN_250KBPS):                                             // 250Kbps
                    Local_u8CFG1 = MCP_8MHz_250kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_250kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_250kBPS_CFG3;
                break;

                case (CAN_500KBPS):                                             // 500Kbps
                    Local_u8CFG1 = MCP_8MHz_500kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_500kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_500kBPS_CFG3;
                break;

                case (CAN_1000KBPS):                                            //   1Mbps
                    Local_u8CFG1 = MCP_8MHz_1000kBPS_CFG1;
                    Local_u8CFG2 = MCP_8MHz_1000kBPS_CFG2;
                    Local_u8CFG3 = MCP_8MHz_1000kBPS_CFG3;
                break;

                default:
                    Local_u8SetValue = 0;
                break;
            }
        break;

        case (MCP_16MHZ):
            switch (Copy_CAN_SPEEDCANSpeed)
            {
                case (CAN_5KBPS):                                               //   5Kbps
                    Local_u8CFG1 = MCP_16MHz_5kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_5kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_5kBPS_CFG3;
                break;

                case (CAN_10KBPS):                                              //  10Kbps
                    Local_u8CFG1 = MCP_16MHz_10kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_10kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_10kBPS_CFG3;
                break;

                case (CAN_20KBPS):                                              //  20Kbps
                    Local_u8CFG1 = MCP_16MHz_20kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_20kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_20kBPS_CFG3;
                break;

                case (CAN_33KBPS):                                              //  33.333Kbps
                    Local_u8CFG1 = MCP_16MHz_33k3BPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_33k3BPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_33k3BPS_CFG3;
                break;

                case (CAN_40KBPS):                                              //  40Kbps
                    Local_u8CFG1 = MCP_16MHz_40kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_40kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_40kBPS_CFG3;
                break;

                case (CAN_50KBPS):                                              //  50Kbps
                    Local_u8CFG1 = MCP_16MHz_50kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_50kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_50kBPS_CFG3;
                break;

                case (CAN_80KBPS):                                              //  80Kbps
                    Local_u8CFG1 = MCP_16MHz_80kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_80kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_80kBPS_CFG3;
                break;

                case (CAN_83K3BPS):                                             //  83.333Kbps
                    Local_u8CFG1 = MCP_16MHz_83k3BPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_83k3BPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_83k3BPS_CFG3;
                break;

                case (CAN_95KBPS):                                              //  95Kbps
                    Local_u8CFG1 = MCP_16MHz_95kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_95kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_95kBPS_CFG3;
                break;

                case (CAN_100KBPS):                                             // 100Kbps
                    Local_u8CFG1 = MCP_16MHz_100kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_100kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_100kBPS_CFG3;
                break;

                case (CAN_125KBPS):                                             // 125Kbps
                    Local_u8CFG1 = MCP_16MHz_125kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_125kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_125kBPS_CFG3;
                break;

                case (CAN_200KBPS):                                             // 200Kbps
                    Local_u8CFG1 = MCP_16MHz_200kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_200kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_200kBPS_CFG3;
                break;

                case (CAN_250KBPS):                                             // 250Kbps
                    Local_u8CFG1 = MCP_16MHz_250kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_250kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_250kBPS_CFG3;
                break;

                case (CAN_500KBPS):                                             // 500Kbps
                    Local_u8CFG1 = MCP_16MHz_500kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_500kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_500kBPS_CFG3;
                break;

                case (CAN_1000KBPS):                                            //   1Mbps
                    Local_u8CFG1 = MCP_16MHz_1000kBPS_CFG1;
                    Local_u8CFG2 = MCP_16MHz_1000kBPS_CFG2;
                    Local_u8CFG3 = MCP_16MHz_1000kBPS_CFG3;
                break;

                default:
                    Local_u8SetValue = 0;
                break;
            }
        break;

        case (MCP_20MHZ):
            switch (Copy_CAN_SPEEDCANSpeed)
            {
                case (CAN_33KBPS):                                              //  33.333Kbps
                    Local_u8CFG1 = MCP_20MHz_33k3BPS_CFG1;
                    Local_u8CFG2 = MCP_20MHz_33k3BPS_CFG2;
                    Local_u8CFG3 = MCP_20MHz_33k3BPS_CFG3;
                break;

                case (CAN_40KBPS):                                              //  40Kbps
                    Local_u8CFG1 = MCP_20MHz_40kBPS_CFG1;
                    Local_u8CFG2 = MCP_20MHz_40kBPS_CFG2;
                    Local_u8CFG3 = MCP_20MHz_40kBPS_CFG3;
                break;

                case (CAN_50KBPS):                                              //  50Kbps
                    Local_u8CFG1 = MCP_20MHz_50kBPS_CFG1;
                    Local_u8CFG2 = MCP_20MHz_50kBPS_CFG2;
                    Local_u8CFG3 = MCP_20MHz_50kBPS_CFG3;
                break;

                case (CAN_80KBPS):                                              //  80Kbps
                    Local_u8CFG1 = MCP_20MHz_80kBPS_CFG1;
                    Local_u8CFG2 = MCP_20MHz_80kBPS_CFG2;
                    Local_u8CFG3 = MCP_20MHz_80kBPS_CFG3;
                break;

                case (CAN_83K3BPS):                                             //  83.333Kbps
                    Local_u8CFG1 = MCP_20MHz_83k3BPS_CFG1;
                    Local_u8CFG2 = MCP_20MHz_83k3BPS_CFG2;
                    Local_u8CFG3 = MCP_20MHz_83k3BPS_CFG3;
                break;

                case (CAN_100KBPS):                                             // 100Kbps
                    Local_u8CFG1 = MCP_20MHz_100kBPS_CFG1;
                    Local_u8CFG2 = MCP_20MHz_100kBPS_CFG2;
                    Local_u8CFG3 = MCP_20MHz_100kBPS_CFG3;
                break;

                case (CAN_125KBPS):                                             // 125Kbps
                    Local_u8CFG1 = MCP_20MHz_125kBPS_CFG1;
                    Local_u8CFG2 = MCP_20MHz_125kBPS_CFG2;
                    Local_u8CFG3 = MCP_20MHz_125kBPS_CFG3;
                break;

                case (CAN_200KBPS):                                             // 200Kbps
                    Local_u8CFG1 = MCP_20MHz_200kBPS_CFG1;
                    Local_u8CFG2 = MCP_20MHz_200kBPS_CFG2;
                    Local_u8CFG3 = MCP_20MHz_200kBPS_CFG3;
                break;

                case (CAN_250KBPS):                                             // 250Kbps
                    Local_u8CFG1 = MCP_20MHz_250kBPS_CFG1;
                    Local_u8CFG2 = MCP_20MHz_250kBPS_CFG2;
                    Local_u8CFG3 = MCP_20MHz_250kBPS_CFG3;
                break;

                case (CAN_500KBPS):                                             // 500Kbps
                    Local_u8CFG1 = MCP_20MHz_500kBPS_CFG1;
                    Local_u8CFG2 = MCP_20MHz_500kBPS_CFG2;
                    Local_u8CFG3 = MCP_20MHz_500kBPS_CFG3;
                break;

                case (CAN_1000KBPS):                                            //   1Mbps
                    Local_u8CFG1 = MCP_20MHz_1000kBPS_CFG1;
                    Local_u8CFG2 = MCP_20MHz_1000kBPS_CFG2;
                    Local_u8CFG3 = MCP_20MHz_1000kBPS_CFG3;
                break;

                default:
                    Local_u8SetValue = 0;
                break;
            }
        break;

        default:
            Local_u8SetValue = 0;
        break;
    }

    if (Local_u8SetValue)
    {
        HMCP_voidSetRegister(MCP_CNF1, Local_u8CFG1);
        HMCP_voidSetRegister(MCP_CNF2, Local_u8CFG2);
        HMCP_voidSetRegister(MCP_CNF3, Local_u8CFG3);
        return ERROR_OK;
    }
    else
    {
        return ERROR_FAIL;
    }
}

ERROR HMCP_ERRORSetClkOut(const CAN_CLKOUT Copy_CAN_CLKOUTDivisor)
{
    if (Copy_CAN_CLKOUTDivisor == CLKOUT_DISABLE)
    {
	/* Turn off CLKEN */
	HMCP_voidModifyRegister(MCP_CANCTRL, CANCTRL_CLKEN, 0x00);

	/* Turn on CLKOUT for SOF */
	HMCP_voidModifyRegister(MCP_CNF3, CNF3_SOF, CNF3_SOF);
        return ERROR_OK;
    }

    /* Set the prescaler (CLKPRE) */
    HMCP_voidModifyRegister(MCP_CANCTRL, CANCTRL_CLKPRE, Copy_CAN_CLKOUTDivisor);

    /* Turn on CLKEN */
    HMCP_voidModifyRegister(MCP_CANCTRL, CANCTRL_CLKEN, CANCTRL_CLKEN);

    /* Turn off CLKOUT for SOF */
    HMCP_voidModifyRegister(MCP_CNF3, CNF3_SOF, 0x00);
    return ERROR_OK;
}

void HMCP_voidPrepareID(u8 *Copy_pu8Buffer, const u8 Copy_u8Extended, const u32 Copy_u32ID)
{
    u16 Local_u16CANID = (u16)(Copy_u32ID & 0x0FFFF);

    if (Copy_u8Extended)
    {
        Copy_pu8Buffer[MCP_EID0] = (u8) (Local_u16CANID & 0xFF);
        Copy_pu8Buffer[MCP_EID8] = (u8) (Local_u16CANID >> 8);
        Local_u16CANID = (u16)(Copy_u32ID >> 16);
        Copy_pu8Buffer[MCP_SIDL] = (u8) (Local_u16CANID & 0x03);
        Copy_pu8Buffer[MCP_SIDL] += (u8) ((Local_u16CANID & 0x1C) << 3);
        Copy_pu8Buffer[MCP_SIDL] |= TXB_EXIDE_MASK;
        Copy_pu8Buffer[MCP_SIDH] = (u8) (Local_u16CANID >> 5);
    } 
    else
    {
        Copy_pu8Buffer[MCP_SIDH] = (u8) (Local_u16CANID >> 3);
        Copy_pu8Buffer[MCP_SIDL] = (u8) ((Local_u16CANID & 0x07 ) << 5);
        Copy_pu8Buffer[MCP_EID0] = 0;
        Copy_pu8Buffer[MCP_EID8] = 0;
    }
}

ERROR HMCP_ERRORSetFilterMask(const MASK Copy_MASKMask, const u8 Copy_u8Extended, const u32 Copy_u32Data)
{
    ERROR Local_ERRORResult = HMCP_ERRORSetConfigMode();
    if (Local_ERRORResult != ERROR_OK)
    {
        return Local_ERRORResult;
    }
    
    u8 Local_u8TemporaryBufferDataArray[4];
    HMCP_voidPrepareID(Local_u8TemporaryBufferDataArray, Copy_u8Extended, Copy_u32Data);

    REGISTER Local_REGISTERRegister;
    switch (Copy_MASKMask)
    {
        case MASK0: Local_REGISTERRegister = MCP_RXM0SIDH; break;
        case MASK1: Local_REGISTERRegister = MCP_RXM1SIDH; break;
        default:
            return ERROR_FAIL;
    }

    HMCP_voidSetRegisters(Local_REGISTERRegister, Local_u8TemporaryBufferDataArray, 4);
    
    return ERROR_OK;
}

ERROR HMCP_ERRORSetFilter(const RXF Copy_RXFNumber, const u8 Copy_u8Extended, const u32 Copy_u32Data)
{
    ERROR Local_ERRORResult = HMCP_ERRORSetConfigMode();
    if (Local_ERRORResult != ERROR_OK)
    {
        return Local_ERRORResult;
    }

    REGISTER Local_REGISTERRegister;

    switch (Copy_RXFNumber)
    {
        case RXF0: Local_REGISTERRegister = MCP_RXF0SIDH; break;
        case RXF1: Local_REGISTERRegister = MCP_RXF1SIDH; break;
        case RXF2: Local_REGISTERRegister = MCP_RXF2SIDH; break;
        case RXF3: Local_REGISTERRegister = MCP_RXF3SIDH; break;
        case RXF4: Local_REGISTERRegister = MCP_RXF4SIDH; break;
        case RXF5: Local_REGISTERRegister = MCP_RXF5SIDH; break;
        default:
            return ERROR_FAIL;
    }

    u8 Local_u8TemporaryBufferDataArray[4];
    HMCP_voidPrepareID(Local_u8TemporaryBufferDataArray, Copy_u8Extended, Copy_u32Data);
    HMCP_voidSetRegisters(Local_REGISTERRegister, Local_u8TemporaryBufferDataArray, 4);

    return ERROR_OK;
}

void *pvoidmemcpy(void *Copy_pvoidDestination, void *Copy_pvoidSource, u8 Copy_u8NumberofData)
{
    u8 *Local_pu8TemporarySource = (u8 *)Copy_pvoidSource;
    u8 *Local_pu8TemporaryDestination = (u8 *)Copy_pvoidDestination;

    // Copy bytes from source to destination
    for (u8 Local_u8Itirator = 0; Local_u8Itirator < Copy_u8NumberofData; Local_u8Itirator++)
    {
        Local_pu8TemporaryDestination[Local_u8Itirator] = Local_pu8TemporarySource[Local_u8Itirator];
    }

    return Copy_pvoidDestination;
}

ERROR HMCP_ERRORSendMessage(const TXBn Copy_TXBntxbn, const struct CAN_FRAME *CANFrameobj)
{
    if (CANFrameobj->CAN_DLC > CAN_MAX_DLEN)
    {
        return ERROR_FAILTX;
    }

    const struct TXBn_REGS *Local_pTXBn_REGSTXBuffer = &TXB[Copy_TXBntxbn];

    u8 Local_u8DataArray[13];

    u8 Local_u8Extended = (CANFrameobj->CAN_ID & CAN_EFF_FLAG);
    u8 Local_u8RTR = (CANFrameobj->CAN_ID & CAN_RTR_FLAG);
    u32 Local_u32ID = (CANFrameobj->CAN_ID & (Local_u8Extended ? CAN_EFF_MASK : CAN_SFF_MASK));

    HMCP_voidPrepareID(Local_u8DataArray, Local_u8Extended, Local_u32ID);

    Local_u8DataArray[MCP_DLC] = Local_u8RTR ? (CANFrameobj->CAN_DLC | RTR_MASK) : CANFrameobj->CAN_DLC;

    pvoidmemcpy(&Local_u8DataArray[MCP_DATA], CANFrameobj->DATA, CANFrameobj->CAN_DLC);

    HMCP_voidSetRegisters(Local_pTXBn_REGSTXBuffer->SIDH, Local_u8DataArray, 5 + CANFrameobj->CAN_DLC);

    HMCP_voidModifyRegister(Local_pTXBn_REGSTXBuffer->CTRL, TXB_TXREQ, TXB_TXREQ);

    u8 Local_u8CTRLValue = HMCP_u8ReadRegister(Local_pTXBn_REGSTXBuffer->CTRL);
    if ((Local_u8CTRLValue & (TXB_ABTF | TXB_MLOA | TXB_TXERR)) != 0)
    {
        return ERROR_FAILTX;
    }
    return ERROR_OK;
}

ERROR HMCP_ERRORSendAllMessages(const struct CAN_FRAME *CANFrameobj)
{
    if (CANFrameobj->CAN_DLC > CAN_MAX_DLEN)
    {
        return ERROR_FAILTX;
    }

    TXBn Local_TXBntxBuffers[N_TXBUFFERS] = {TXB0, TXB1, TXB2};

    for (u32 Locla_u32Itirator = 0; Locla_u32Itirator < N_TXBUFFERS; Locla_u32Itirator++)
    {
        const struct TXBn_REGS *Local_TXBn_REGStxBuffer = &TXB[Local_TXBntxBuffers[Locla_u32Itirator]];
        u8 Local_u8CTRLValue = HMCP_u8ReadRegister(Local_TXBn_REGStxBuffer->CTRL);
        if ( (Local_u8CTRLValue & TXB_TXREQ) == 0 )
        {
            return HMCP_ERRORSendMessage(Local_TXBntxBuffers[Locla_u32Itirator], CANFrameobj);
        }
    }

    return ERROR_ALLTXBUSY;
}

ERROR HMCP_ERRORReadMessage(const RXBn Copy_RXBnrxbn, struct CAN_FRAME *CANFrameobj)
{
    const struct RXBn_REGS *Local_RXBn_REGSrxBuffer = &RXB[Copy_RXBnrxbn];

    u8 Local_u8TemporaryBufferDataArray[5];

    HMCP_voidReadRegisters(Local_RXBn_REGSrxBuffer->SIDH, Local_u8TemporaryBufferDataArray, 5);

    u32 Local_u32ID = (Local_u8TemporaryBufferDataArray[MCP_SIDH]<<3) + (Local_u8TemporaryBufferDataArray[MCP_SIDL]>>5);

    if ( (Local_u8TemporaryBufferDataArray[MCP_SIDL] & TXB_EXIDE_MASK) ==  TXB_EXIDE_MASK )
    {
        Local_u32ID = (Local_u32ID << 2) + (Local_u8TemporaryBufferDataArray[MCP_SIDL] & 0x03);
        Local_u32ID = (Local_u32ID << 8) + Local_u8TemporaryBufferDataArray[MCP_EID8];
        Local_u32ID = (Local_u32ID << 8) + Local_u8TemporaryBufferDataArray[MCP_EID0];
        Local_u32ID |= CAN_EFF_FLAG;
    }

    u8 Local_u8DLC = (Local_u8TemporaryBufferDataArray[MCP_DLC] & DLC_MASK);
    if (Local_u8DLC > CAN_MAX_DLEN)
    {
        return ERROR_FAIL;
    }

    u8 Local_u8CTRLValue = HMCP_u8ReadRegister(Local_RXBn_REGSrxBuffer->CTRL);
    if (Local_u8CTRLValue & RXBnCTRL_RTR)
    {
        Local_u32ID |= CAN_RTR_FLAG;
    }

    CANFrameobj->CAN_ID = Local_u32ID;
    CANFrameobj->CAN_DLC = Local_u8DLC;

    HMCP_voidReadRegisters(Local_RXBn_REGSrxBuffer->DATA, CANFrameobj->DATA, Local_u8DLC);

    HMCP_voidModifyRegister(MCP_CANINTF, Local_RXBn_REGSrxBuffer->CANINTF_RXnIF, 0);

    return ERROR_OK;
}

ERROR HMCP_ERRORReadAllMessages(struct CAN_FRAME *CANFrameobj)
{
    ERROR Local_ERRORReceiveComplete;
    u8 Local_u8Status = HMCP_u8GetStatus();

    if ( Local_u8Status & STAT_RX0IF )
    {
        Local_ERRORReceiveComplete = HMCP_ERRORReadMessage(RXB0, CANFrameobj);
    }
    else if ( Local_u8Status & STAT_RX1IF )
    {
        Local_ERRORReceiveComplete = HMCP_ERRORReadMessage(RXB1, CANFrameobj);
    }
    else
    {
        Local_ERRORReceiveComplete = ERROR_NOMSG;
    }

    return Local_ERRORReceiveComplete;
}

u8 HMCP_u8CheckReceive(void)
{
    u8 Local_u8Result = HMCP_u8GetStatus();
    if ( Local_u8Result & STAT_RXIF_MASK )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

u8 HMCP_u8CheckError(void)
{
    u8 Local_u8ErrorFlag = HMCP_u8GetErrorFlags();

    if ( Local_u8ErrorFlag & EFLG_ERRORMASK )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

u8 HMCP_u8GetErrorFlags(void)
{
    return HMCP_u8ReadRegister(MCP_EFLG);
}

void HMCP_voidClearRXnOVRFlags(void)
{
	HMCP_voidModifyRegister(MCP_EFLG, EFLG_RX0OVR | EFLG_RX1OVR, 0);
}

u8 HMCP_u8GetInterrupts(void)
{
    return HMCP_u8ReadRegister(MCP_CANINTF);
}

u8 HMCP_u8GetINTPinValue(void)
{
    return MDIO_u8GetVal(INT_PORT, INT_PIN);
}

void HMCP_voidClearInterrupts(void)
{
    HMCP_voidSetRegister(MCP_CANINTF, 0);
}

u8 HMCP_u8GetInterruptMask(void)
{
    return HMCP_u8ReadRegister(MCP_CANINTE);
}

void HMCP_voidClearTXInterrupts(void)
{
    HMCP_voidModifyRegister(MCP_CANINTF, (CANINTF_TX0IF | CANINTF_TX1IF | CANINTF_TX2IF), 0);
}

void HMCP_voidClearRXnOVR(void)
{
	u8 Local_u8ErrorFlag = HMCP_u8GetErrorFlags();
	if (Local_u8ErrorFlag != 0)
    {
		HMCP_voidClearRXnOVRFlags();
		HMCP_voidClearInterrupts();
		//HMCP_voidModifyRegister(MCP_CANINTF, CANINTF_ERRIF, 0);
	}
	
}

void HMCP_voidClearMERR()
{
	//HMCP_voidModifyRegister(MCP_EFLG, EFLG_RX0OVR | EFLG_RX1OVR, 0);
	//HMCP_voidClearInterrupts();
	HMCP_voidModifyRegister(MCP_CANINTF, CANINTF_MERRF, 0);
}

void HMCP_voidClearERRIF()
{
    //HMCP_voidModifyRegister(MCP_EFLG, EFLG_RX0OVR | EFLG_RX1OVR, 0);
    //HMCP_voidClearInterrupts();
    HMCP_voidModifyRegister(MCP_CANINTF, CANINTF_ERRIF, 0);
}

u8 HMCP_u8ErrorCountRX(void)                             
{
    return HMCP_u8ReadRegister(MCP_REC);
}

u8 HMCP_u8ErrorCountTX(void)                             
{
    return HMCP_u8ReadRegister(MCP_TEC);
}

/************************** EMULATION FUNCTIONS ***************************/
void HMCP_voidEMULATEInit(void)
{
    MDIO_voidSPIMasterConfig();
    MDIO_voidsetpindir(INT_PORT, INT_PIN, INPUT);
    MSPI_voidMasterInit();
}

void HMCP_voidEMULATEStartSPI(void) 
{
    MDIO_voidsetpinval(DIO_PORTB, PIN4, LOW);
}

void HMCP_voidEMULATEEndSPI(void)
{
    MDIO_voidsetpinval(DIO_PORTB, PIN4, HIGH);
}

void HMCP_voidEMULATESPITransfer(u8 Copy_u8Data)
{
    u8 Local_u8DummyData = MSPI_u8SendReceive(Copy_u8Data);
}

u8 HMCP_voidEMULATESPIReceive(void)
{
    u8 Local_u8Data = MSPI_u8SendReceive(0x00);
    return(Local_u8Data);
}

/* data are transmitted out of CAN pins into the u8CAN_ARRAY then saved into CANFrameobj structure */
/* whare u8CAN_ARRAY[13] = ID (4BYTE)(MSB(12)->LSB(9)) + DLC (1BYTE)(8) + DATA (8BYTE)(7->0) */
ERROR HMCP_ERROREMULATEReadMessage(u8 u8CAN_ARRAY[13], struct CAN_FRAME *CANFrameobj)
{
	HMCP_voidEMULATEStartSPI();
	HMCP_voidEMULATESPITransfer(0x00);
	HMCP_voidEMULATEEndSPI();
	
    for (u8 i = 0; i <= 12; i++)
    {
        HMCP_voidEMULATEStartSPI();
        u8CAN_ARRAY[i] = HMCP_voidEMULATESPIReceive();
        HMCP_voidEMULATEEndSPI();
    }

    u32 Local_u32ID = 0;

    Local_u32ID = (Local_u32ID) + (u8CAN_ARRAY[12]);
    Local_u32ID = (Local_u32ID << 8) + u8CAN_ARRAY[11];
    Local_u32ID = (Local_u32ID << 8) + u8CAN_ARRAY[10];
    Local_u32ID = (Local_u32ID << 8) + u8CAN_ARRAY[9];

    u8 Local_u8DLC = u8CAN_ARRAY[8];
    if (Local_u8DLC > CAN_MAX_DLEN)
    {
        return ERROR_FAIL;
    }

    for (u8 i = 0; i <= 7; i++)
    {
        CANFrameobj->DATA[i] = u8CAN_ARRAY[7-i];
    }

    CANFrameobj->CAN_ID = Local_u32ID;
    CANFrameobj->CAN_DLC = Local_u8DLC;

    return ERROR_OK;
}

ERROR HMCP_ERROREMULATESendMessage(struct CAN_FRAME *CANFrameobj)
{
    u8 u8CAN_ARRAY[13];

    if (CANFrameobj->CAN_DLC > CAN_MAX_DLEN)
    {
        return ERROR_FAILTX;
    }

    u32 Local_u32ID = CANFrameobj->CAN_ID;

    u8CAN_ARRAY[12] = (u8) (Local_u32ID >> 24);
    u8CAN_ARRAY[11] = (u8) (Local_u32ID >> 16);
    u8CAN_ARRAY[10] = (u8) (Local_u32ID >> 8);
    (u8CAN_ARRAY[9]) = (u8) (Local_u32ID);

    u8CAN_ARRAY[8] = CANFrameobj->CAN_DLC;

    for (u8 i = 0; i <= 7; i++)
    {
        u8CAN_ARRAY[7-i] = CANFrameobj->DATA[i];
    }

	HMCP_voidEMULATEStartSPI();
	HMCP_voidEMULATESPITransfer(0xff);
	HMCP_voidEMULATEEndSPI();

    for (u8 i = 0; i <= 12; i++)
    {
        HMCP_voidEMULATEStartSPI();
        HMCP_voidEMULATESPITransfer(u8CAN_ARRAY[i]);
        HMCP_voidEMULATEEndSPI();
    }

    return ERROR_OK;
}