/*******************************************************************************
  BME280 Sensor Source File

  Company:
    Perez Dynamics OÜ

  File Name:
    bme280.c

  Summary:
    Funzioni per inizializzare e leggere i dati grezzi dal sensore BME280.

  Description:
    Questo modulo inizializza il sensore BME280 e legge i dati grezzi di temperatura,
    pressione e umidità, oltre ai dati di calibrazione.
*******************************************************************************/

#include "definitions.h"
#include "bme280.h"

#define BME280_ADDRESS         0x76
#define BME280_DATA_START      0xF7
#define BME280_CALIB_START     0x88

uint8_t bme_raw_data[8];
uint8_t bme_calib_data[26];

bool BME280_Initialize(void)
{
    bool success = true;

    uint8_t ctrl_hum[2]  = { 0xF2, 0x01 };
    uint8_t ctrl_meas[2] = { 0xF4, 0x27 };
    uint8_t config[2]    = { 0xF5, 0xA0 };

    success &= I2C2_Write(BME280_ADDRESS, ctrl_hum, 2);
    while (I2C2_IsBusy());

    success &= I2C2_Write(BME280_ADDRESS, ctrl_meas, 2);
    while (I2C2_IsBusy());

    success &= I2C2_Write(BME280_ADDRESS, config, 2);
    while (I2C2_IsBusy());

    return success;
}

bool BME280_ReadRawData(void)
{
    uint8_t data_start = BME280_DATA_START;
    uint8_t calib_start = BME280_CALIB_START;

    if (!I2C2_WriteRead(BME280_ADDRESS, &data_start, 1, bme_raw_data, 8))
        return false;
    while (I2C2_IsBusy());

    if (!I2C2_WriteRead(BME280_ADDRESS, &calib_start, 1, bme_calib_data, 26))
        return false;
    while (I2C2_IsBusy());

    return true;
}

const uint8_t* BME280_GetRawData(void)
{
    return bme_raw_data;
}

const uint8_t* BME280_GetCalibData(void)
{
    return bme_calib_data;
}
