#include "rs485.h"
#include "definitions.h" // Per UART5_Write()

void RS485_SendSensorData(const SensorData_t* data)
{
    if (data == NULL)
        return;

    // Buffer di trasmissione: 3 float da 4 byte = 12 byte
    uint8_t buffer[12];
    float* p = (float*)buffer;

    p[0] = data->temperature;
    p[1] = data->pressure;
    p[2] = data->humidity;

    UART5_Write(buffer, sizeof(buffer));
    while (UART5_WriteIsBusy());
}
