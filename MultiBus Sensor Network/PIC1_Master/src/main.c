// *****************************************************************************
// Main Source File
//
// Company:
//     Perez Dynamics OÜ
//
// File Name:
//     main.c
//
// Summary:
//     Punto di ingresso principale per il progetto MultiBus Sensor Network.
//
// Description:
//     Questo codice inizializza il sistema. All'interno del ciclo principale,
//     monitora il tasto USER (RE6). Quando viene premuto, legge i dati grezzi
//     dal sensore BME280, calcola temperatura, pressione e umidità, e li
//     trasmette (in futuro) via UART e CAN.
// *****************************************************************************

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"
#include "input.h"
#include "bme280.h"
#include "parser.h"
#include "rs485.h"
#include "canbus.h"

int main(void)
{
    SYS_Initialize(NULL);
    INPUT_Initialize();
    BME280_Initialize();
    CANBUS_Initialize();


    while (true)
    {
        SYS_Tasks();

        if (INPUT_UserPressed())
        {
            if (BME280_ReadRawData())
            {
                const uint8_t* raw_data   = BME280_GetRawData();
                const uint8_t* calib_data = BME280_GetCalibData();

                SensorData_t sensorValues;
                PARSER_ProcessData(raw_data, calib_data, &sensorValues);

                RS485_SendSensorData(&sensorValues);
                CANBUS_SendTemperature(sensorValues.temperature);

                // TODO: CAN_Send(sensorValues);
            }
        }
    }

    return EXIT_FAILURE;
}
