#ifndef RS485_RX_H
#define RS485_RX_H

#include <stdbool.h>
#include "sensordata.h"

bool RS485_ReceiveSensorData(SensorData_t* data);

#endif // RS485_RX_H