#ifndef SERVO_PWM_H
#define SERVO_PWM_H

#include <stdint.h>
#include <stdbool.h>

/* Impostazioni di default “standard hobby servo”: 20 ms periodo, 1.0–2.0 ms impulso */
typedef struct {
    uint16_t min_us;      // tipicamente 1000
    uint16_t mid_us;      // tipicamente 1500 (facoltativo, solo per comodità)
    uint16_t max_us;      // tipicamente 2000
    uint16_t period_us;   // tipicamente 20000
} ServoPwmConfig_t;

/* Inizializza il driver servomotore su OC1 (Timer2 già configurato da MCC).
   - Abilita OCMP1
   - Aggancia il periodo già impostato su TMR2 (PR2)
   - Imposta impulso a centro */
void ServoPWM_Init(const ServoPwmConfig_t *cfg);

/* Set diretto della larghezza impulso in microsecondi (clippato tra min/max) */
void ServoPWM_SetPulseUS(uint16_t us);

/* Set in gradi 0–180 (mappato linearmente su [min_us..max_us]) */
void ServoPWM_SetAngleDeg(uint8_t deg);

#endif /* SERVO_PWM_H */
