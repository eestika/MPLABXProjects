/*******************************************************************************
  BME280 Sensor Source File

  Company:
    Perez Dynamics OÜ

  File Name:
    bme280.c

  Summary:
    Funzioni per inizializzare e leggere i dati grezzi dal sensore BME280.

  Description:
    Inizializzazione del BME280 e lettura dati grezzi (P/T/H) e calibrazione.
    Calibrazione completa: 0x88..0xA1 (26B, include H1) + 0xE1..0xE7 (7B).
*******************************************************************************/

#include "definitions.h"
#include "bme280.h"
#include <stdbool.h>
#include <stdint.h>

#define BME280_ADDR_76         0x76
#define BME280_ADDR_77         0x77
#define BME280_DATA_START      0xF7
#define BME280_CALIB_START     0x88

static uint8_t s_addr = BME280_ADDR_76;   // indirizzo attivo (76 o 77)

uint8_t bme_raw_data[8];
uint8_t bme_calib_data[33];               // [0..25]=0x88..0xA1, [26..32]=0xE1..0xE7


static bool bme280_check_id(uint8_t addr)
{
    uint8_t reg = 0xD0, id = 0;
    if (!I2C2_WriteRead(addr, &reg, 1, &id, 1)) return false;
    while (I2C2_IsBusy());
    return (id == 0x60);
}

bool BME280_Initialize(void)
{
    // Rileva indirizzo (0x76 di default, fallback 0x77)
    if (!bme280_check_id(BME280_ADDR_76))
    {
        if (!bme280_check_id(BME280_ADDR_77))
            return false;                 // sensore non trovato
        s_addr = BME280_ADDR_77;
    }
    else
    {
        s_addr = BME280_ADDR_76;
    }

    // Oversampling e configurazioni base (T=×1, P=×1, H=×1, normal mode, standby/filter)
    bool success = true;
    uint8_t ctrl_hum[2]  = { 0xF2, 0x01 }; // hum oversampling x1
    uint8_t ctrl_meas[2] = { 0xF4, 0x27 }; // temp x1, press x1, normal mode
    uint8_t config[2]    = { 0xF5, 0xA0 }; // standby 1000 ms, filter off (puoi cambiare)

    success &= I2C2_Write(s_addr, ctrl_hum,  2);
    while (I2C2_IsBusy());
    success &= I2C2_Write(s_addr, ctrl_meas, 2);
    while (I2C2_IsBusy());
    success &= I2C2_Write(s_addr, config,    2);
    while (I2C2_IsBusy());

    return success;
}

bool BME280_ReadRawData(void)
{
    uint8_t reg;

    // Dati grezzi: 0xF7..0xFE (8 byte: P[19:0], T[19:0], H[15:0])
    reg = BME280_DATA_START;
    if (!I2C2_WriteRead(s_addr, &reg, 1, bme_raw_data, 8)) return false;
    while (I2C2_IsBusy());

    // Calibrazione T/P + H1: 0x88..0xA1 (26B) ? calib[0..25]
    reg = BME280_CALIB_START;
    if (!I2C2_WriteRead(s_addr, &reg, 1, &bme_calib_data[0], 26)) return false;
    while (I2C2_IsBusy());

    // Calibrazione H2..H6: 0xE1..0xE7 (7B) ? calib[26..32]
    reg = 0xE1;
    if (!I2C2_WriteRead(s_addr, &reg, 1, &bme_calib_data[26], 7)) return false;
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

