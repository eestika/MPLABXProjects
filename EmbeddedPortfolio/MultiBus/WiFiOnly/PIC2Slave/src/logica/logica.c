#include "logica.h"
#include "definitions.h"
#include "utils.h"

#define TEMP_THRESHOLD 25.0f

void Logica_ProcessData(const SensorData_t* data)
{
    if (data == NULL) return;

    if (data->temperature <= TEMP_THRESHOLD)
    {
        // Verde ON (RE3 LOW), Rosso OFF (RE1 HIGH)
        LATECLR = (1 << 3);  // RE3 = 0 → ON
        LATESET = (1 << 1);  // RE1 = 1 → OFF
    }
    else
    {
        // Rosso ON (RE1 LOW), Verde OFF (RE3 HIGH)
        LATECLR = (1 << 1);  // RE1 = 0 → ON
        LATESET = (1 << 3);  // RE3 = 1 → OFF
    }
}


