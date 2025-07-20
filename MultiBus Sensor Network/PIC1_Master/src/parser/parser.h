#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

typedef struct
{
    float temperature; // Temperatura in gradi Celsius
    float pressure;    // Pressione in hPa
    float humidity;    // Umidità in percentuale
} SensorData_t;

// Elabora i dati grezzi del BME280 e riempie la struct dei dati calcolati
void PARSER_ProcessData(const uint8_t* raw, const uint8_t* calib, SensorData_t* result);

#endif // PARSER_H

