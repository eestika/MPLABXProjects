#ifndef ADC_CONTROL_H
#define ADC_CONTROL_H

#include <stdint.h>

// Inizializza ADC1 e seleziona AN4 (RB4)
void ADCCTL_Init(void);

// Legge una conversione singola su AN4 (0..1023)
uint16_t ADCCTL_ReadRaw(void);

// Filtro esponenziale semplice: y = (a*y + (N-a)*x)/N
// Consiglia: a=4, N=5  (≈ 80% vecchio, 20% nuovo) oppure a=9,N=10
static inline uint16_t ADCCTL_FilterEMA(uint16_t prev, uint16_t sample,
                                        uint8_t a, uint8_t N)
{
    return (uint16_t)((a * (uint32_t)prev + (uint32_t)(N - a) * sample) / N);
}

#endif // ADC_CONTROL_H
