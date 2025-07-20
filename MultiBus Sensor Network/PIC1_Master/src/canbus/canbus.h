#ifndef CANBUS_H
#define CANBUS_H

#include <stdint.h>
#include <stdbool.h>

void CANBUS_Initialize(void);
void CANBUS_SendTemperature(float temperature);

#endif // CANBUS_H
