#include "logica.h"
#include "definitions.h"
#include "utils.h"

#define TEMP_THRESHOLD 25.0f  // soglia

void LOGIC_HandleTemperature(float temperature)
{
    if (temperature <= TEMP_THRESHOLD)
    {
        LATECLR = (1 << 3);  // LED verde ON (RE3 sinking)
        LATESET = (1 << 1);  // LED rosso OFF (RE1 sinking)
    }
    else
    {
        LATECLR = (1 << 1);  // LED rosso ON
        LATESET = (1 << 3);  // LED verde OFF
    }
}

