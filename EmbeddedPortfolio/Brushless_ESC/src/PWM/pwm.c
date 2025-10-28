#include <stdint.h>
#include "definitions.h"   // include plib_* (OCMP1, TMR2) generati da MCC
#include "pwm.h"

// Conversione us -> tick usando la freq reale del timer esposta da MCC.
// ticks = us * (TMR2_FrequencyGet / 1e6)  → arrotondato
static inline uint16_t us_to_ticks(uint16_t us)
{
    uint32_t f = TMR2_FrequencyGet();                 // es. 312500 Hz
    return (uint16_t)((us * f + 500000u) / 1000000u); // arrotonda correttamente
}

void PWM_Init(void)
{
    // Avvia le periferiche configurate in MCC
    TMR2_Start();
    OCMP1_Enable();

    // Imposta subito al minimo per armare l’ESC in sicurezza
    PWM_SetUS(PWM_US_MIN);
}

void PWM_SetUS(uint16_t us)
{
    if (us < PWM_US_MIN) us = PWM_US_MIN;
    if (us > PWM_US_MAX) us = PWM_US_MAX;

    OCMP1_CompareSecondaryValueSet(us_to_ticks(us));
}
