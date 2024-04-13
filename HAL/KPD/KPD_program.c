/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    28 MAR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                          Description
 * v1.0          28 MAR, 2023     Abdullah R.Hebashi       Initial Creation    
***********************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"




void HKPD_voidInit(void)
{
	MDIO_voidsetpindir(KPD_ROWS_PORT, KPD_ROW0_PIN, INPUT);
    MDIO_voidsetpindir(KPD_ROWS_PORT, KPD_ROW1_PIN, INPUT);
    MDIO_voidsetpindir(KPD_ROWS_PORT, KPD_ROW2_PIN, INPUT);
    MDIO_voidsetpindir(KPD_ROWS_PORT, KPD_ROW3_PIN, INPUT);
    
    MDIO_voidsetpinval(KPD_ROWS_PORT, KPD_ROW0_PIN, PULLUP);
    MDIO_voidsetpinval(KPD_ROWS_PORT, KPD_ROW1_PIN, PULLUP);
    MDIO_voidsetpinval(KPD_ROWS_PORT, KPD_ROW2_PIN, PULLUP);
    MDIO_voidsetpinval(KPD_ROWS_PORT, KPD_ROW3_PIN, PULLUP);

    MDIO_voidsetpindir(KPD_COLUMNS_PORT, KPD_COLUMN0_PIN, OUTPUT);
    MDIO_voidsetpindir(KPD_COLUMNS_PORT, KPD_COLUMN1_PIN, OUTPUT);
    MDIO_voidsetpindir(KPD_COLUMNS_PORT, KPD_COLUMN2_PIN, OUTPUT);
    MDIO_voidsetpindir(KPD_COLUMNS_PORT, KPD_COLUMN3_PIN, OUTPUT);

    MDIO_voidsetpinval(KPD_COLUMNS_PORT, KPD_COLUMN0_PIN, HIGH);
    MDIO_voidsetpinval(KPD_COLUMNS_PORT, KPD_COLUMN1_PIN, HIGH);
    MDIO_voidsetpinval(KPD_COLUMNS_PORT, KPD_COLUMN2_PIN, HIGH);
    MDIO_voidsetpinval(KPD_COLUMNS_PORT, KPD_COLUMN3_PIN, HIGH);
}


u8 HKPD_u8GetPressedKey(void)
{
    static u8 Local_u8KPDArray[KPD_ROWS_NUM][KPD_COULMNS_NUM] = KPD_ARR_VAL;
    static u8 Local_u8KPDColumnsArray[KPD_COULMNS_NUM] = {KPD_COLUMN0_PIN, KPD_COLUMN1_PIN, KPD_COLUMN2_PIN, KPD_COLUMN3_PIN};
    static u8 Local_u8KPDRowsArray[KPD_ROWS_NUM] = {KPD_ROW0_PIN, KPD_ROW1_PIN, KPD_ROW2_PIN, KPD_ROW3_PIN};
    u8 Local_u8RowValue;
    u8 Local_u8ColumnsIterator;
    u8 Local_u8RowsIterator;
    u8 Local_u8PressedKey = KPD_NOT_PRESSED_VAL;
    for(Local_u8ColumnsIterator = 0; Local_u8ColumnsIterator < KPD_COULMNS_NUM; Local_u8ColumnsIterator++)
    {
        MDIO_voidsetpinval(KPD_COLUMNS_PORT, Local_u8KPDColumnsArray[Local_u8ColumnsIterator], LOW);
        for(Local_u8RowsIterator = 0; Local_u8RowsIterator < KPD_ROWS_NUM; Local_u8RowsIterator++)
        {
            Local_u8RowValue = MDIO_u8GetVal(KPD_ROWS_PORT, Local_u8KPDRowsArray[Local_u8RowsIterator]);
            if(Local_u8RowValue == LOW)
            {
                Local_u8PressedKey = Local_u8KPDArray[Local_u8RowsIterator][Local_u8ColumnsIterator];
                while(Local_u8RowValue == LOW)
                {
                    Local_u8RowValue = MDIO_u8GetVal(KPD_ROWS_PORT, Local_u8KPDRowsArray[Local_u8RowsIterator]);
                }
                return Local_u8PressedKey;
            }
        }
        MDIO_voidsetpinval(KPD_COLUMNS_PORT, Local_u8KPDColumnsArray[Local_u8ColumnsIterator], HIGH);
    }
    return Local_u8PressedKey;
}