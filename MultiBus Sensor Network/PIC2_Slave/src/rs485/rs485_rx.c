#include "rs485_rx.h"
#include "definitions.h"
#include "sensordata.h"
#include "utils.h"
#include <string.h> 

bool RS485_ReceiveSensorData(SensorData_t* data)
{
    if (data == NULL)
        return false;

    uint8_t buffer[12];

    if (!UART5_ReadIsBusy())
    {
        if (UART5_Read(buffer, sizeof(buffer)))
        {
            while (UART5_ReadIsBusy());

            memcpy(&(data->temperature), &buffer[0], 4);
            memcpy(&(data->pressure),    &buffer[4], 4);
            memcpy(&(data->humidity),    &buffer[8], 4);

            return true;
        }
    }

    return false;
}
