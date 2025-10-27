#include "utils.h"
#include <definitions.h>  // per _CP0_GET_COUNT()

#define SYS_FREQ 80000000UL

void DelayMs(unsigned int ms)
{
    uint32_t tStart = _CP0_GET_COUNT();
    uint32_t tWait = (SYS_FREQ / 2000) * ms;
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}

