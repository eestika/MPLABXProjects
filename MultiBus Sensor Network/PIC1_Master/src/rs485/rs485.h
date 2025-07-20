#ifndef RS485_H
#define RS485_H

#include "parser.h"  // Per il tipo SensorData_t

// Invia i dati del sensore via UART5
void RS485_SendSensorData(const SensorData_t* data);

#endif // RS485_H
