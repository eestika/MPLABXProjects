/*******************************************************************************
  BME280 Sensor Header File

  Company:
    Perez Dynamics OÜ

  File Name:
    bme280.h

  Summary:
    Interfaccia per l'inizializzazione e lettura del sensore BME280.

  Description:
    Questo file fornisce le dichiarazioni delle funzioni e degli accessi ai
    buffer per leggere i dati grezzi dal sensore BME280.
*******************************************************************************/

#ifndef BME280_H
#define BME280_H

#include <stdbool.h>
#include <stdint.h>

// Inizializza il sensore BME280 (oversampling e configurazioni base)
bool BME280_Initialize(void);

// Legge i dati grezzi da sensore e da memoria di calibrazione
bool BME280_ReadRawData(void);

// Restituisce il puntatore ai dati grezzi (8 byte)
const uint8_t* BME280_GetRawData(void);

// Restituisce il puntatore ai dati di calibrazione (26 byte)
const uint8_t* BME280_GetCalibData(void);

#endif // BME280_H
