#include "definitions.h"   // include plib_adc.h generato da MCC
#include "adc_control.h"

void ADCCTL_Init(void)
{
    ADC_Enable();

    // MUX A, positivo = AN4, negativo = VREFL (come impostato in MCC)
#ifdef ADC_INPUT_POSITIVE_AN4
    ADC_InputSelect(ADC_MUX_A, ADC_INPUT_POSITIVE_AN4, ADC_INPUT_NEGATIVE_VREFL);
#else
    // fallback se gli enum hanno nomi diversi
    ADC_InputSelect(ADC_MUX_A, (ADC_INPUT_POSITIVE)4, ADC_INPUT_NEGATIVE_VREFL);
#endif
}

uint16_t ADCCTL_ReadRaw(void)
{
    // Sequenza manuale: SAMP=1 (sample) → piccola attesa → SAMP=0 (convert)
    ADC_SamplingStart();
    for (volatile uint32_t d = 0; d < 800; ++d) { __asm__ volatile("nop"); } // ~qualche µs
    ADC_ConversionStart();

    while (!ADC_ResultIsReady()) { /* wait */ }

#ifdef ADC_RESULT_BUFFER_0
    return (uint16_t)ADC_ResultGet(ADC_RESULT_BUFFER_0);
#else
    return (uint16_t)ADC_ResultGet((ADC_RESULT_BUFFER)0);
#endif
}
