#include "delay_ms.h"
#include "definitions.h"   // TMR2_*

void DelayMs(uint32_t ms)
{
    uint32_t ticks_per_ms = TMR2_FrequencyGet() / 1000u; // es. 1250
    uint32_t remaining = ms * ticks_per_ms;
    uint16_t last = TMR2_CounterGet();

    while (remaining > 0u) {
        uint16_t now = TMR2_CounterGet();
        uint16_t delta = (uint16_t)(now - last);
        last = now;
        if (delta >= remaining) remaining = 0u; else remaining -= delta;
    }
}
