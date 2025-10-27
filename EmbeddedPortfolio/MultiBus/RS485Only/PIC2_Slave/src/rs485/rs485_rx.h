#ifndef RS485_RX_H
#define RS485_RX_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "sensordata.h"

// Riceve esattamente n byte dalla UART5 (funzione base)
bool RS485_ReadExact(uint8_t* dst, size_t n);

// Variante compatibile con il vecchio codice: riceve 12 byte e popola SensorData_t
bool RS485_ReceiveSensorData(SensorData_t* data);

#endif // RS485_RX_H
