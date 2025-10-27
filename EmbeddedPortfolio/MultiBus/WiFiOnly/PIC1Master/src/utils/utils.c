#include <xc.h>
#include "utils.h"

#define SYS_CLK_FREQ 80000000UL

void DelayMs(uint32_t ms)
{
    uint32_t start = _CP0_GET_COUNT();
    uint32_t ticks = (SYS_CLK_FREQ / 2 / 1000) * ms;
    while ((_CP0_GET_COUNT() - start) < ticks);
}
