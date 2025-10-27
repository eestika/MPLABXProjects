#include <xc.h>
#include "definitions.h" // se fornisce SYSTEM_GetPeripheralClock() o simile
#include "utils.h"

// Il Core Timer corre a SYSCLK/2. Se non hai un getter del SYSCLK, lascia 80MHz.
#ifndef SYS_CLK_FREQ
#define SYS_CLK_FREQ 80000000UL
#endif

static inline uint32_t CoreTimerHz(void) {
    return (SYS_CLK_FREQ / 2u);  // CoreTimer = SYSCLK/2
}

void DelayMs(uint32_t ms)
{
    uint32_t ticks = (CoreTimerHz() / 1000u) * ms;
    uint32_t start = _CP0_GET_COUNT();
    while ((uint32_t)(_CP0_GET_COUNT() - start) < ticks) { }
}

