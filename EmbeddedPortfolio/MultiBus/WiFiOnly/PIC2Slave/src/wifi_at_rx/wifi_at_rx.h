#ifndef WIFI_AT_RX_H
#define WIFI_AT_RX_H

#include <stdbool.h>
#include "utils.h"
#include "sensordata.h"

// Inizializza il modulo ESP8266 come Access Point e Server TCP
void WiFi_AT_Initialize(void);

// Riceve dati JSON da UART4 e li converte in struct SensorData_t
bool WiFi_AT_ReceiveSensorData(SensorData_t* data);

#endif // WIFI_AT_RX_H
