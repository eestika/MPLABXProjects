#ifndef WIFI_AT_TX_H
#define WIFI_AT_TX_H

#include <stdbool.h>
#include "parser.h"  // Per SensorData_t

#ifdef __cplusplus
extern "C" {
#endif

// Inizializza il modulo ESP8266 (Reset + Join WiFi + TCP Connect)
void WiFi_AT_Initialize(void);

// Invia i dati del sensore formattati in JSON tramite comandi AT
bool WiFi_AT_SendSensorData(const SensorData_t* data);

#ifdef __cplusplus
}
#endif

#endif // WIFI_AT_TX_H


