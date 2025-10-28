#ifndef PWM_H
#define PWM_H

#include <stdint.h>

// limiti standard ESC (puoi cambiarli se serve)
#define PWM_US_MIN   1000u
#define PWM_US_MAX   2000u

// Inizializza il PWM basato su TMR2 + OC1 (già configurati da MCC)
void PWM_Init(void);

// Imposta l’impulso in microsecondi (clamp automatico ai limiti)
void PWM_SetUS(uint16_t us);

// Utility: mappa 0..1023 (ADC) -> 1000..2000 us
static inline uint16_t PWM_MapAdcToUS(uint16_t adc)
{
    return (uint16_t)(PWM_US_MIN + ((uint32_t)adc * (PWM_US_MAX - PWM_US_MIN)) / 1023u);
}

#endif // PWM_H
